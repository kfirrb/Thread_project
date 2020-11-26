#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "decrypted.c"

#define INITIAL_SIZE 10

void handle_thread(char* path);
int* end_lines(FILE* fp);
int* count_end_line(char* fp, int* flag, int* counter);


void handle_thread(char* path) {
    FILE* p_input_file = NULL;
    char* in_file_name = path;
    char* in_file_open_type = "r";
    if (NULL == (p_input_file = open_file(p_input_file, in_file_name, in_file_open_type))) return ERROR_CODE_FILE;
    int* array = end_lines(p_input_file);
}

int *end_lines(FILE *fp) {
    int* line;
    if (NULL == (line = (int*)malloc(sizeof(int)*1))) { //check if allocate complketed
        printf("Memomry allocation failed\n");
        return NULL;
    }
    int counter = 0;
    int i = 0;
    int* flag = 1;
    while (flag) {
        counter = count_end_line(fp, flag, counter);
        line[i] = counter;
        if (NULL == (line = (int*)realloc(line,i+2))) {
            printf("Memomry allocation failed\n");
            return NULL; // re allocate memory.
        }
        i++;
    }
    return line;
}

int *count_end_line(char* fp,int *flag, int* counter) {
    char ch;
    int i=0;
    int CUR_MAX_ROW = INITIAL_SIZE;
    char* buffer;

    if (NULL == (buffer = (char*)malloc(sizeof(char) * CUR_MAX_ROW))) { //check if allocate complketed
        printf("Memomry allocation failed\n");
        return NULL;
    }

    for (ch = fgetc(fp); ch != '\n'; ch = fgetc(fp)) {
        if (i == CUR_MAX_ROW - 1) {
            CUR_MAX_ROW += 10; // expand to double the current size of anything similar.
            if (NULL == (buffer = (char*)realloc(buffer, CUR_MAX_ROW))) {
                printf("Memomry allocation failed\n");
                return NULL; // re allocate memory.
            }
        }
        if (ch == EOF) {
            flag = 0;
            break;
        }
        counter++;
        i++;
    }
    return counter++;
}