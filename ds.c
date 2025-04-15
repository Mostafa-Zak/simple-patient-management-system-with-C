#include "ds.h"
#include <stdlib.h>

void initArray(dArray *a,size_t initialSize,size_t elementSize)
{
    a -> array = malloc(initialSize * elementSize);
    a -> used = 0;
    a ->size = initialSize;
    a ->elementSize = elementSize;
}

void insertArray(dArray *a, void *element)
{
    if(a->used == a->size)
    {
	a->size *= 2;
	a->array = realloc(a->array, a->size * a->elementSize);
    }
    void *target = (char *)a->array + (a->used * a->elementSize);
    memcpy(target, element, a->elementSize);
    a->used++;
    
}

void freeArray(dArray *a)
{
    free(a->array);
    a->array = NULL;
    a->size = a->used = a-> elementSize = 0;
}

char* userInput()
{
	char* input = malloc(50);
	fgets(input,50, stdin);
	input[strcspn(input, "\n")] = 0; // remove newline
	return input;
};

