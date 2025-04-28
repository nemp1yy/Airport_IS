#ifndef DATAAIRPORT_h
#define DATAAIRPORT_h

#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <sstream>
#include <Windows.h>
#include "utils.h"


using namespace std;
class dataAirport
{
    private:
        int id;
        string departure_time;
        string arrival_time;
        array<string, 3> airport_Status = { "По расписанию", "Задержан", "Отменен" };
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
            departure_time = "n/a";
            arrival_time = "n/a";
            gate = "n/a";
            status = airport_Status[0];
            aircraft_type = "n/a";
        }
    
    void table_header()
    {
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
    }

    void table_footer()
    {
        cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
    }

    void input(int count)
    {
        int var;
        gotoxy(0,3+count); cout << "| "; cin.get(); cin >> flight;
        gotoxy(9, 3+count); cout << "| "; cin.get(); getline(cin, airline);
        gotoxy(31, 3+count); cout << "| "; cin >> departure_from;
        gotoxy(50, 3+count); cout << "| "; cin >> destination;
        gotoxy(70, 3+count); cout << "| "; cin.get(); getline(cin, departure_time);
        gotoxy(90, 3+count); cout << "| "; cin.get(); getline(cin, arrival_time);
        gotoxy(110, 3+count); cout << "| "; cin >> gate;

        gotoxy(1, 10+count); cout << "Статус: " << endl 
            << " 1. По расписанию" << endl
            << " 2. Задержан" << endl
            << " 3. Отменен" << endl
            << "Ваш вариант: "; cin >> var; status = airport_Status[var-1];
        
        string selectedStatus = airport_Status[var-1];
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int row = 10; row <= 14; row++) {
            COORD startPos = {1, static_cast<SHORT>(row)};
            DWORD written;
            FillConsoleOutputCharacter(hConsole, ' ', 79, startPos, &written);
        }
    
        status = selectedStatus;
        gotoxy(117, 3+count); cout << "| "; cout << status; 
        gotoxy(134, 3+count); cout << "| "; cin.get(); getline(cin, aircraft_type);
        gotoxy(150, 3+count); cout << "| " << endl; 
    }

    void output() const
    {
       cout << "| " << setw(7) << convertTo_1251(flight)
            << " | " << setw(20) << convertTo_1251(airline)
            << " | " << setw(17) << convertTo_1251(departure_from)
            << " | " << setw(18) << convertTo_1251(destination)
            << " | " << setw(18) << convertTo_1251(departure_time)
            << " | " << setw(18) << convertTo_1251(arrival_time)
            << " | " << setw(5) << convertTo_1251(gate)
            << " | " << setw(15) << convertTo_1251(status)
            << " | " << setw(15) << convertTo_1251(aircraft_type) << "|" << endl;
    }

    string getId() const { return to_string(id); }
    string getFlight() const { return flight; }
    string getAirline() const { return airline; }
    string getDeparture_from() const { return departure_from; }
    string getDestination() const { return destination; }
    string getDeparture_time() const { return departure_time; }
    string getArrival_time() const { return arrival_time; }
    string getGate() const { return gate; }
    string getStatus() const { return status; }
    string getAircraft_type() const { return aircraft_type; }

    void setId(int id) { this->id = id; }
    void setFlight(string flight) { this->flight = flight; }
    void setAirline(string airline) { this->airline = airline; }
    void setDeparture_from(string departure_from) { this->departure_from = departure_from; }
    void setDestination(string destination) { this->destination = destination; }
    void setDeparture_time(string departure_time) { this->departure_time = departure_time; }
    void setArrival_time(string arrival_time) { this->arrival_time = arrival_time; }
    void setGate(string gate) { this->gate = gate; }
    void setStatus(string status) { this->status = status; }
    void setAircraft_type(string aircraft_type) { this->aircraft_type = aircraft_type; }

};

#endif