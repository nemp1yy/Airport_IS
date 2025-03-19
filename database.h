#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include "sqlite3.h"
#include "airport.h"
#include "utils.h"

class database_airport
    {
    private:
     sqlite3 *db;
     char *errMsg = 0;

    public:
        database_airport()
        {
            if (sqlite3_open("data.db", &db)) {
                cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
                exit(1);
            }


        }

        void create_table()
        {
            const char *sql = "CREATE TABLE IF NOT EXISTS flights (id INTEGER PRIMARY KEY, departure_time DATETIME NOT NULL, arrival_time DATETIME NOT NULL, status TEXT NOT NULL, aircraft_type TEXT NOT NULL, airline TEXT NOT NULL, flight TEXT NOT NULL, departure_from TEXT NOT NULL, destination TEXT NOT NULL, gate TEXT NOT NULL);";
            if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            } else {
                std::cout << "Table created successfully!" << std::endl;
            }
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
        
        
        bool updateData(dataAirport flight, int id)
        {
            const char *sql = "UPDATE flights SET, departute_time=?, arrival_time=?, status=?, aircraft_type=?, airline=?, flight=?, departure_from=?, destination=?, gate=? WHERE id=?;";

            sqlite3_stmt* stmt;
            int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
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

        void deleteData(int id)
        {
            const char *sql = "DELETE FROM flights WHERE id=?";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
                cerr << "SQL error: " << sqlite3_errmsg(db)
                        << std::endl;
                return;
            }

            sqlite3_bind_int(stmt, 1, id);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }

        void searchData(string flight = "-", string airline = "-", string departure_from = "-", 
            string destination = "-", string departure_time_range1 = "-", 
            string departure_time_range2 = "-", string arrival_time_range1 = "-", 
            string arrival_time_range2 = "-", string gate = "-", string status = "-", 
            string aircraft_type = "-")
{
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
            sqlite3_finalize(stmt);
        }
        
        void close_database()
        {
            sqlite3_close(db);
        }
    };

#endif