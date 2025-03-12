#ifndef DATAAIRPORT_h
#define DATAAIRPORT_h

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <array>
#include <chrono>
#include <sstream>


using namespace std;
using namespace chrono;

class dataAirport
{
    private:
        int id;
        int terminal;
        int bagBelt;
        string departute_time;
        string arrival_time;
        array<string, 3> airport_Status = { "�� ����������", "��������", "�������" };
        string status;
        string aircraft_type;
        string airline;
        string flight;
        string departure_from;
        string destination;
        string gate;

    public:
        dataAirport()
        {
            flight = "n/a";
            airline = "n/a";
            departure_from = "n/a";
            destination = "n/a";
            departute_time = "n/a";
            arrival_time = "n/a";
            gate = "n/a";
            status = airport_Status[0];
            aircraft_type = "n/a";
            terminal = 0;
            bagBelt = 0;
        }
    

    // system_clock::time_point inputTime(string prompt)
    // {
    //         string input;
    //     cout << prompt;
    //     getline(cin, input);

    //     istringstream ss(input);
    //     system_clock::time_point tp;
    //     time_t time = system_clock::to_time_t(tp);

    //     // Parse input time (this is an example, need parsing mechanism)
    //     ss >> get_time(&time, "%Y-%m-%d %H:%M");

    //     return tp;
    // }

    void input()
    {   
        int var;

        cout << "����: "; cin >> flight;
        cout << "������������: "; cin >> airline;
        cout << "������ �����: "; cin >> departure_from;
        cout << "����� ����������:"; cin >> destination;
        cout << "����� �: "; getline(cin, departute_time);
        cout << "��������� �:"; getline(cin, arrival_time);
        cout << "����: "; cin >> gate;
        cout << "������: " << endl 
             << " 1. �� �����������" << endl
             << " 2. ��������" << endl
             << " 3. �������" << endl
             << "��� �������: "; cin >> var; status = airport_Status[var-1];
        cout << "��� BC"; cin >> aircraft_type;
        cout << "��������: "; cin >> terminal;
        cout << "�������� �����: "; cin >> bagBelt;

    }

    void output()
    {
        
    }

};

#endif