#include "../include/operations.h"

int insert_operation(sqlite3 *db, int patient_id, const char *description,
                     const char *date) {
  const char *sql =
      "INSERT INTO operations (patient_id ,description,date) VALUES (?,?,?);";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }
  if ((rc = sqlite3_bind_int(stmt, 1, patient_id)) != SQLITE_OK ||
      (rc = sqlite3_bind_text(stmt, 2, description, -1, SQLITE_STATIC)) !=
          SQLITE_OK ||
      (rc = sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC)) != SQLITE_OK) {
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

int get_operations_by_patient(sqlite3 *db, int patient_id);
