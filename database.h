#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "sqlite3.h"
#include "airport.h"

class database_airport
    {
    private:
     sqlite3 *db;
     char *errMsg = 0;

    public:
        database_airport()
        {
            if (sqlite3_open("data.db", &db)) {
                std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
                exit(1);
            }

            if ()
        }

        void create_table()
        {
            const char *sql = "CREATE TABLE IF NOT EXISTS flights (id INTEGER PRIMARY KEY, terminal INTEGER, bagBelt INTEGER, departute_time DATETIME, arrival_time DATETIME, status TEXT, aircraft_type TEXT, airline TEXT, flight TEXT, departure_from TEXT, destination TEXT, gate TEXT);";
            if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            } else {
                std::cout << "Table created successfully!" << std::endl;
            }
        }

        // void insert_airport(dataAirport airport)
        // {
        //             const char *insert_sql = "INSERT INTO flights (terminal, bagBelt, departute_time, arrival_time, status, aircraft_type, airline, flight, departure_from, destination, gate) VALUES (?,?,?,?,?,?,?,?,?,?,?);";
        //     if (sqlite3_exec(db, insert_sql, 0, 0, &errMsg) != SQLITE_OK) {
        //         std::cerr << "SQL error: " << errMsg << std::endl;
        //         sqlite3_free(errMsg);
        //     } else {
        //         std::cout << "Data inserted successfully!" << std::endl;
        //     }
        // }

        void input_airport(dataAirport airport)
        {   
            const char *input_sql = "INSERT INTO flights (terminal, bagBelt, departute_time, arrival_time, status, aircraft_type, airline, flight, departure_from, destination, gate) VALUES (?,?,?,?,?,?,?,?,?,?,?);";
        }
        
        void update_airport(dataAirport airport)
        {
            const char *update_sql = "UPDATE flights SET terminal=?, bagBelt=?, departute_time=?, arrival_time=?, status=?, aircraft_type=?, airline=?, flight=?, departure_from=?, destination=?, gate=? WHERE id=?;";
            if (sqlite3_exec(db, update_sql, 0, 0, &errMsg) != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            } else {
                std::cout << "Data updated successfully!" << std::endl;
            }
        }

        void delete_airport(int id)
        {
            const char *delete_sql = "DELETE FROM flights WHERE id=?;";
            if (sqlite3_exec(db, delete_sql, 0, 0, &errMsg) != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            } else {
                std::cout << "Data deleted successfully!" << std::endl;
            }
        }

        // void find_airport(int id)
        // {
        //     const char *select_sql = "SELECT * FROM flights WHERE id=?;";
        //     sqlite3_stmt *stmt;
        //     if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0) != SQLITE_OK) {
        //         std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        //         return;
        //     }
        //     sqlite3_bind_int(stmt, 1, id);
        //     int rc = sqlite3_step(stmt);
        //     if (rc == SQLITE_ROW) {
        //         dataAirport airport;

        void output_airport()
        {
            const char *select_sql = "SELECT * FROM flights;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0) != SQLITE_OK) {
                std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
                return;
            }
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                int terminal = sqlite3_column_int(stmt, 1);
                int bagBelt = sqlite3_column_int(stmt, 2);
                const char *departute_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                const char *arrival_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
                const char *status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
                const char *aircraft_type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
                const char *airline = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
                const char *flight = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
                const char *departure_from = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
                const char *destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
                const char *gate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11));

                cout << left << setw(10) << id << setw(10) << terminal << setw(10) << bagBelt << setw(20) << departute_time << setw(20) << arrival_time << setw(10) << status << setw(20) << aircraft_type << setw(20) << airline << setw(20) << flight << setw(20) << departure_from << setw(20) << destination << setw(20) << gate << endl;
            }
            sqlite3_finalize(stmt);
        }
        
        void close_database()
        {
            sqlite3_close(db);

        }
    };

#endif