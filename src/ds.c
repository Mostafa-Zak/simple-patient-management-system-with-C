#include "../include/ds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initArray(dArray *a, size_t initialSize, size_t elementSize) {
  a->array = malloc(initialSize * elementSize);
  a->used = 0;
  a->size = initialSize;
  a->elementSize = elementSize;
}

void insertArray(dArray *a, void *element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * a->elementSize);
  }
  void *target = (char *)a->array + (a->used * a->elementSize);
  memcpy(target, element, a->elementSize);
  a->used++;
}

void freeArray(dArray *a) {
  free(a->array);
  a->array = NULL;
  a->size = a->used = a->elementSize = 0;
}

char *userInput() {
  char *input = malloc(50);
  fgets(input, 50, stdin);
  input[strcspn(input, "\n")] = 0; // remove newline
  return input;
};

char *getInput(const char *prompt) {
  printf("%s", prompt); // Show user what to do
  return userInput();   // Get their input and return it
}

void addOp(dArray *ops) {
  while (true) {
    char *input = getInput(
        "Type operation name (or type 'p' to stop adding operations):\n");
    if (strcmp(input, "p") == 0) {
      free(input);
      break;
    }
    op new_op;
    new_op.status = false;
    strcpy(new_op.name, input); // here for adding op name
    free(input);
    if (strcmp(new_op.name, "endo") == 0 || strcmp(new_op.name, "resto") == 0) {
      input = getInput("what is the stage: \n");
      strcpy(new_op.stage, input); // here for adding op stage
      if (strcmp(input, "final restoration") == 0) {
        new_op.status = true;
      }
      free(input);
    } else {
      new_op.status = true;
    };
    insertArray(ops, &new_op);
    printf("operation added!\n");
    //----------------------
  }
}

void addPatient(dArray *patients) {
  char *input = getInput("Enter patient name: \n");
  patient p;
  strcpy(p.name, input);
  dArray ops;
  initArray(&ops, 2, sizeof(op));
  addOp(&ops);
  op *opsList = (op *)ops.array;

  p.status = true;
  for (size_t i = 0; i < ops.used; i++) {
    if (!opsList[i].status) {
      p.status = false;
      break;
    }
  }
  p.ops.array = ops.array;
  p.ops.used = ops.used;
  p.ops.size = ops.size;
  p.ops.elementSize = ops.elementSize;
  ops.array = NULL;
  ops.used = 0;
  ops.size = 0;
  insertArray(patients, &p);
}

void addDoctor(dArray *doctors) {
  char *input = getInput("write doctor name: \n");
  doctor d;
  strcpy(d.name, input);
  free(input);
  dArray patients;
  initArray(&patients, 3, sizeof(patient));
  char continueAdding = 'y';
  while (continueAdding == 'y') {
    addPatient(&patients);
    input = getInput("Add another patient? (y/n): ");
    continueAdding = input[0];
    free(input);
  }

  d.patients.array = patients.array;
  d.patients.used = patients.used;
  d.patients.size = patients.size;
  d.patients.elementSize = patients.elementSize;
  patients.array = NULL;
  patients.used = 0;
  patients.size = 0;
  insertArray(doctors, &d);
}

void printPatients(char *input, dArray doctors) {
  doctor *dList = (doctor *)doctors.array;

  // Loop through all doctors
  for (size_t i = 0; i < doctors.used; i++) {
    patient *pList = (patient *)dList[i].patients.array;
    printf("-----------------------------------------\n");
    printf("[Doctor: %s]\n", dList[i].name);
    printf("{total number of patients performed: %zu}\n",
           dList[i].patients.used);
    printf("-----------------------------------------\n");
    // Loop through all patients for current doctor
    for (size_t j = 0; j < dList[i].patients.used; j++) {
      bool shouldPrint = false;

      // Filter based on input:
      // 'a' - all patients
      // 'c' - only completed patients (status == true)
      // 'i' - only incomplete patients (status == false)
      if (strcmp(input, "a") == 0)
        shouldPrint = true;
      else if (strcmp(input, "c") == 0 && pList[j].status)
        shouldPrint = true;
      else if (strcmp(input, "i") == 0 && !pList[j].status)
        shouldPrint = true;

      if (shouldPrint) {
        printf("> Patient %zu: %s\n", j + 1, pList[j].name);
        op *opsList = (op *)pList[j].ops.array;
        for (size_t r = 0; r < pList[j].ops.used; r++) {
          printf("> Operation %zu: %s\n", r + 1, opsList[r].name);
        }
        printf("---------------------------------------\n");
        printf("\n");
      }
    }
  }
}
int selectDoctor(dArray *doctors) {
  doctor *dList = (doctor *)doctors->array;

  if (doctors->used == 0) {
    printf("No doctors available. Please add a doctor first.\n");
    return -1;
  }

  printf("Available doctors:\n");
  for (size_t i = 0; i < doctors->used; i++) {
    printf("%zu. %s\n", i + 1, dList[i].name);
  }

  char *input = getInput("Select doctor number (or 0 to cancel): ");
  int selection = atoi(input);
  free(input);

  if (selection <= 0 || selection > (int)doctors->used) {
    printf("Invalid selection.\n");
    return -1;
  }

  return selection - 1; // Return array index (0-based)
}

void delet(dArray elements, void *element) {}

void showDoctorPatients() {
  // TODO: implementing feature to show patient of specifc doctor
};

void deletePatientFromDoctor() {

  // TODO: implementing feature to delete patient of specifc doctor
};

void deleteAllPatientsFromDoctor() {

  // TODO: implementing feature to delete all patients of specifc doctor
};

void manageDoctor(doctor *doc) {
  bool exitMenu = false;

  while (!exitMenu) {
    printf("\n--- Managing Dr. %s ---\n", doc->name);
    printf("1. Add new patient\n");
    printf("2. Show all patients\n");
    printf("3. Delete a patient\n");
    printf("4. Delete all patients\n");
    printf("5. Return to main menu\n");

    char *input = getInput("Select an option: ");
    int choice = atoi(input);
    free(input);

    switch (choice) {
    case 1:
      addPatient(&doc->patients);
      break;
    case 2:
      showDoctorPatients(doc);
      break;
    case 3:
      deletePatientFromDoctor(doc);
      break;
    case 4:
      deleteAllPatientsFromDoctor(doc);
      break;
    case 5:
      exitMenu = true;
      break;
    default:
      printf("Invalid option.\n");
      break;
    }
  }
}
