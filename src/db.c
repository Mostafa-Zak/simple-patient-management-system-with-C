#include "../include/db.h"

// config.h
#define DB_PATH "data/PMS.db"
#define INIT_SQL_PATH "sql/init.sql"

int init_db(sqlite3 **db) {
  int rc = sqlite3_open(DB_PATH, db);
  if (rc != SQLITE_OK) {
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
  file = fopen(INIT_SQL_PATH, "r");
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
// TODO: some basic functions to retrieve data from data base
void close_db(sqlite3 *db) { sqlite3_close(db); }
