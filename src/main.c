#include "../include/db.h"
#include "../include/doctor.h"
#include "../include/patient.h"
#include "../include/utils.h"
#include "sqlite3.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {

  // TODO: render ui here

  printf("if you want to quit press(q): \n");
  printf("for adding patient type (d): \n");
  bool shouldQuit = false;
  sqlite3 *db;
  init_db(&db);
  create_tables(db);
  while (!shouldQuit) {
    printf("\n--- Main Menu ---\n");
    printf("(n) Add new doctor\n");
    printf("(m) Manage existing doctor\n");
    printf("(s) Show all patients\n");
    printf("(q) Quit\n");
    char input[10];
    if (fgets(input, sizeof(input), stdin) == NULL) {
      printf("Input error!\n");
      continue;
    };
    switch (input[0]) {
    case 'q':
      close_db(db);
      return 0;
    case 'n': {
      const char *name = getInput("write doctor name: \n");
      int doctor_id = insert_doctor(db, name);
      const char *pName = getInput("write patient name: \n");
      int age = atoi(getInput("write patient age: "));
      insert_patient(db, pName, age, doctor_id, 0);
    } break;
    case 'm': {
      // const char *name = getInput("write doctor name: \n");

    } break;
    case 's': {
      char *viewChoice = getInput("(D)octor, (P)atients\n");
      if (strcmp(viewChoice, "d") == 0) {
        Doctor *doctors = NULL;
        int doctor_count = 0;
        viewChoice = getInput(
            "press (a) to get all patients and (i)to get patient by id\n");

        if (strcmp(viewChoice, "a") == 0) {
          if (get_all_doctors(db, &doctors, &doctor_count) == SQLITE_OK) {
            for (int i = 0; i < doctor_count; i++) {
              printf("Doctor ID: %d, Name: %s\n", doctors[i].id,
                     doctors[i].name);
            }

            free(doctors);
          }
        } else if (strcmp(viewChoice, "i") == 0) {
          int id = atoi(getInput("write doctor id: \n"));
          Doctor doctor;
          if (get_doctor_by_id(db, id, &doctor) == SQLITE_OK) {

            printf("Doctor ID: %d, Name: %s\n", doctor.id, doctor.name);
          }
        }

      } else if (strcmp(viewChoice, "p") == 0) {
        viewChoice = getInput(
            "press (a) to get all patients and (i)to get patient by id\n");
        if (strcmp(viewChoice, "a") == 0) {
          Patient *patients = NULL;
          int patient_count = 0;

          if (get_all_patients(db, &patients, &patient_count) == SQLITE_OK) {
            for (int i = 0; i < patient_count; i++) {
              printf("patient ID: %d, Name: %s\n", patients[i].id,
                     patients[i].name);
            }
            free(patients);
          }
        } else if (strcmp(viewChoice, "i") == 0) {
          int id = atoi(getInput("write patient id: \n"));
          Patient patient;
          if (get_patient_by_id(db, id, &patient) == SQLITE_OK) {

            printf("patient ID: %d, Name: %s, Age: %d\n", patient.id,
                   patient.name, patient.age);
          }
        }
      }
    } break;
    default:
      printf("Invalid input!\n");
      break;
    }
  }
  close_db(db);
  return 0;
}
