#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ds.h"
#include "raylib.h"


void addNewPatient(dArray *patients) {
//TODO: transfare the logic of adding patient here

}

void loadPatientsFromCSV(dArray *patients, const char *filename) {
//TODO: function to load patient from DB
}

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
    const int screenW = 800;
    const int screenH = 600;
    InitWindow(screenW, screenH, "PMS");
    SetTargetFPS(60);
    //main loop
    while (!WindowShouldClose()) {
	BeginDrawing();
	    ClearBackground(WHITE);
	    for(int i=0;i<100;i++){
		for(int r=0;r<100;r++){
		    Color cc = { r+i, r+i, r+i,r+i } ;
		    DrawCircle(50*r+i,50*r+i,50, cc);
	    }
	}
	    DrawText("Hello world", 190, 200, 20,BLACK );
	EndDrawing();
    }
    CloseWindow();

    dArray patients;
    initArray(&patients, 10,sizeof(patient));
    printf("if you want to quit press(q): \n");
    bool shouldQuit = false;
    while (!shouldQuit) {
	// adding patient 
	printf("write patient name: \n");
	
	char *input = userInput();//getting user input
	
	if(strcmp(input, "q") == 0)
	{
	    free(input);
	    break;
	};

	patient p;
	strcpy(p.name,input);
	free(input);
	dArray ops;
	initArray(&ops, 2,sizeof(op)); // initializing op for each patient
	//---------adding operations-------------
	printf("types of operations: \n");
	printf("type (p) to stop adding operations and return to patients: \n");
	while(true){
	    input = userInput();
	    if (strcmp(input, "q") == 0) {
		shouldQuit =true;
		break;
	    }
	    if(strcmp(input, "p") == 0)
	    {
		break;
	    };
	    
	    op new_op;
	    new_op.status = false;
	    strcpy(new_op.name,input); // here for adding op name
	    //---------------------
	    // handling stage
	    //--------------------
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
	    insertArray(&ops,&new_op);
	    printf("operation added!\n");
	    free(input);
	//----------------------
	
	op *opsList = (op *)ops.array;
	p.status = true;
	for(size_t i=0;i < ops.used;i++){
		if(!opsList[i].status){
		    p.status = false;
		    break;
	    }
	    }
	}
	p.ops.array = ops.array;
	p.ops.used = ops.used;
	p.ops.size = ops.size;
	p.ops.elementSize = ops.elementSize;
	ops.array = NULL;
	ops.used = 0;
	ops.size = 0;
	insertArray(&patients, &p);
	
    }
    patient *pList = (patient *)patients.array;
    printf("press (c) to print completed cases or (i) for incompleted or (a) for all: \n");
    char *input = userInput();
    printPatients(input,patients);
    free(input);
    // Print the values of the array of structs

	FILE *fp;
	size_t ret;
	unsigned char buffer[4];
	fp = fopen("data.csv", "a+");
	if (!fp) {
               perror("fopen");
               return EXIT_FAILURE;
           }
	
    ret = fread(buffer, 1, 1, fp);
           if (ret != 1) {
               fprintf(stderr, "fread() failed: %zu\n", ret);
               exit(EXIT_FAILURE);
           }



    for (size_t i = 0; i < patients.used ; i++) {
	    if(pList[i].status == true){
		printf("%zu: %s\n", i + 1, pList[i].name);
		for (size_t r = 0; r < pList[i].ops.used; r++) {
		    op *opsList = (op *)(pList[i].ops.array);
		    fprintf(fp, "\"%s\",\"%s\"\n", pList[i].name, opsList[r].name);
		}
	    }
    }

    fclose(fp);
     for(size_t i = 0 ;i<patients.used;i++){
	free(pList[i].ops.array);
    }
    freeArray(&patients);

    return 0;
}
