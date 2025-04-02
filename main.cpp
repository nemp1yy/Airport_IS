#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
#include "airport.h"
#include "database.h"
#include "utils.h"

using namespace std;

int main()
{   
    HWND consoleWindow = GetConsoleWindow();   
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleTitle("�� \"��������\"");

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
        cout << "������� ������� ���������." << endl;
    }

    system("pause");

    while (menu)
    {   
        system("cls");
        cout << "������� ����" << endl
             << "----------------------------" << endl;
        cout << "1. �������� �������" << endl;
        cout << "2. �������� ������" << endl;
        cout << "3. �������� ��������� �������" << endl;
        cout << "4. �������� ������" << endl;
        cout << "5. ������� ������" << endl;
        cout << "6. ����� ������" << endl;
        cout << "7. � ���������" << endl;
        cout << "8. �����" << endl;
        cout << "�������� ����� ����: "; cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
        {   
            cout << "����� �������" << endl
                << "----------------------------" << endl; system("pause"); system("cls");
            
            db.getData(); 
            system("pause");
            break;

        }
        case 2:
        {
            cout << "���� ������." << endl
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
            cout << "���� ���������� �������." << endl
                << "----------------------------" << endl;
            cout << "���-�� �������, ������� ����� ���������: "; cin >> n; system("cls");

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
            
            cout << "�������� ������" << endl
                << "----------------------------" << endl; system("pause"); system("cls");
            db.deleteData();
            system("pause");
            break;
        }

        case 6:
        {   
            cout << "�����" << endl
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
            system("cls"); cout << "�����!" << endl; system("pause");
            db.close_database();
            menu = false;
            break;
        }

        default:
        {
            cout << "�������� ����� ����, ���������� ��� ���." << system("pause") << endl;
            break;
        }

    }
    }

    system("cls");
    return 0;
}