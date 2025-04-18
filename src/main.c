#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ds.h"
//#include "raylib.h"

/*#define RAYGUI_IMPLEMENTATION*/
/*#include "raygui.h"*/
/*#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again*/

#define SIZEOF(A) (sizeof(A)/sizeof(A[0]))

void addOp(dArray *ops){
    //TODO: implementing logic for adding new ops

    //---------adding operations-------------
	
    printf("type (p) to stop adding operations and return to patients: \n");
    printf("types of operations: \n");
    char *input = userInput();
    op new_op;
	    new_op.status = false;
	    strcpy(new_op.name,input); // here for adding op name
	    if(strcmp(input,"endo") == 0 || strcmp(input,"resto") == 0){	
		printf("what is the stage: \n");
		input = userInput();
		strcpy(new_op.stage,input); // here for adding op stage
		if(strcmp(input, "final restoration") == 0){
		    new_op.status = true;
		};
	    }else{
		new_op.status = true;
	    };
	    insertArray(ops,&new_op);
	    printf("operation added!\n");
	    free(input);
	//----------------------
}

void addPatient(dArray *patients) {
//TODO: transfare the logic of adding patient here
    
    printf("write patient name: \n");
    char *input = userInput();
    patient p;
    strcpy(p.name,input);
    dArray ops;
    initArray(&ops,2,sizeof(op));
    addOp(&ops);
    op *opsList = (op *)ops.array;
    
    p.status = true;
    for(size_t i=0;i < ops.used;i++){
    	if(!opsList[i].status){
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

void addDoctor(dArray *doctors){
    //TODO: implementing logic for adding doctors here
    initArray(doctors,10, sizeof(doctor));
    
}
/**/
/*int loadDataFromDb(dArray *patients, const char *filename) {*/
/*//TODO: function to load data from DB*/
/*    sqlite3 *db;*/
/**/
/*    int rc = sqlite3_open(filename, &db);*/
/*    if (rc != SQLITE_OK) {*/
/*        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));*/
/*        return 1;*/
/*    }*/
/*    const char *sql = "CREATE TABLE IF NOT EXISTS patients";*/
/**/
/*}*/
/**/
void printPatients(char *input,dArray patients){
	patient *pList = (patient *)patients.array;
	if(strcmp(input,"c")==0){
	    for (size_t i = 0; i < patients.used ; i++) {
	    if(pList[i].status == true){
		printf("Patient %zu: %s\n", i + 1, pList[i].name);
		for (size_t r = 0; r < pList[i].ops.used; r++) {
		    op *opsList = (op *)(pList[i].ops.array);
		    printf("operations performed: %zu: %s\n",r+1,opsList[r].name);
		}
	    }
	}
    }
    else if(strcmp(input,"i") == 0) {
    // print incomplete patients
     for (size_t i = 0; i < patients.used ; i++) {
	    if(pList[i].status == false){
		printf("Patient %zu: %s\n", i + 1, pList[i].name);
		for (size_t r = 0; r < pList[i].ops.used; r++) {
		    op *opsList = (op *)(pList[i].ops.array);
		    printf("operations performed: %zu: %s\n",r+1,opsList[r].name);
		}
	    }
	}

    }
    else if(strcmp(input,"a") == 0) {
    // print all patients
    for (size_t i = 0; i < patients.used ; i++) {
	    if(pList[i].status == true){
		printf("Patient %zu: %s\n", i + 1, pList[i].name);
		for (size_t r = 0; r < pList[i].ops.used; r++) {
		    op *opsList = (op *)(pList[i].ops.array);
		    printf("operations performed: %zu: %s\n",r+1,opsList[r].name);
		}
	    }
	}
}
}

int main(void)
{

    //TODO: render ui here 
 
    /*const int screenWidth = 800;*/
    /*const int screenHeight = 450;*/
   
    dArray doctors;
    dArray patients;
    initArray(&doctors,10, sizeof(doctor));
    initArray(&patients, 10,sizeof(patient));
    printf("if you want to quit press(q): \n");
    printf("for adding patient type (d): \n");
    bool shouldQuit = false;
 
    while (!shouldQuit) {
	// adding patient 
	
	char *input = userInput();//getting user input
	
	if(strcmp(input, "q") == 0)
	{
	    free(input);
	    break;
	};

	//---------adding operations-------------
		    addPatient(&patients);
    }
    patient *pList = (patient *)patients.array;
    printf("press (c) to print completed cases or (i) for incompleted or (a) for all: \n");
    char *input = userInput();
    printPatients(input,patients);
    free(input);
    
     for(size_t i = 0 ;i<patients.used;i++){
	free(pList[i].ops.array);
    }
    freeArray(&patients);

    return 0;
}
