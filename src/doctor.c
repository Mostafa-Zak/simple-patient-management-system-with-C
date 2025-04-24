#include "../include/doctor.h"

int get_all_doctors(sqlite3 *db, Doctor **doctors, int *count) {
  const char *sql = "SELECT id, name FROM doctors;";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return rc;
  }

  int capacity = 10;
  *doctors = malloc(capacity * sizeof(Doctor));
  if (*doctors == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    sqlite3_finalize(stmt);
    return 1;
  }

  *count = 0;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    if (*count >= capacity) {
      capacity *= 2;
      *doctors = realloc(*doctors, capacity * sizeof(Doctor));
      if (*doctors == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        sqlite3_finalize(stmt);
        return 1;
      }
    }

    (*doctors)[*count].id = sqlite3_column_int(stmt, 0);
    strncpy((*doctors)[*count].name, (const char *)sqlite3_column_text(stmt, 1),
            sizeof((*doctors)[*count].name));
    (*count)++;
  }

  sqlite3_finalize(stmt);
  return SQLITE_OK;
}

int insert_doctor(sqlite3 *db, const char *name) {
  const char *sql = "INSERT INTO doctors (name) VALUES (?);";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }
  rc = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
  if (rc != SQLITE_OK) {
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
};
