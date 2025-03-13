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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleTitle("�� \"��������\"");


    dataAirport airport;
    database_airport db;
    int choice;
    int input_id;
    bool menu = true;

    db.create_table();

    while (menu)
    {   
        system("cls");

        cout << "������� ����" << endl;
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
            MoveWindow(consoleWindow, 100, 100, 800, 1000, TRUE);
            system("cls");
            cout << left 
                 << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << left << setw(5) << "ID" 
                 << " | " << left << setw(6) << "����" 
                 << " | " << left << setw(19) << "������������" 
                 << " | " << left << setw(16) << "������ �����" 
                 << " | " << left << setw(17) << "����� ����������"
                 << " | " << left << setw(17) << "����� �" 
                 << " | " << left << setw(17) << "��������� �" 
                 << " | " << left << setw(4) << "����" 
                 << " | " << left << setw(14) << "������" 
                 << " | " << left << setw(13) << "��� BC" << " | " << endl;
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            db.getData(); 
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
            system("pause");
            break;

        }
        case 2:
        {
            cout << "�������� ������" << endl;
            airport.input();
            db.addData(airport);

            break;
        }
        case 3:
        {
            int n;

            cout << "���-�� �������, ������� ����� ���������: "; cin >> n;
            for (int i = 0; i <= n; i++)
            {
                airport.input();
                db.addData(airport);
                system("pause");
            }

            break;
        }
        case 4:
        {
            cout << "������� id ��� ���������� ������: "; cin >> input_id;
            airport.input();
            db.updateData(airport, input_id);
            break;
        }
        case 5:
        {
            cout << "������� id ��� ��������: "; cin >> input_id;
            db.deleteData(input_id);
            break;

        }

        case 6:
        {   
            cout << "�����" << endl;
            
            cout << "������� id ��� ������: "; cin >> input_id;
            cout << left 
                 << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << left << setw(5) << "ID" 
                 << " | " << left << setw(6) << "����" 
                 << " | " << left << setw(19) << "������������" 
                 << " | " << left << setw(16) << "������ �����" 
                 << " | " << left << setw(17) << "����� ����������"
                 << " | " << left << setw(17) << "����� �" 
                 << " | " << left << setw(17) << "��������� �" 
                 << " | " << left << setw(4) << "����" 
                 << " | " << left << setw(14) << "������" 
                 << " | " << left << setw(13) << "��� BC" << " | " << endl;
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            db.searchData(input_id);
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
            system("pause");
            break;
        }
        case 7:
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
    return 0;
}