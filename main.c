#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct operation 
{
    char name[50];
    char stage[50];
    bool status ;
}op;

typedef struct
{
    op *array;
    size_t used;
    size_t size;
} opArray;

typedef struct 
{
    char name[50];
    bool status;
    opArray ops;
}patient;

typedef struct 
{
    patient *array;
    size_t used;
    size_t size;
} pArray;

void initpArray(pArray *a,size_t initialSize)
{
    a -> array = malloc(initialSize * sizeof(patient));
    a -> used = 0;
    a ->size = initialSize;
}
void initOpArray(opArray *a, size_t initialSize)
{
    a->array = malloc(initialSize * sizeof(op));
    a-> used = 0;
    a->size = initialSize;
};

void insertOpArray(opArray *a, op element)
{
    if (a->used == a->size)
    {
	a->size *=2;
	a->array = realloc(a->array, a->size * sizeof(op));
    }
    a->array[a->used++] = element;
}

void insertpArray(pArray *a,patient element)
{
    if(a->used == a->size)
    {
	a->size *= 2;
	a->array = realloc(a->array, a->size * sizeof(patient));
    }
    a->array[a->used++] = element;
}

void freeArray(pArray *a)
{
    free(a->array);
    a->array = NULL;
    a->size = a->used = 0;
}
void freeOpArray(opArray *a)
{
    free(a->array);
    a->size = a->used = 0;
}


char* userInput()
{
	char* input = malloc(50);
	fgets(input,50, stdin);
	input[strcspn(input, "\n")] = 0; // remove newline
	return input;
};

int main(int argc,char* argv[])
{
    pArray patients;
    initpArray(&patients, 10);
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
	initOpArray(&p.ops, 2);
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
	    insertOpArray(&p.ops,new_op);
	    printf("operation added!\n");
	    free(input);
	//----------------------
	
	for(int i=0;i < p.ops.used;i++){
		if(p.ops.array[i].status == false){
		    p.status = false;
		    break;
	    }else{
		p.status = true;
		};
	    }
	}
	
	insertpArray(&patients, p);
	
    }
    printf("press (c) to print completed cases or (i) for incompleted or (a) for all: \n");
    char *input = userInput();
    if(strcmp(input,"c")==0){
	    for (int i = 0; i < patients.used ; i++) {
	    if(patients.array[i].status == 1){
		printf("Patient %d: %s\n", i + 1, patients.array[i].name);
		for (int r = 0; r < patients.array[i].ops.used; r++) {
		    printf("operations performed: %d: %s\n",r+1,patients.array[i].ops.array[r].name);
		}
	    }
	}
    }
    return 0;
    // Print the values of the array of structs
    for (int i = 0; i < patients.used; i++) {
        printf("Patient %d: %s\n", i + 1, patients.array[i].name);

	for (int r = 0; r < patients.array[i].ops.used; r++) {
	    printf("operations performed: %d: %s\n",r+1,patients.array[i].ops.array[r].name);
	}
    }

	/*   FILE *fpt;*/
	/*   fpt = fopen("data.csv", "a+");*/
	/*   for(int i =0; i<patients.used;i++){*/
	/*fprintf(fpt,"%d, %s,%s\n", i + 1, patients.array[i].name);*/
	/*   }*/
	/*   fclose(fpt);*/
    for (int i = 0; i < patients.used; i++) {
	freeOpArray(&patients.array[i].ops);
}
    freeArray(&patients);
    return 0;
}
