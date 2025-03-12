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

        cout << "�� \"��������\". ������� ����" << endl;
        cout << "1. �������� �������" << endl;
        cout << "2. �������� ������" << endl;
        cout << "3. �������� ��������� �������" << endl;
        cout << "4. �������� ������" << endl;
        cout << "5. ������� ������" << endl;
        cout << "6. �����" << endl;
        cout << "7. �����" << endl;
        cout << "�������� ����� ����: "; cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
        {
            cout << "�������:" << endl;
            db.output_airport();
            break;

        }
        case 2:
        {
            cout << "�������� ������" << endl;
            airport.input();
            db.input_airport(airport);
            break;
        }
        case 3:
        {
            int n;

            cout << "���-�� �������, ������� ����� ���������: "; cin >> n;
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
            cout << "�����" << endl;
            
            cout << "������� id ��� ������:"; cin >> input_id;
            break;
        }
        case 5:
        {   
            system("cls"); cout << "�����!"; system("pause");
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
    return 0;
}