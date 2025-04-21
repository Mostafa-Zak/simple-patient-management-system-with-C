#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "ds.h"
//#include "raylib.h"
#include "sqlite3.h"
/*#define RAYGUI_IMPLEMENTATION*/
/*#include "raygui.h"*/
/*#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again*/

#define SIZEOF(A) (sizeof(A)/sizeof(A[0]))
int loadDataFromDb(dArray *patients, const char *filename) {
//TODO: function to load data from DB
    sqlite3 *db;

    int rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    const char *sql = "CREATE TABLE IF NOT EXISTS patients";
return 0;
}
enum menu{
    n,
    m,
    s,
    q,
};
int main(void)
{

    //TODO: render ui here 
 
    /*const int screenWidth = 800;*/
    /*const int screenHeight = 450;*/
   
    dArray doctors;
    initArray(&doctors,3, sizeof(doctor));
    printf("if you want to quit press(q): \n");
    printf("for adding patient type (d): \n");
    bool shouldQuit = false;
 
    while (!shouldQuit) {
	printf("\n--- Main Menu ---\n");
        printf("(n) Add new doctor\n");
	printf("(m) Manage existing doctor\n");
	printf("(s) Show all patients\n");
	printf("(q) Quit\n");
	char input = getchar();
	while (getchar() != '\n'); // Clear the input buffer
	switch (input) {
	    case 'q':
		return 0;
		case 'n':
		addDoctor(&doctors);
		break;
	    case 'm':
		{
		int docIndex = selectDoctor(&doctors);
		if(docIndex>=0){
		    doctor *dList = (doctor *)doctors.array;
		    manageDoctor(&dList[docIndex]);
		}
		}
		break;
	    case 's':
		{
		char *viewChoice = getInput("Show (c) completed, (i) incomplete, (a) all: ");
		printPatients(viewChoice,doctors);
		free(viewChoice);
		}
		break;
	    default:
		printf("Invalid input!\n");
		break;    
	}
    }
            doctor *dList = (doctor *)doctors.array;
    for (size_t i = 0; i < doctors.used; i++) {
	patient *plist = (patient *)dList[i].patients.array;
	for (size_t j = 0; j < dList[i].patients.used; j++) {
	    free(plist[j].ops.array);
	}
    free(dList[i].patients.array);
}
    return 0;
}
