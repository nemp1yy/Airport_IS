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
    dataAirport airport;
    database_airport db;
    int choice;
    bool menu = true;
    while (menu)
    {   
        system("cls");

        cout << "ИС \"Аэрофлот\". Главное меню" << endl;
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
            cout << "Таблица:" << endl;
            db.output_airport();
            break;

        }
        case 2:
        {
            cout << "Добавить запись" << endl;
            airport.input();
            db.input_airport(airport);
            break;
        }
        case 3:
        {
            int n;

            cout << "Кол-во записей, который будут добавлены: "; cin >> n;
            for (int i = 0; i <= n; i++)
            {
                airport.input();
                db.input_airport(airport);
            }

            break;
        }
        case 4:
        {   
            int input_id;
            cout << "Поиск" << endl;
            
            cout << "Введите id для поиска:"; cin >> input_id;
            break;
        }
        case 5:
        {   
            system("cls"); cout << "Удачи!"; system("pause");
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