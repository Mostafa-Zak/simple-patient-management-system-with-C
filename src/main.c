#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ds.h"

int main(void)
{
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
	    // handling stage
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
    free(input);
    for(size_t i = 0 ;i<patients.used;i++){
	free(pList[i].ops.array);
    }
    freeArray(&patients);
    return 0;

    // Print the values of the array of structs

	/*   FILE *fpt;*/
	/*   fpt = fopen("data.csv", "a+");*/
	/*   for(int i =0; i<patients.used;i++){*/
	/*fprintf(fpt,"%d, %s,%s\n", i + 1, patients.array[i].name);*/
	/*   }*/
	/*   fclose(fpt);*/
 
}
