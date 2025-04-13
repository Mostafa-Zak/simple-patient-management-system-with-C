#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct operation 
{
    char name[50];
    char stage[50];
}op;
struct patient 
{
    char name[50];
    bool status;
    op op;
};

typedef struct 
{
    struct patient *array;
    size_t used;
    size_t size;
} Array;

void initArray(Array *a,size_t initialSize)
{
    a -> array = malloc(initialSize * sizeof(struct patient));
    a -> used = 0;
    a ->size = initialSize;
}
void insertArray(Array *a, struct patient element)
{
    if(a->used == a->size)
    {
	a->size *= 2;
	a->array = realloc(a->array, a->size * sizeof(struct patient));
    }
    a->array[a->used++] = element;
}
void freeArray(Array *a)
{
    free(a->array);
    a->array = NULL;
    a->size = a->used = 0;
}
int main(int argc,char* argv[])
{
    Array patients;
    initArray(&patients, 10);
    
    int count = 0;
    printf("if you want to quit press(q): ");
    while (true) {
	
	char input[100];
	printf("write patient name: \n");
	// Using scanf (not safe for spaces):
	scanf("%s", input);
	if(strcmp(input, "q") == 0)break;
	struct patient p;
	strcpy(p.name, input);
	insertArray(&patients, p);
	count++;
    }
    // Print the values of the array of structs
    for (int i = 0; i < count; i++) {
        printf("Patient %d: %s\n", i + 1, patients.array[i].name);
    }
    return 0;
}
