#include "thread.h"

int *end_lines(FILE *fp) {
    int* line=NULL;
    if (NULL == (line = (int*)malloc(sizeof(int)*1))) { //check if allocate complketed
        printf("Memomry allocation failed\n");
        return NULL;
    }
    char ch;
    int counter = 0;
    int maximum = 1;
    int i = 0;
    for (ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        counter++;
        if (i == maximum - 1){
            if (NULL == (line = (int*)realloc(line, (maximum+2) * sizeof(int)))) {
                printf("Memomry allocation failed\n");
                return NULL;
            }
        }
        if (ch == '\n') {
            line[i] = counter;
            i++;
        }
    }
    line[i] = counter;
    i++;
    line[i] = '\0';
    return line;
}
