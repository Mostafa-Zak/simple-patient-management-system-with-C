
#ifndef DOCTOR_H
#define DOCTOR_H

#include <sqlite3.h>
#include <sqlite3.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  int id;
  char name[100];
} Doctor;

int get_all_doctors(sqlite3 *db, Doctor **doctors, int *count);
int insert_doctor(sqlite3 *db, const char *name);
int get_doctor_by_id(sqlite3 *db, int id, Doctor *doctor);

#endif
