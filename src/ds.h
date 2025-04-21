#ifndef DS_H
#define DS_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// using void pointer for generic purpose and this is like templates from c++
// and this struct is for this purpuse to not repeat unneccessary code and make just one init function and one insert or i need to do one for each struct 

typedef struct{
    void *array; 
    size_t used;
    size_t size;
    size_t elementSize;
}dArray;

typedef struct{
    char name[50];
    char stage[50];
    bool status ;
}op;

typedef struct 
{
    char name[50];
    bool status;
    dArray ops;
}patient;

typedef struct{
    char name[50];
    dArray patients;
}doctor;

void initArray(dArray *a,size_t initialSize,size_t elementSize);
void insertArray(dArray *a,void *elemnt);
void freeArray(dArray *a);
char* userInput();
char *getInput(const char *prompt);
void addOp(dArray *ops);
void addPatient(dArray *patients,char *status);
void addDoctor(dArray *doctors);
void printPatients(char *input, dArray doctors);
int selectDoctor(dArray *doctors);
void showDoctorPatients();
void deletePatientFromDoctor();
void deleteAllPatientsFromDoctor();
void manageDoctor(doctor *doc);

#endif
