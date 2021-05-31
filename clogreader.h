#pragma once

// Strings and streams are not part of STL (a.k.a. Standard Template Library) 
// but from C++ Standart Library
#include <fstream>

class CLogReader final
{
public:
    CLogReader() = default;
    ~CLogReader() = default;
    CLogReader(const CLogReader&) = delete;
    CLogReader& operator=(const CLogReader&) = delete;
    CLogReader(CLogReader&&) = delete;
    CLogReader& operator=(CLogReader&&) = delete;

    bool    Open(const char* filename);      // открытие файла, false - ошибка
    void    Close();                         // закрытие файла

    bool    SetFilter(const char* filter);   // установка фильтра строк, false - ошибка
    bool    GetNextLine(char* buf,           // запрос очередной найденной строки,
                        const int bufsize);  // buf - буфер, bufsize - максимальная длина
                                             // false - конец файла или ошибка

private:
    bool string_search(const char* line, const char* filter);

    std::ifstream file_;
    const char* filter_ = "";
};
