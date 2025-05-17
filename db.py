import sqlite3
from pathlib import Path
from airport import dataAirport as airp
from utils import table_header as header
from utils import table_footer as footer
from utils import displayFoundRecords as dfr
from utils import gotoxy
from utils import pause
from datetime import datetime
from os import system



class airportDB:
    def __init__(self):
        self.db_path = Path('data/data.db')
        self.db_path.parent.mkdir(parents=True, exist_ok=True)
        self.ap = airp()

        db_exists = self.db_path.exists()

        self.conn = sqlite3.connect(self.db_path)

        # Create tables if the database did not exist
        if not db_exists:
            self.create_tables()



    def create_tables(self):
        cursor = self.conn.cursor()
        cursor.execute('''
                   CREATE TABLE IF NOT EXISTS flights 
                    (id INTEGER PRIMARY KEY, 
                     departure_time DATETIME NOT NULL,
                     arrival_time DATETIME NOT NULL,
                     status TEXT NOT NULL,
                     aircraft_type TEXT NOT NULL, 
                     airline TEXT NOT NULL, 
                     flight TEXT NOT NULL, 
                     departure_from TEXT NOT NULL, 
                     destination TEXT NOT NULL, 
                     gate TEXT NOT NULL);
               ''')

        self.conn.commit()
        cursor.close()

    def getData(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT * FROM flights")

        rows = cursor.fetchall()

        header()

        for row in rows:
            self.ap.departure_time = row[1]
            self.ap.arrival_time = row[2]
            self.ap.status = row[3]
            self.ap.aircraft_type = row[4]
            self.ap.airline = row[5]
            self.ap.flight = row[6]
            self.ap.departure_from = row[7]
            self.ap.destination = row[8]
            self.ap.gate = row[9]


            self.ap.output()
            footer()

            cursor.close()

    def addData(self, count : int):
        header()
        self.ap.input(count)
        footer()

        cursor = self.conn.cursor()
        cursor.execute("INSERT INTO flights (departure_time, arrival_time, status, aircraft_type, airline, flight, departure_from, destination, gate) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)",
                       (self.ap.departure_time, self.ap.arrival_time, self.ap.status, self.ap.aircraft_type, self.ap.airline, self.ap.flight, self.ap.departure_from, self.ap.destination, self.ap.gate,))

        self.conn.commit()
        cursor.close()

    def SearchBuildQuery(self):

        print("+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+")
        print(f"| {"Рейс":6} | {"Авиакомпания":19} | {"Откуда вылет":16} | {"Пункт назначения":17} | {"Вылет в (от)":17} | {"Вылет в (до)":17} | {"Прибывает в (от)":17} | {"Прибывает в (до)":17} | {"Гейт":4} | {"Статус":14} | {"Тип BC":10} |")
        print("+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+ ")

        gotoxy(0, 4); print("| ", end=""); flight = input()
        gotoxy(9, 4); print("| ", end=""); airline = input()
        gotoxy(31, 4); print("| ", end=""); departure_from = input()
        gotoxy(50, 4); print("| ", end=""); destination = input()
        gotoxy(70, 4); print("| ", end=""); departure_time_range1 = input()
        gotoxy(90, 4); print("| ", end=""); departure_time_range2 = input()
        gotoxy(110, 4); print("| ", end=""); arrival_time_range1 = input()
        gotoxy(130, 4); print("| ", end=""); arrival_time_range2 = input()
        gotoxy(150, 4); print("| ", end=""); gate = input()
        gotoxy(157, 4); print("| ", end=""); status = input()
        gotoxy(174, 4); print("| ", end=""); aircraft_type = input()
        gotoxy(187, 4); print("| ")
        print("+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+")

        sql = "SELECT * FROM flights WHERE 1=1"
        conditions = []

        if (flight != "-"): conditions.append(f"flight LIKE '%' ? '%'", (flight,))6

        if (airline != "-"): conditions.append(f"airline LIKE '%' {airline} '%'")
        if (departure_from != "-"): conditions.append(f"departure_from LIKE '%' {departure_from} '%'")
        if (destination != "-"): conditions.append(f"destination LIKE '%' {destination} '%'")
        if (departure_time_range1 != "-" and departure_time_range2 != "-"): conditions.append(f"departure_time BETWEEN  {departure_time_range1} AND {departure_time_range2}")
        if (departure_time_range1 != "-"): conditions.append(f"departure_time_range2 >={departure_time_range1}")
        if (departure_time_range1 != "-"): conditions.append(f"departure_time <= {departure_time_range2}")
        if (arrival_time_range1 != "-" and arrival_time_range2 != "-"): conditions.append(f"arrival_time BETWEEN  {arrival_time_range1} AND {arrival_time_range2}")
        if (arrival_time_range1 != "-"): conditions.append(f"arrival_time >= {arrival_time_range1}")
        if (arrival_time_range2 != "-"): conditions.append(f"arrival_time <= {arrival_time_range2}")
        if (gate != "-"): conditions.append(f"gate LIKE '%' {gate} '%'")
        if (status != "-"): conditions.append(f"status LIKE '%' {status} '%'")
        if (aircraft_type != "-"): conditions.append(f"aircraft_type LIKE '%' {aircraft_type} '%'")

        for condition in conditions:
            sql+= " AND " + condition

        cursor = self.conn.cursor()
        print(sql)
        cursor.execute(sql)

        foundRecords = []

        rows = cursor.fetchall()
        for row in rows:
            self.ap.id = row[0]
            self.ap.departure_time = row[1]
            self.ap.arrival_time = row[2]
            self.ap.status = row[3]
            self.ap.aircraft_type = row[4]
            self.ap.airline = row[5]
            self.ap.flight = row[6]
            self.ap.departure_from = row[7]
            self.ap.destination = row[8]
            self.ap.gate = row[9]

            foundRecords.append(self.ap)
            cursor.close()

        return foundRecords

    def searchData(self):
        foundRecords = self.SearchBuildQuery()
        if not foundRecords: print("Записи не были найдены."); return
        dfr(foundRecords)
        pause()

    def deleteData(self):
        foundRecords = self.SearchBuildQuery()
        if not foundRecords: print("Записи не были найдены."); return
        dfr(foundRecords)
        if not foundRecords: return

        user_input = input("Введите номера записей, которые хотите удалить (через пробел), или 0 для отмены: ")
        user_input = user_input.strip()
        if user_input == "" or user_input == "0": print("Операция отменена."); return

        selected_indices = []
        for index_str in user_input.split():
            try:
                index = int(index_str)
                if 1 <= index <= len(foundRecords):
                    selected_indices.append(index)
                else:
                    print(f"Неверный номер: {index}. Игнорируется")

            except ValueError:
                print(f"Неверный форат: {index_str}. Игнорируется")

        deleted_count = 0
        cursor = self.conn.cursor()

        for idx in selected_indices:
            record_id = int(foundRecords[idx - 1].getId())

            try:
                cursor.execute("DELETE FROM flights WHERE id = ?", (record_id,))
                deleted_count += 1

            except sqlite3.Error as e:
                print(f"Ошибка SQL: {e}")

        self.conn.commit()
        cursor.close()

        print(f"Удалено записей: {deleted_count} из {len(selected_indices)} выбранных записей")
        pause()

    def updateData(self):
        foundRecords = self.SearchBuildQuery()
        if not foundRecords: print("Записи не были найдены."); return
        dfr(foundRecords)
        if not foundRecords: return

        user_input = int(input("Введите номер записи, которую хотите удалить, или 0 для отмены: "))
        try:
            if user_input == 0: print("Операция отменена."); return; pause()

        except TypeError: print("Операция отменена."); return; pause()

        cursor = self.conn.cursor()
        record_id = int(foundRecords[user_input - 1].getID())

        temp_airport = airp
        header()
        temp_airport.input()
        footer()

        try:
            cursor.execute("""UPDATE flights SET flights (departure_time = ?, arrival_time = ?, status = ?, 
                                                            aircraft_type = ?, airline = ?, flight = ?,
                                                            departure_from = ?, destination = ?, gate = ?,
                           "                                departure_time = ?, arrival_time = ?) WHERE id = ? """,
                                                            (temp_airport.getDeparture_from(), temp_airport.getArrival_time(), temp_airport.getStatus(),
                                                             temp_airport.getAircraft_type(), temp_airport.getAirline(), temp_airport.getFlight(),
                                                             temp_airport.getDeparture_from(), temp_airport.getDestination(), temp_airport.getGate(),
                                                             temp_airport.getDeparture_time(), temp_airport.getArrival_time(), record_id,))

            self.conn.commit()

            print(f"\n\nЗапись успешно изменена.")


        except sqlite3.Error as e: print(f"Ошибка SQL: {e}")
        finally: cursor.close()


        pause()

    def close_db(self):
        self.conn.close()