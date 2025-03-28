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
        cout << "\nИнформационная система \"Аэрофлот\" " << endl
                << "Автор: Свинухов Александр Александрович" << endl << endl
                << "--------------------------------------------------------------------------" << endl << endl
                << "В объекте \"Аэрофлот\" имеется поля:" << endl << endl
                << " - Код;" << endl
                << " - Рейс;" << endl
                << " - Авиакомпания;" << endl
                << " - Откуда вылет и пункт назначения;" << endl
                << " - Время вылета и прибытия" << endl
                << " - Гейт;" << endl
                << " - Статус;" << endl
                << " - Тип воздушного судна;" << endl << endl
                << "--------------------------------------------------------------------------" << endl << endl
                << "Методы:" << endl << endl
                << " 1. Вывод: позволяет вывести данные из БД;" << endl
                << " 2. Ввод / Добавление: позволяет добавить данные в БД;" << endl
                << " 3. Добавление неск. файлов: позволяет добавить n-количество данных;" << endl
                << " 4. Обновление: позволяет обновить данные по коду (id);" << endl
                << " 5. Удаление: позволяет удалять данные из БД по параметрам;" << endl
                << " 6. Поиск: позволяет найти данные из БД по параметрам;" << endl
                << " 7. О программе: выводит информацию об авторе и программе;" << endl
                << " 8. Выход: выход из программы;" << endl << endl
                << "--------------------------------------------------------------------------" << endl << endl;

    }

#endif