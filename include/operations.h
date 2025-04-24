
#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <sqlite3.h>

#include <stdio.h>
#include <stdlib.h>


int insert_operation(sqlite3 *db, int patient_id, const char *description, const char *date);
int get_operations_by_patient(sqlite3 *db, int patient_id);

#endif
