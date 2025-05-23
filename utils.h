#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

string convertTo_utf8(const string& input) {
    int wideSize = MultiByteToWideChar(1251, 0, input.c_str(), -1, nullptr, 0);
    if (wideSize <= 0) return "";

    wstring wideStr(wideSize, L'\0');
    MultiByteToWideChar(1251, 0, input.c_str(), -1, &wideStr[0], wideSize);

    int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8Size <= 0) return "";

    string utf8Str(utf8Size, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &utf8Str[0], utf8Size, nullptr, nullptr);

    return utf8Str;
}

string convertTo_1251(const string& input) {
    int wideSize = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, nullptr, 0);
    if (wideSize <= 0) return "";

    wstring wideStr(wideSize, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, &wideStr[0], wideSize);

    int ansiSize = WideCharToMultiByte(1251, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (ansiSize <= 0) return "";

    string cp1251Str(ansiSize, '\0');
    WideCharToMultiByte(1251, 0, wideStr.c_str(), -1, &cp1251Str[0], ansiSize, nullptr, nullptr);

    return cp1251Str;
}

void gotoxy(int x, int y)                                                                                                                                                                                               
{                                                                                                                                                                                                                                              
    COORD coord;                                                                                                                                                                                                        
    coord.X = x;                                                                                                                                                                                                        
    coord.Y = y;                                                                                                                                                                                                        
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);                                                                                                                                                   
}  

void about_programm()
    {
        cout << "\n�������������� ������� \"��������\" " << endl
                << "�����: �������� ��������� �������������" << endl << endl
                << "--------------------------------------------------------------------------" << endl << endl
                << "� ������� \"��������\" ������� ����:" << endl << endl
                << " - ���;" << endl
                << " - ����;" << endl
                << " - ������������;" << endl
                << " - ������ ����� � ����� ����������;" << endl
                << " - ����� ������ � ��������" << endl
                << " - ����;" << endl
                << " - ������;" << endl
                << " - ��� ���������� �����;" << endl << endl
                << "--------------------------------------------------------------------------" << endl << endl
                << "������:" << endl << endl
                << " 1. �����: ��������� ������� ������ �� ��;" << endl
                << " 2. ���� / ����������: ��������� �������� ������ � ��;" << endl
                << " 3. ���������� ����. ������: ��������� �������� n-���������� ������;" << endl
                << " 4. ����������: ��������� �������� ������ �� ���� (id);" << endl
                << " 5. ��������: ��������� ������� ������ �� �� �� ����������;" << endl
                << " 6. �����: ��������� ����� ������ �� �� �� ����������;" << endl
                << " 7. � ���������: ������� ���������� �� ������ � ���������;" << endl
                << " 8. �����: ����� �� ���������;" << endl << endl
                << "--------------------------------------------------------------------------" << endl << endl;

    }

#endif