#ifndef DB_H
#define DB_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>


int init_db(sqlite3 **db);
int create_tables(sqlite3 *db);
void close_db(sqlite3 *db);
#endif
