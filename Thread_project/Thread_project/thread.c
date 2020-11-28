// LastErrorDemonstration.c

/*
* This program serves as a demonstration on when and how to get the
* Last Error Code Value.
*
* The last error code is a thread local variable in kernel space.
* Some WINAPI functions write to this variable as a method of passing
* extended error information to the calling thread.
* Consult the recitation slides for additional information.
*/

// Includes --------------------------------------------------------------------

#include "thread.h"

// Function Declarations -------------------------------------------------------

int *end_lines(FILE *fp) {
    int* line=NULL;
    if (NULL == (line = (int*)malloc(sizeof(int)*1))) { //check if allocate complketed
        printf("Memomry allocation failed\n");
        return NULL;
    }
    char ch;
    int empty_file = 1;
    int counter = 0;
    int maximum = 1;
    int i = 0;
    for (ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        counter++;
        if (i == maximum - 1){
            if (NULL == (line = (int*)realloc(line, (maximum++) * sizeof(int)))) {
                printf("Memomry allocation failed\n");
                return NULL;
            }
        }
        if (ch == '\n') {
            line[i] = counter;
            i++;
        }
        empty_file = 0;
    }
    if (empty_file) {
        printf("Input file is empty\n");
    }
    line[i] = counter;
    i+=1;
    line[i] = '\0';
    return line;
}
