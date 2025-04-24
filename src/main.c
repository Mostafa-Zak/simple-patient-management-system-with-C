#include "../include/db.h"
#include "../include/doctor.h"
#include "../include/ds.h"
#include "../include/patient.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include "raylib.h"
#include "sqlite3.h"
/*#define RAYGUI_IMPLEMENTATION*/
/*#include "raygui.h"*/
/*#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui
 * implementation again*/

#define SIZEOF(A) (sizeof(A) / sizeof(A[0]))
int main(void) {

  // TODO: render ui here

  /*const int screenWidth = 800;*/
  /*const int screenHeight = 450;*/

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
      const char *name = getInput("write doctor name: ");
      int doctor_id = insert_doctor(db, name);
      const char *pName = getInput("write patient name: ");
      int age = atoi(getInput("write patient age: "));
      insert_patient(db, pName, age, doctor_id, 0);
    } break;
    case 'm': {
      const char *name = getInput("write doctor name: ");

    } break;
    case 's': {
      char *viewChoice = getInput("(D)octor, (P)atients");
      if (strcmp(viewChoice, "d") == 0) {
        Doctor *doctors = NULL;
        int doctor_count = 0;
        if (get_all_doctors(db, &doctors, &doctor_count) == SQLITE_OK) {
          for (int i = 0; i < doctor_count; i++) {
            printf("Doctor ID: %d, Name: %s\n", doctors[i].id, doctors[i].name);
          }

          free(doctors);
        }
      } else if (strcmp(viewChoice, "p") == 0) {
        Patient *patients = NULL;
        int patient_count = 0;
        if (get_all_patients(db, &patients, &patient_count) == SQLITE_OK) {
          for (int i = 0; i < patient_count; i++) {
            printf("Doctor ID: %d, Name: %s\n", patients[i].id,
                   patients[i].name);
          }
          free(patients);
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
