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
            terminal = 0;
            bagBelt = 0;
        }
    

    void input()
    {   
        int var;

        cout << "Рейс: "; cin >> flight;
        cout << "Авиакомпания: "; cin >> airline;
        cout << "Откуда вылет: "; cin >> departure_from;
        cout << "Пункт назначения: "; cin >> destination;
        cin.get();
        cout << "Вылет в: "; getline(cin, departure_time);
        cout << "Прибывает в: "; getline(cin, arrival_time);
        cout << "Гейт: "; cin >> gate;
        cout << "Статус: " << endl 
             << " 1. По рассписанию" << endl
             << " 2. Задержан" << endl
             << " 3. Отменен" << endl
             << "Ваш вариант: "; cin >> var; status = airport_Status[var-1];
        cin.get();
        cout << "Тип BC: "; getline(cin, aircraft_type);
        cout << "Терминал: "; cin >> terminal;
        cout << "Багажная лента: "; cin >> bagBelt;

    }

    void output()
    {
        cout << left << setw(10) << "Рейс: " << flight << endl
             << left << setw(10) << "Авиакомпания: " << airline << endl
             << left << setw(10) << "Откуда вылет: " << departure_from << endl
             << left << setw(10) << "Пункт назначения:" << destination << endl
             << left << setw(10) << "Вылет в: " << departure_time << endl
             << left << setw(10) << "Прибывает в:" << arrival_time << endl
             << left << setw(10) << "Гейт: " << gate << endl
             << left << setw(10) << "Статус: " << status << endl
             << left << setw(10) << "Тип BC: " << aircraft_type << endl
             << left << setw(10) << "Терминал: " << terminal << endl
             << left << setw(10) << "Багажная лента: " << bagBelt << endl;
    }


    string getFlight() { return flight; }
    string getAirline() { return airline; }
    string getDeparture_from() { return departure_from; }
    string getDestination() { return destination; }
    string getDeparture_time() { return departure_time; }
    string getArrival_time() { return arrival_time; }
    string getGate() { return gate; }
    string getStatus() { return status; }
    string getAircraft_type() { return aircraft_type; }
    int getTerminal() { return terminal; }
    int getBagBelt() { return bagBelt; }

    void setFlight(string flight) { this->flight = flight; }
    void setAirline(string airline) { this->airline = airline; }
    void setDeparture_from(string departure_from) { this->departure_from = departure_from; }
    void setDestination(string destination) { this->destination = destination; }
    void setDeparture_time(string departure_time) { this->departure_time = departure_time; }
    void setArrival_time(string arrival_time) { this->arrival_time = arrival_time; }
    void setGate(string gate) { this->gate = gate; }
    void setStatus(string status) { this->status = status; }
    void setAircraft_type(string aircraft_type) { this->aircraft_type = aircraft_type; }
    void setTerminal(int terminal) { this->terminal = terminal; }
    void setBagBelt(int bagBelt) { this->bagBelt = bagBelt; }

    void setAll(string flight, string airline, string departure_from, string destination, string departure_time, string arrival_time, string gate, string status, string aircraft_type, int terminal, int bagBelt)
    {
        this->flight = flight;
        this->airline = airline;
        this->departure_from = departure_from;
        this->destination = destination;
        this->departure_time = departure_time;
        this->arrival_time = arrival_time;
        this->gate = gate;  
        this->status = status;
        this->aircraft_type = aircraft_type;
        this->terminal = terminal;
        this->bagBelt = bagBelt;
    }

};

#endif