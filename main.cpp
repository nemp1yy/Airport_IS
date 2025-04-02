#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
#include "airport.h"
#include "database.h"
#include "utils.h"

using namespace std;

#define IDI_APP_ICON 101

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Регистрация класса окна
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyApp";
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON)); // Загрузка иконки
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR);
        return 0;
    }

    // Создание окна
    HWND hwnd = CreateWindow(
        "MyApp", "My App with Icon", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Цикл сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

int main()
{   
    HWND consoleWindow = GetConsoleWindow();   
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleTitle("ИС \"Аэрофлот\"");

    bool menu = true;
    int choice;
    dataAirport airport;
    database_airport db;

    if (!db.tableExits())
    {
        db.create_table();
    }

    else 
    {
        cout << "Таблица успешно загружена." << endl;
    }

    system("pause");

    while (menu)
    {   
        system("cls");
        cout << "Главное меню" << endl
             << "----------------------------" << endl;
        cout << "1. Показать таблицу" << endl;
        cout << "2. Добавить запись" << endl;
        cout << "3. Добавить несколько записей" << endl;
        cout << "4. Обновить запись" << endl;
        cout << "5. Удалить запись" << endl;
        cout << "6. Поиск записи" << endl;
        cout << "7. О программе" << endl;
        cout << "8. Выход" << endl;
        cout << "Выберите пункт меню: "; cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
        {   
            cout << "Показ таблицы" << endl
                << "----------------------------" << endl; system("pause"); system("cls");
            
            db.getData(); 
            system("pause");
            break;

        }
        case 2:
        {
            cout << "Ввод данных." << endl
            << "----------------------------" << endl; system("pause"); system("cls");
            airport.table_header();
            airport.input_table(0); 
            airport.table_footer();
            
            db.addData(airport);
            system("pause");

            break;
        }
        case 3:
        {
            int n;
            cout << "Ввод нескольких записей." << endl
                << "----------------------------" << endl;
            cout << "Кол-во записей, который будут добавлены: "; cin >> n; system("cls");

            airport.table_header();
            for (int i = 0; i < n; i++)
            {
                airport.input_table(i);
                db.addData(airport);
                
            }

            airport.table_footer();

            cout << endl; system("pause");
            break;
        }
        case 4:
        {
            db.updateData();
            break;
        }
        case 5:
        {   
            
            cout << "Удаление записи" << endl
                << "----------------------------" << endl; system("pause"); system("cls");
            db.deleteData();
            system("pause");
            break;
        }

        case 6:
        {   
            cout << "Поиск" << endl
                << "----------------------------" << endl; system("pause"); system("cls");
            db.searchData();
            system("pause");
            break;
        }

        case 7:
        {
            about_programm();
            system("pause");
            break;
        }

        case 8:
        {   
            system("cls"); cout << "Удачи!" << endl; system("pause");
            db.close_database();
            menu = false;
            break;
        }

        default:
        {
            cout << "Неверный пункт меню, попробуйте ещё раз." << system("pause") << endl;
            break;
        }

    }
    }

    system("cls");
    return 0;
}