#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <Windows.h>
#include "sqlite3.h"
#include "airport.h"
#include "utils.h"

using namespace std;
class database_airport
    {
    protected:
     sqlite3 *db;
     char *errMsg = 0;

     string flight = "-", 
           airline = "-", 
           departure_from = "-", 
           destination = "-", 
           departure_time_range1 = "-", 
           departure_time_range2 = "-", 
           arrival_time_range1 = "-", 
           arrival_time_range2 = "-", 
           gate = "-", 
           status = "-", 
           aircraft_type = "-";

    public:
        database_airport()
        {
            if (sqlite3_open("data.db", &db)) {
                cerr << "Не открывается БД :< " << sqlite3_errmsg(db) << endl;
                exit(1);
            }

        }

        bool tableExits()
        {
            string query = "SELECT name FROM sqlite_master WHERE type='table' AND name='flights'";
            sqlite3_stmt *stmt;

            if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0) != SQLITE_OK) {
                cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
                return false;
            }

            bool result = sqlite3_step(stmt) == SQLITE_ROW;
            sqlite3_finalize(stmt);

            return result;
        }


        void create_table()
        {
            const char *sql = "CREATE TABLE IF NOT EXISTS flights (id INTEGER PRIMARY KEY, departure_time DATETIME NOT NULL, arrival_time DATETIME NOT NULL, status TEXT NOT NULL, aircraft_type TEXT NOT NULL, airline TEXT NOT NULL, flight TEXT NOT NULL, departure_from TEXT NOT NULL, destination TEXT NOT NULL, gate TEXT NOT NULL);";
            if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            } else {
                std::cout << "Таблица успешна создана" << std::endl;
            }
        }

        void inputData()
        {   

            cout << left 
                 << "+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << left << setw(6) << "Рейс" 
                 << " | " << left << setw(19) << "Авиакомпания" 
                 << " | " << left << setw(16) << "Откуда вылет" 
                 << " | " << left << setw(17) << "Пункт назначения"
                 << " | " << left << setw(17) << "Вылет в (от)" 
                 << " | " << left << setw(17) << "Вылет в (до)"
                 << " | " << left << setw(17) << "Прибывает в (от)" 
                 << " | " << left << setw(17) << "Прибывает в (до)"
                 << " | " << left << setw(4) << "Гейт" 
                 << " | " << left << setw(14) << "Статус" 
                 << " | " << left << setw(10) << "Тип BC" << " | " << endl;
            cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;


                gotoxy(0,3); cout << "| "; cin >> flight;
                cin.get();

                gotoxy(9, 3); cout << "| "; getline(cin, airline);
                gotoxy(31, 3); cout << "| "; getline(cin, departure_from);
                gotoxy(50, 3); cout << "| "; getline(cin, destination);
                gotoxy(70, 3); cout << "| "; getline(cin, departure_time_range1);
                gotoxy(90, 3); cout << "| "; getline(cin, departure_time_range2);
                gotoxy(110, 3); cout << "| "; getline(cin, arrival_time_range1);
                gotoxy(130, 3); cout << "| "; getline(cin, arrival_time_range2);
                gotoxy(150, 3); cout << "| "; getline(cin, gate);
                gotoxy(157, 3); cout << "| "; getline(cin, status);
                gotoxy(174, 3); cout << "| "; getline(cin, aircraft_type);
                gotoxy(187, 3); cout << "| " << endl; cin.ignore();

                cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;

    }

        bool addData(dataAirport flight) {
            const char* sql = "INSERT INTO flights (departure_time, arrival_time, status, aircraft_type, airline, flight, departure_from, destination, gate) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
            
            sqlite3_stmt* stmt;
            int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Cannot be insert into table: " << sqlite3_errmsg(db) << std::endl;
                return false;
            }
        
            auto safe_convert_utf = [](const string& text) -> string {
                string utf8_text = convertTo_utf8(text);
                if (utf8_text.empty()) {
                    cerr << "Error: " << text << endl;
                    return "";
                }
                return utf8_text;
            };
            
            sqlite3_bind_text(stmt, 1, safe_convert_utf(flight.getDeparture_time()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, safe_convert_utf(flight.getArrival_time()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, safe_convert_utf(flight.getStatus()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 4, safe_convert_utf(flight.getAircraft_type()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 5, safe_convert_utf(flight.getAirline()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 6, safe_convert_utf(flight.getFlight()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 7, safe_convert_utf(flight.getDeparture_from()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 8, safe_convert_utf(flight.getDestination()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 9, safe_convert_utf(flight.getGate()).c_str(), -1, SQLITE_TRANSIENT);
        
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(stmt);
                return false;
            }
        
            sqlite3_finalize(stmt);
            return true;
        }
        
        
        // bool updateData()
        // {   
        //     inputData();
        //     vector<dataAirport> foundRecords;
    
        //         string sql = "SELECT * FROM flights WHERE 1=1";
        //         vector<string> conditions;

        //         // Добавляем условия для каждого параметра, если он не равен "-"
        //         if (flight != "-")
        //             conditions.push_back("flight = ?");

        //         if (airline != "-")
        //             conditions.push_back("airline = ?");

        //         if (departure_from != "-")
        //             conditions.push_back("departure_from = ?");

        //         if (destination != "-")
        //             conditions.push_back("destination = ?");

        //         if (departure_time_range1 != "-" && departure_time_range2 != "-")
        //             conditions.push_back("departure_time BETWEEN ? AND ?");
        //         else if (departure_time_range1 != "-")
        //             conditions.push_back("departure_time >= ?");
        //         else if (departure_time_range2 != "-")
        //             conditions.push_back("departure_time <= ?");

        //         if (arrival_time_range1 != "-" && arrival_time_range2 != "-")
        //             conditions.push_back("arrival_time BETWEEN ? AND ?");
        //         else if (arrival_time_range1 != "-")
        //             conditions.push_back("arrival_time >= ?");
        //         else if (arrival_time_range2 != "-")
        //             conditions.push_back("arrival_time <= ?");

        //         if (gate != "-")
        //             conditions.push_back("gate = ?");

        //         if (status != "-")
        //             conditions.push_back("status = ?");

        //         if (aircraft_type != "-")
        //             conditions.push_back("aircraft_type = ?");

        //         // Добавляем условия в SQL-запрос
        //         for (const auto& condition : conditions) {
        //             sql += " AND " + condition;
        //         }

        //         sqlite3_stmt *stmt;
        //         if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        //             cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        //             return;
        //         }

        //         auto safe_convert_utf = [](const string& text) -> string {
        //             string utf8_text = convertTo_utf8(text);
        //             if (utf8_text.empty()) {
        //                 cerr << "Error: " << text << endl;
        //                 return "";
        //             }
        //             return utf8_text;
        //         };

        //         // Связываем параметры с запросом
        //         int paramIndex = 1;

        //         if (flight != "-")
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(flight).c_str(), -1, SQLITE_TRANSIENT);
                
        //         if (airline != "-")
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(airline).c_str(), -1, SQLITE_TRANSIENT);

        //         if (departure_from != "-")
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_from).c_str(), -1, SQLITE_TRANSIENT);

        //         if (destination != "-")
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(destination).c_str(), -1, SQLITE_TRANSIENT);

        //         if (departure_time_range1 != "-" && departure_time_range2 != "-") {
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range1).c_str(), -1, SQLITE_TRANSIENT);
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range2).c_str(), -1, SQLITE_TRANSIENT);
        //         } else if (departure_time_range1 != "-") {
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range1).c_str(), -1, SQLITE_TRANSIENT);
        //         } else if (departure_time_range2 != "-") {
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range2).c_str(), -1, SQLITE_TRANSIENT);
        //         }

        //         if (arrival_time_range1 != "-" && arrival_time_range2 != "-") {
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range1).c_str(), -1, SQLITE_TRANSIENT);
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range2).c_str(), -1, SQLITE_TRANSIENT);
        //         } else if (arrival_time_range1 != "-") {
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range1).c_str(), -1, SQLITE_TRANSIENT);
        //         } else if (arrival_time_range2 != "-") {
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range2).c_str(), -1, SQLITE_TRANSIENT);
        //         }

        //         if (gate != "-")
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(gate).c_str(), -1, SQLITE_TRANSIENT);

        //         if (status != "-")
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(status).c_str(), -1, SQLITE_TRANSIENT);

        //         if (aircraft_type != "-")
        //             sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(aircraft_type).c_str(), -1, SQLITE_TRANSIENT);

        //         // Выполняем запрос и сохраняем найденные записи
        //         while (sqlite3_step(stmt) == SQLITE_ROW) {
        //             dataAirport data;
        //             data.setId(sqlite3_column_int(stmt, 0));
        //             data.setDeparture_time(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        //             data.setArrival_time(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        //             data.setStatus(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        //             data.setAircraft_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        //             data.setAirline(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        //             data.setFlight(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        //             data.setDeparture_from(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        //             data.setDestination(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        //             data.setGate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
                    
        //             foundRecords.push_back(data);
        //         }
                

        //         sqlite3_finalize(stmt);
                
        //         // Проверяем, найдены ли записи
        //         if (foundRecords.empty()) {
        //             cout << "Записи не найдены." << endl;
        //             return;
        //         }
                
        //         // Выводим найденные записи
        //         cout << "Найдено " << foundRecords.size() << " записей:" << endl;

        //         cout << left 
        //             << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
        //         cout << "| " << left << setw(5) << "ID" 
        //             << " | " << left << setw(6) << "Рейс" 
        //             << " | " << left << setw(19) << "Авиакомпания" 
        //             << " | " << left << setw(16) << "Откуда вылет" 
        //             << " | " << left << setw(17) << "Пункт назначения"
        //             << " | " << left << setw(17) << "Вылет в" 
        //             << " | " << left << setw(17) << "Прибывает в" 
        //             << " | " << left << setw(4) << "Гейт" 
        //             << " | " << left << setw(14) << "Статус" 
        //             << " | " << left << setw(13) << "Тип BC" << " | " << endl;
        //         cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;


        //         for (size_t i = 0; i < foundRecords.size(); ++i) {
        //             cout << left << "| " << setw(6) << i + 1 << " ";
        //             foundRecords[i].output_convert();
        //         }

        //         cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
                
        //         // Предлагаем пользователю выбрать записи для удаления
        //         cout << "Введите номера записей, которые хотите удалить (через пробел), или '0' для отмены: ";
        //         string input;
        //         cin.ignore();
        //         getline(cin, input);
                
        //         if (input == "0") {
        //             cout << "Операция отменена." << endl;
        //             return;
        //         }
                
        //         // Парсим введенные номера
        //         istringstream iss(input);
        //         vector<int> selectedIndices;
        //         int index;
        //         while (iss >> index) {
        //             if (index >= 1 && index <= static_cast<int>(foundRecords.size())) {
        //                 selectedIndices.push_back(index);
        //             } else {
        //                 cout << "Неверный номер: " << index << ". Игнорируется." << endl;
        //             }
        //         }
                
        //         if (selectedIndices.empty()) {
        //             cout << "Не выбрано ни одной действительной записи. Операция отменена." << endl;
        //             return;
        //         }
        // }

        void deleteData()
        {

        inputData();
        // Сначала найдем записи, соответствующие критериям поиска
        vector<dataAirport> foundRecords;
        
        string sql = "SELECT * FROM flights WHERE 1=1";
        vector<string> conditions;

        // Добавляем условия для каждого параметра, если он не равен "-"
        if (flight != "-")
            conditions.push_back("flight = ?");

        if (airline != "-")
            conditions.push_back("airline = ?");

        if (departure_from != "-")
            conditions.push_back("departure_from = ?");

        if (destination != "-")
            conditions.push_back("destination = ?");

        if (departure_time_range1 != "-" && departure_time_range2 != "-")
            conditions.push_back("departure_time BETWEEN ? AND ?");
        else if (departure_time_range1 != "-")
            conditions.push_back("departure_time >= ?");
        else if (departure_time_range2 != "-")
            conditions.push_back("departure_time <= ?");

        if (arrival_time_range1 != "-" && arrival_time_range2 != "-")
            conditions.push_back("arrival_time BETWEEN ? AND ?");
        else if (arrival_time_range1 != "-")
            conditions.push_back("arrival_time >= ?");
        else if (arrival_time_range2 != "-")
            conditions.push_back("arrival_time <= ?");

        if (gate != "-")
            conditions.push_back("gate = ?");

        if (status != "-")
            conditions.push_back("status = ?");

        if (aircraft_type != "-")
            conditions.push_back("aircraft_type = ?");

        // Добавляем условия в SQL-запрос
        for (const auto& condition : conditions) {
            sql += " AND " + condition;
        }

        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
            cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
            return;
        }

        auto safe_convert_utf = [](const string& text) -> string {
            string utf8_text = convertTo_utf8(text);
            if (utf8_text.empty()) {
                cerr << "Error: " << text << endl;
                return "";
            }
            return utf8_text;
        };

        // Связываем параметры с запросом
        int paramIndex = 1;

        if (flight != "-")
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(flight).c_str(), -1, SQLITE_TRANSIENT);
        
        if (airline != "-")
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(airline).c_str(), -1, SQLITE_TRANSIENT);

        if (departure_from != "-")
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_from).c_str(), -1, SQLITE_TRANSIENT);

        if (destination != "-")
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(destination).c_str(), -1, SQLITE_TRANSIENT);

        if (departure_time_range1 != "-" && departure_time_range2 != "-") {
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range1).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range2).c_str(), -1, SQLITE_TRANSIENT);
        } else if (departure_time_range1 != "-") {
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range1).c_str(), -1, SQLITE_TRANSIENT);
        } else if (departure_time_range2 != "-") {
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range2).c_str(), -1, SQLITE_TRANSIENT);
        }

        if (arrival_time_range1 != "-" && arrival_time_range2 != "-") {
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range1).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range2).c_str(), -1, SQLITE_TRANSIENT);
        } else if (arrival_time_range1 != "-") {
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range1).c_str(), -1, SQLITE_TRANSIENT);
        } else if (arrival_time_range2 != "-") {
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range2).c_str(), -1, SQLITE_TRANSIENT);
        }

        if (gate != "-")
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(gate).c_str(), -1, SQLITE_TRANSIENT);

        if (status != "-")
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(status).c_str(), -1, SQLITE_TRANSIENT);

        if (aircraft_type != "-")
            sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(aircraft_type).c_str(), -1, SQLITE_TRANSIENT);

        // Выполняем запрос и сохраняем найденные записи
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            dataAirport data;
            data.setId(sqlite3_column_int(stmt, 0));
            data.setDeparture_time(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            data.setArrival_time(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            data.setStatus(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            data.setAircraft_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            data.setAirline(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            data.setFlight(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
            data.setDeparture_from(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
            data.setDestination(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
            data.setGate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
            
            foundRecords.push_back(data);
        }
        

        sqlite3_finalize(stmt);
        
        // Проверяем, найдены ли записи
        if (foundRecords.empty()) {
            cout << "Записи не найдены." << endl;
            return;
        }
        
        // Выводим найденные записи
        cout << "Найдено " << foundRecords.size() << " записей:" << endl;

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


        for (size_t i = 0; i < foundRecords.size(); ++i) {
            cout << left << "| " << setw(5) << i + 1 << " ";
            foundRecords[i].output_convert();
        }

        cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
        
        // Предлагаем пользователю выбрать записи для удаления
        cout << "Введите номера записей, которые хотите удалить (через пробел), или '0' для отмены: ";
        string input;
        cin.ignore();
        getline(cin, input);
        
        if (input == "0") {
            cout << "Операция отменена." << endl;
            return;
        }
        
        // Парсим введенные номера
        istringstream iss(input);
        vector<int> selectedIndices;
        int index;
        while (iss >> index) {
            if (index >= 1 && index <= static_cast<int>(foundRecords.size())) {
                selectedIndices.push_back(index);
            } else {
                cout << "Неверный номер: " << index << ". Игнорируется." << endl;
            }
        }
        
        if (selectedIndices.empty()) {
            cout << "Не выбрано ни одной действительной записи. Операция отменена." << endl;
            return;
        }
        
        // Запрашиваем подтверждение
        cout << "Вы собираетесь удалить " << selectedIndices.size() << " записей. Подтвердите удаление (y/n): ";
        cin.get();
        getline(cin, input);
        
        if (input != "y" && input != "Y") {
            cout << "Операция отменена." << endl;
            return;
        }
        
        // Удаляем выбранные записи
        int deletedCount = 0;
        for (int idx : selectedIndices) {
            int recordId = std::stoi(foundRecords[idx - 1].getId());
            
            string deleteSql = "DELETE FROM flights WHERE id = ?";
            sqlite3_stmt *deleteStmt;
            if (sqlite3_prepare_v2(db, deleteSql.c_str(), -1, &deleteStmt, 0) != SQLITE_OK) {
                cerr << "SQL error при подготовке запроса на удаление: " << sqlite3_errmsg(db) << endl;
                continue;
            }
            
            sqlite3_bind_int(deleteStmt, 1, recordId);
            
            if (sqlite3_step(deleteStmt) != SQLITE_DONE) {
                cerr << "SQL error при выполнении запроса на удаление: " << sqlite3_errmsg(db) << endl;
            } else {
                deletedCount++;
            }
            
            sqlite3_finalize(deleteStmt);
        }
        
        cout << "Удалено " << deletedCount << " из " << selectedIndices.size() << " выбранных записей." << endl;
    }

        void searchData()
        {
            inputData();

            dataAirport data;
            string sql = "SELECT * FROM flights WHERE 1=1";
            vector<string> conditions;

            // Добавляем условия для каждого параметра, если он не равен "-"
            if (flight != "-")
                conditions.push_back("flight = ?");

            if (airline != "-")
                conditions.push_back("airline = ?");

            if (departure_from != "-")
                conditions.push_back("departure_from = ?");

            if (destination != "-")
                conditions.push_back("destination = ?");

            if (departure_time_range1 != "-" && departure_time_range2 != "-")
                conditions.push_back("departure_time BETWEEN ? AND ?");
            else if (departure_time_range1 != "-")
                conditions.push_back("departure_time >= ?");
            else if (departure_time_range2 != "-")
                conditions.push_back("departure_time <= ?");

            if (arrival_time_range1 != "-" && arrival_time_range2 != "-")
                conditions.push_back("arrival_time BETWEEN ? AND ?");
            else if (arrival_time_range1 != "-")
                conditions.push_back("arrival_time >= ?");
            else if (arrival_time_range2 != "-")
                conditions.push_back("arrival_time <= ?");

            if (gate != "-")
                conditions.push_back("gate = ?");

            if (status != "-")
                conditions.push_back("status = ?");

            if (aircraft_type != "-")
                conditions.push_back("aircraft_type = ?");

            // Добавляем условия в SQL-запрос
            for (const auto& condition : conditions) {
                sql += " AND " + condition;
            }

            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
                cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
                return;
            }

            auto safe_convert_utf = [](const string& text) -> string {
                string utf8_text = convertTo_utf8(text);
                if (utf8_text.empty()) {
                    cerr << "Error: " << text << endl;
                    return "";
                }
                return utf8_text;
            };

            // Связываем параметры с запросом
            int paramIndex = 1;

            if (flight != "-")
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(flight).c_str(), -1, SQLITE_TRANSIENT);
            
                if (airline != "-")
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(airline).c_str(), -1, SQLITE_TRANSIENT);

            if (departure_from != "-")
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_from).c_str(), -1, SQLITE_TRANSIENT);

            if (destination != "-")
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(destination).c_str(), -1, SQLITE_TRANSIENT);

            if (departure_time_range1 != "-" && departure_time_range2 != "-") {
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range1).c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range2).c_str(), -1, SQLITE_TRANSIENT);
            } else if (departure_time_range1 != "-") {
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range1).c_str(), -1, SQLITE_TRANSIENT);
            } else if (departure_time_range2 != "-") {
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(departure_time_range2).c_str(), -1, SQLITE_TRANSIENT);
            }

            if (arrival_time_range1 != "-" && arrival_time_range2 != "-") {
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range1).c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range2).c_str(), -1, SQLITE_TRANSIENT);
            } else if (arrival_time_range1 != "-") {
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range1).c_str(), -1, SQLITE_TRANSIENT);
            } else if (arrival_time_range2 != "-") {
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(arrival_time_range2).c_str(), -1, SQLITE_TRANSIENT);
            }

            if (gate != "-")
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(gate).c_str(), -1, SQLITE_TRANSIENT);

            if (status != "-")
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(status).c_str(), -1, SQLITE_TRANSIENT);

            if (aircraft_type != "-")
                sqlite3_bind_text(stmt, paramIndex++, safe_convert_utf(aircraft_type).c_str(), -1, SQLITE_TRANSIENT);


                cout << left 
                << "+-----------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
                cout  << "| " << left << setw(6) << "Рейс" 
                << " | " << left << setw(19) << "Авиакомпания" 
                << " | " << left << setw(16) << "Откуда вылет" 
                << " | " << left << setw(17) << "Пункт назначения"
                << " | " << left << setw(17) << "Вылет в" 
                << " | " << left << setw(17) << "Прибывает в" 
                << " | " << left << setw(4) << "Гейт" 
                << " | " << left << setw(14) << "Статус" 
                << " | " << left << setw(13) << "Тип BC" << " | " << endl;
                cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            // Выполняем запрос и обрабатываем результаты
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                data.setId(sqlite3_column_int(stmt, 0));
                data.setDeparture_time(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                data.setArrival_time(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
                data.setStatus(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
                data.setAircraft_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
                data.setAirline(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
                data.setFlight(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
                data.setDeparture_from(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
                data.setDestination(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
                data.setGate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
                
                data.output_convert();
            }

            cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;

            sqlite3_finalize(stmt);
        }

        void getData()
        {

            dataAirport data;
            const char *sql = "SELECT * FROM flights";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
                std::cerr << "SQL error: " << sqlite3_errmsg(db)
                        << std::endl;
                return;
            }

            cout << left 
            << "+-----------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout  << "| " << left << setw(6) << "Рейс" 
            << " | " << left << setw(19) << "Авиакомпания" 
            << " | " << left << setw(16) << "Откуда вылет" 
            << " | " << left << setw(17) << "Пункт назначения"
            << " | " << left << setw(17) << "Вылет в" 
            << " | " << left << setw(17) << "Прибывает в" 
            << " | " << left << setw(4) << "Гейт" 
            << " | " << left << setw(14) << "Статус" 
            << " | " << left << setw(13) << "Тип BC" << " | " << endl;
            cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;


            while (sqlite3_step(stmt) == SQLITE_ROW) {
                data.setId(sqlite3_column_int(stmt, 0));
                data.setDeparture_time(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                data.setArrival_time(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
                data.setStatus(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
                data.setAircraft_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
                data.setAirline(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
                data.setFlight(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
                data.setDeparture_from(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
                data.setDestination(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
                data.setGate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));

                data.output_convert();
            }

            cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;
            sqlite3_finalize(stmt);
        }
        
        void close_database()
        {
            sqlite3_close(db);
        }
    };

#endif