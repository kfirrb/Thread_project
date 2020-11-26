#include "thread.h"

int *end_lines(FILE *fp) {
    int* line=NULL;
    if (NULL == (line = (int*)malloc(sizeof(int)*1))) { //check if allocate complketed
        printf("Memomry allocation failed\n");
        return NULL;
    }
    int counter = 0;
    int maximum = 1;
    int i = 0;
    int* flag = 1;
    while (flag) {
        counter = count_end_line(fp, flag, counter);
        line[i] = counter;
        if (NULL == (line = (int*)realloc(line,maximum))) {
            printf("Memomry allocation failed\n");
            return NULL; // re allocate memory.
        }
        i++;
    }
    return line;
}

int count_end_line(char* fp,int *flag, int* counter) {
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
        counter+=1;
        i++;
    }
    counter+=1;
    return counter;
}