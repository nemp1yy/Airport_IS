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
    SetConsoleTitle("�� \"��������\"");


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
            std::cout << "������ ��������� ������� ����. ��� ������: " << GetLastError() << std::endl;
        }

        else cout << endl;

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
            COORD bufferSize = {320, 768};
            SetConsoleScreenBufferSize(hConsole, bufferSize);
            SMALL_RECT windowSize = {0, 0, 640, 768};

            system("cls");

            if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
                std::cout << "������ ��������� ������� ����. ��� ������: " << GetLastError() << std::endl;
            }

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
            COORD bufferSize = {320, 768};
            SetConsoleScreenBufferSize(hConsole, bufferSize);
            SMALL_RECT windowSize = {0, 0, 640, 768};

            system("cls");

            if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
                std::cout << "������ ��������� ������� ����. ��� ������: " << GetLastError() << std::endl;
            }

            else cout << endl;

            cout << left 
                 << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << left << setw(6) << "����" 
                 << " | " << left << setw(19) << "������������" 
                 << " | " << left << setw(16) << "������ �����" 
                 << " | " << left << setw(17) << "����� ����������"
                 << " | " << left << setw(17) << "����� �" 
                 << " | " << left << setw(17) << "��������� �" 
                 << " | " << left << setw(4) << "����" 
                 << " | " << left << setw(14) << "������" 
                 << " | " << left << setw(13) << "��� BC" << " | " << endl;
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

            cout << "���-�� �������, ������� ����� ���������: "; cin >> n;

            cout << endl << left 
                 << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << left << setw(6) << "����" 
                 << " | " << left << setw(19) << "������������" 
                 << " | " << left << setw(16) << "������ �����" 
                 << " | " << left << setw(17) << "����� ����������"
                 << " | " << left << setw(17) << "����� �" 
                 << " | " << left << setw(17) << "��������� �" 
                 << " | " << left << setw(4) << "����" 
                 << " | " << left << setw(14) << "������" 
                 << " | " << left << setw(13) << "��� BC" << " | " << endl;
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