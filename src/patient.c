#include "../include/patient.h"

int insert_patient(sqlite3 *db, const char *name, int age, int doctor_id) {

  const char *sql = "INSERT INTO patients (name,age,doctor_id) VALUES (?,?,?);";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }
  if ((rc = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC)) != SQLITE_OK ||
      (rc = sqlite3_bind_int(stmt, 2, age)) != SQLITE_OK ||
      (rc = sqlite3_bind_int(stmt, 3, doctor_id)) != SQLITE_OK) {
    fprintf(stderr, "Couldn't bind to prepared sql stmt: %s\n",
            sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }
  sqlite3_finalize(stmt);
  return 0;
}

int get_all_patients(sqlite3 *db, Patient **patients, int *count);
int get_patient_by_id(sqlite3 *db, int id, Patient *patient);
