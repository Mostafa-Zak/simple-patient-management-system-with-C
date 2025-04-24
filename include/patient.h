
#ifndef PATIENT_H
#define PATIENT_H


#include <sqlite3.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char name[100];
  int age;
  int status;
  int doctor_id;
} Patient;

int insert_patient(sqlite3 *db, const char *name, int age, int doctor_id,int status);
int get_all_patients(sqlite3 *db, Patient **patients, int *count);
int get_patient_by_id(sqlite3 *db, int id, Patient *patient);

#endif
