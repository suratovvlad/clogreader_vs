#include "clogreader.h"

#include <windows.h>

// DgbHelp is part of Win32 API
#include <DbgHelp.h>

// Strings and streams are not part of STL (a.k.a. Standard Template Library) 
// but from C++ Standart Library
#include <fstream>
#include <string>
#include <iostream>

bool CLogReader::Open(const char* filename)
{
    file_.open(filename);
    return file_.is_open();
}

void CLogReader::Close()
{
    if (file_.is_open())
        file_.close();
}

bool CLogReader::SetFilter(const char* filter)
{
    filter_ = filter;
    return true;
}

bool CLogReader::GetNextLine(char* buf, const int bufsize)
{
    if (!buf)
        return false;

    if (auto line = std::string{};
        std::getline(file_, line))
    {
        const auto line_c_str = line.c_str();

        if (string_search(line_c_str, filter_))
        {
            const auto ret = strncpy_s(buf, bufsize, line_c_str, bufsize - 1);
            if (ret != 0)
                return false;
        }

        return true;
    }

    return false;
}

bool CLogReader::string_search(const char* line, const char* filter)
{
#ifdef USE_DBG_HELP
    // Actually, this works, but it is not very 
    // fast when several '*' goes one after another
    return SymMatchString(line, filter, false)
#else
    const char* line_keep_pointer = nullptr;
    const char* mask_keep_pointer = nullptr;

    const char asteriks = '*';
    const char question = '?';

    // compare to first '*'
    while ( *line && *filter != asteriks)
    {
        if ( *filter != *line && *filter != question )
        {
            return false;
        }

        ++filter;
        ++line;
    }

    while ( *line )
    {
        // go through several asteriks
        if (*filter == asteriks)
        {
            ++filter;
            if (!*filter)
                return true;
 
            mask_keep_pointer = filter;
            line_keep_pointer = line + 1;
        }
        // compare exact part
        else if ( *filter == *line || *filter == question )
        {
            ++filter;
            ++line;
        }
        // keep going
        else 
        {
            filter = mask_keep_pointer;
            line = line_keep_pointer++;
        }
    }

    // ignore last asteriks
    while ( *filter == asteriks )
    {
        ++filter;
    }

    // check if pointer reaches end of filter
    return !*filter;
#endif
}
