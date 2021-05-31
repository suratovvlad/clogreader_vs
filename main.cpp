
// Strings and streams are not part of STL (a.k.a. Standard Template Library) 
// but from C++ Standart Library
#include <iostream>
#include "clogreader.h"

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: \n\t" << argv[0] << " /path/to/file search_mask" << std::endl;
        return -1;
    }

    const auto filename = argv[1];
    const auto filter = argv[2];

    if (CLogReader log_reader{};
        log_reader.Open(filename))
    {
        log_reader.SetFilter(filter);

        for (char buf[1024] = ""; ; buf[0] = 0)
        {
            const auto result = log_reader.GetNextLine(buf, sizeof buf);

            if (result && strlen(buf) > 0)
                std::cout << buf << std::endl;

            if (!result)
                break;
        }

        log_reader.Close();
    }
    else 
    {
        std::cout << "Cannot open file: " << filename << std::endl;
    }
 

    return 0;
}

