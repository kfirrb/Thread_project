/*
threads.c
--------------------------------------------------------------------------------------------------
Description- this module responsible on couning the end of each line.
*/
// Includes ---------------------------------------------------------------------------------------

#include "thread.h"

// Function ---------------------------------------------------------------------------------------

int *end_lines(FILE *fp) {
    int maximum = 1;
    int* line=NULL;
    int* line_1 = NULL;
    if (NULL == (line = (int*)malloc(sizeof(int)*maximum))) { //check if allocate completed
        printf("Memomry allocation failed\n");
        return NULL;
    }
    char ch;
    int empty_file = 1;
    int counter = 0;
    int i = 0;
    for (ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        counter++;
        if (i == maximum - 1){
            maximum += 2;
            if (NULL == (line_1 = (int*)realloc(line, (maximum) * sizeof(int)))) {
                free(line);
                printf("Memomry allocation failed\n");
                return NULL;
            }
            line = line_1;
        }
        if (ch == '\n') {
            line[i] = counter;
            i++;
        }
        empty_file = 0;
    }
    if (empty_file) {
        printf("Input file is empty\n");
        return NULL;
    }
    line[i] = counter;
    line[i + 1] = -1;
    return line;
}
