#include "../include/db.h"
#include "../include/doctor.h"
#include "../include/ds.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
  Doctor *doctors = NULL;
  while (!shouldQuit) {
    printf("\n--- Main Menu ---\n");
    printf("(n) Add new doctor\n");
    printf("(m) Manage existing doctor\n");
    printf("(s) Show all patients\n");
    printf("(q) Quit\n");
    char input = getchar();
    while (getchar() != '\n')
      ; // Clear the input buffer
    switch (input) {
    case 'q':
      return 0;
    case 'n': {
      const char *name = getInput("write doctor name: ");
      printf("name is: %s\n", name);
      insert_doctor(db, name);
    } break;
    case 'm': {
    } break;
    case 's': {
      char *viewChoice =
          getInput("Show (c) completed, (i) incomplete, (a) all: ");
      int doctor_count = 0;
      if (get_all_doctors(db, &doctors, &doctor_count) == SQLITE_OK) {
        for (int i = 0; i < doctor_count; i++) {
          printf("Doctor ID: %d, Name: %s\n", doctors[i].id, doctors[i].name);
        }
        free(viewChoice);
        close_db(db);
      }
    } break;
    default:
      printf("Invalid input!\n");
      break;
    }
  }
  return 0;
}
