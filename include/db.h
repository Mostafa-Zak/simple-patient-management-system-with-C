#ifndef DB_H
#define DB_H

#include <sqlite3.h>

int init_db(sqlite3 **db);

int create_tables(sqlite3 *db);

int insert_doctor(sqlite3 *db, const char *name, const char *specialization);

int insert_patient(sqlite3 *db, const char *name, int age, int doctor_id);

int insert_operation(sqlite3 *db, int patient_id, const char *description, const char *date);

int fetch_doctors(sqlite3 *db);

void close_db(sqlite3 *db);
#endif
