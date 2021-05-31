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

    bool    Open(const char* filename);      // �������� �����, false - ������
    void    Close();                         // �������� �����

    bool    SetFilter(const char* filter);   // ��������� ������� �����, false - ������
    bool    GetNextLine(char* buf,           // ������ ��������� ��������� ������,
                        const int bufsize);  // buf - �����, bufsize - ������������ �����
                                             // false - ����� ����� ��� ������

private:
    bool string_search(const char* line, const char* filter);

    std::ifstream file_;
    const char* filter_ = "";
};
