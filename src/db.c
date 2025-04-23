#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

int init_db(sqlite3 **db) {
  int rc = sqlite3_open("../data/PMS.db", db);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    sqlite3_close(*db);
    return rc;
  }
  return 0;
}

int create_tables(sqlite3 *db) {

  FILE *file;
  long file_size;
  char *sql_buffer;
  // Open the SQL schema file
  file = fopen("../sql/init.sql", "r");
  if (!file) {
    fprintf(stderr, "Cannot open schema file: %s\n", "init.sql");
    sqlite3_close(db);
    return 1;
  }

  // Get file size
  fseek(file, 0, SEEK_END);
  file_size = ftell(file);
  rewind(file);
  // Allocate memory for the entire file
  sql_buffer = (char *)malloc(file_size + 1);
  if (!sql_buffer) {
    fprintf(stderr, "Memory allocation error\n");
    fclose(file);
    return 1;
  }
  // Read the entire file
  size_t bytes_read = fread(sql_buffer, 1, (size_t)file_size, file);
  if (bytes_read != (size_t)file_size) {
    fprintf(stderr, "Error reading file\n");
    free(sql_buffer);
    fclose(file);
    return 1;
  } // Null-terminate the buffer
  sql_buffer[file_size] = '\0';
  // Execute the SQL statements
  char *errmsg = NULL;
  int rc = sqlite3_exec(db, sql_buffer, NULL, NULL, &errmsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", errmsg);
    sqlite3_free(errmsg);
    free(sql_buffer);
    return 1;
  }
  // Clean up
  free(sql_buffer);
  fclose(file);
  return 0;
};

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

int fetch_doctors(sqlite3 *db) {
  const char *sql = "SELECT * FROM doctors;";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return rc;
  }
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    printf("Doctor ID: %d, Name: %s\n", sqlite3_column_int(stmt, 0),
           sqlite3_column_text(stmt, 1));
  }
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return rc;
  }

  sqlite3_finalize(stmt);

  return 0;
};

void close_db(sqlite3 *db) { sqlite3_close(db); }
