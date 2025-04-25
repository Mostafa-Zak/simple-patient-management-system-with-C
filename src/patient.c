#include "../include/patient.h"
#include <string.h>

int insert_patient(sqlite3 *db, const char *name, int age, int doctor_id,
                   int status) {

  const char *sql =
      "INSERT INTO patients (name,age,doctor_id,status) VALUES (?,?,?,?);";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }
  if ((rc = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC)) != SQLITE_OK ||
      (rc = sqlite3_bind_int(stmt, 2, age)) != SQLITE_OK ||
      (rc = sqlite3_bind_int(stmt, 3, doctor_id)) != SQLITE_OK ||
      (rc = sqlite3_bind_int(stmt, 4, status)) != SQLITE_OK) {
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

int get_all_patients(sqlite3 *db, Patient **patients, int *count) {
  const char *sql = "SELECT id, name FROM patients;";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return rc;
  }

  int capacity = 10;
  *patients = malloc(capacity * sizeof(Patient));
  if (*patients == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    sqlite3_finalize(stmt);
    return 1;
  }

  *count = 0;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    if (*count >= capacity) {
      capacity *= 2;
      *patients = realloc(*patients, capacity * sizeof(Patient));
      if (*patients == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        sqlite3_finalize(stmt);
        return 1;
      }
    }

    (*patients)[*count].id = sqlite3_column_int(stmt, 0);
    strncpy((*patients)[*count].name,
            (const char *)sqlite3_column_text(stmt, 1),
            sizeof((*patients)[*count].name));
    (*count)++;
  }

  sqlite3_finalize(stmt);
  return SQLITE_OK;
}

int get_patient_by_id(sqlite3 *db, int id, Patient *patient) {
  const char *sql = "SELECT * FROM patients WHERE id = ?";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return rc;
  }
  rc = sqlite3_bind_int(stmt, 1, id);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to bind statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW) {
    patient->id = sqlite3_column_int(stmt, 0);
    strncpy(patient->name, (const char *)sqlite3_column_text(stmt, 1),
            sizeof(patient->name) - 1);

    patient->age = sqlite3_column_int(stmt, 2),
    patient->status = sqlite3_column_int(stmt, 4),
    patient->name[sizeof(patient->name) - 1] = '\0';

  } else {
    fprintf(stderr, "No patient found with ID %d\n", id);
    sqlite3_finalize(stmt);
    return rc;
  }

  sqlite3_finalize(stmt);

  return SQLITE_OK;
}

int delete_all_patients(sqlite3 *db) {
  const char *sql = "DELETE FROM patients";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare DELETE ALL: %s\n", sqlite3_errmsg(db));
    return rc;
  }

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "DELETE ALL failed: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }

  int count = sqlite3_changes(db);
  sqlite3_finalize(stmt);
  return count;
}

int delete_patient_by_id(sqlite3 *db, int id) {
  const char *sql = "DELETE FROM patients WHERE id = ?";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare DELETE BY ID: %s\n", sqlite3_errmsg(db));
    return rc;
  }

  rc = sqlite3_bind_int(stmt, 1, id);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to bind ID %d: %s\n", id, sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "No patient deleted for ID %d: %s\n", id,
            sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }
  return SQLITE_OK;
}
