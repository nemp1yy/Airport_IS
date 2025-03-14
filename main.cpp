#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
#include "airport.h"
#include "database.h"

using namespace std;

int main()
{   
    HWND consoleWindow = GetConsoleWindow();   
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleTitle("ИС \"Аэрофлот\"");


    dataAirport airport;
    database_airport db;
    int choice;
    int input_id;
    bool menu = true;

    db.create_table();

    while (menu)
    {   
        COORD bufferSize = {640, 320};
        SetConsoleScreenBufferSize(hConsole, bufferSize);
        SMALL_RECT windowSize = {0, 0, 640, 320};

        system("cls");

        if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
            std::cout << "Ошибка изменения размера окна. Код ошибки: " << GetLastError() << std::endl;
        }

        else cout << endl;

        cout << "Главное меню" << endl;
        cout << "1. Показать таблицу" << endl;
        cout << "2. Добавить запись" << endl;
        cout << "3. Добавить несколько записей" << endl;
        cout << "4. Обновить запись" << endl;
        cout << "5. Удалить запись" << endl;
        cout << "6. Поиск" << endl;
        cout << "7. Выход" << endl;
        cout << "Выберите пункт меню: "; cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
        {   
            COORD bufferSize = {320, 768};
            SetConsoleScreenBufferSize(hConsole, bufferSize);
            SMALL_RECT windowSize = {0, 0, 640, 768};

            system("cls");

            if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
                std::cout << "Ошибка изменения размера окна. Код ошибки: " << GetLastError() << std::endl;
            }

            system("cls");
            cout << left 
                 << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << left << setw(5) << "ID" 
                 << " | " << left << setw(6) << "Рейс" 
                 << " | " << left << setw(19) << "Авиакомпания" 
                 << " | " << left << setw(16) << "Откуда вылет" 
                 << " | " << left << setw(17) << "Пункт назначения"
                 << " | " << left << setw(17) << "Вылет в" 
                 << " | " << left << setw(17) << "Прибывает в" 
                 << " | " << left << setw(4) << "Гейт" 
                 << " | " << left << setw(14) << "Статус" 
                 << " | " << left << setw(13) << "Тип BC" << " | " << endl;
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            db.getData(); 
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
            system("pause");
            break;

        }
        case 2:
        {
            COORD bufferSize = {320, 768};
            SetConsoleScreenBufferSize(hConsole, bufferSize);
            SMALL_RECT windowSize = {0, 0, 640, 768};

            system("cls");

            if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
                std::cout << "Ошибка изменения размера окна. Код ошибки: " << GetLastError() << std::endl;
            }

            else cout << endl;

            cout << left 
                 << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << left << setw(6) << "Рейс" 
                 << " | " << left << setw(19) << "Авиакомпания" 
                 << " | " << left << setw(16) << "Откуда вылет" 
                 << " | " << left << setw(17) << "Пункт назначения"
                 << " | " << left << setw(17) << "Вылет в" 
                 << " | " << left << setw(17) << "Прибывает в" 
                 << " | " << left << setw(4) << "Гейт" 
                 << " | " << left << setw(14) << "Статус" 
                 << " | " << left << setw(13) << "Тип BC" << " | " << endl;
            cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            
            airport.input_table(0); 
            
            cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
            db.addData(airport);
            system("pause");

            break;
        }
        case 3:
        {
            int n;

            cout << "Кол-во записей, который будут добавлены: "; cin >> n;

            cout << endl << left 
                 << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << left << setw(6) << "Рейс" 
                 << " | " << left << setw(19) << "Авиакомпания" 
                 << " | " << left << setw(16) << "Откуда вылет" 
                 << " | " << left << setw(17) << "Пункт назначения"
                 << " | " << left << setw(17) << "Вылет в" 
                 << " | " << left << setw(17) << "Прибывает в" 
                 << " | " << left << setw(4) << "Гейт" 
                 << " | " << left << setw(14) << "Статус" 
                 << " | " << left << setw(13) << "Тип BC" << " | " << endl;
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;

            for (int i = 0; i <= n; i++)
            {
                airport.input_table(i);
                db.addData(airport);
                cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
                
            }

            cout << endl; system("pause");
            break;
        }
        case 4:
        {
            cout << "Введите id для обновления данных: "; cin >> input_id;
            airport.input();
            db.updateData(airport, input_id);
            break;
        }
        case 5:
        {
            cout << "Введите id для удаления: "; cin >> input_id;
            db.deleteData(input_id);
            break;

        }

        case 6:
        {   
            cout << "Поиск" << endl;
            
            cout << "Введите id для поиска: "; cin >> input_id;
            cout << left 
                 << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << left << setw(5) << "ID" 
                 << " | " << left << setw(6) << "Рейс" 
                 << " | " << left << setw(19) << "Авиакомпания" 
                 << " | " << left << setw(16) << "Откуда вылет" 
                 << " | " << left << setw(17) << "Пункт назначения"
                 << " | " << left << setw(17) << "Вылет в" 
                 << " | " << left << setw(17) << "Прибывает в" 
                 << " | " << left << setw(4) << "Гейт" 
                 << " | " << left << setw(14) << "Статус" 
                 << " | " << left << setw(13) << "Тип BC" << " | " << endl;
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            db.searchData(input_id);
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
            system("pause");
            break;
        }
        case 7:
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
    return 0;
}