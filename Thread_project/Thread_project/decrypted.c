#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void decrypted(char *path, int key){
    char** mat=read_file(path);


}

char** read_file(char *path) {
    FILE* fp= NULL;
    fopen_s(&fp, path, "r"); // open file
    if (!fp) { // handle error
        printf("Error opening file\n");
        return 1;
    }
    char ch;
    int i;
    int CUR_MAX_ROW = 40;
    int CUR_MAX_COLUMN = 40;
    char **matrix = (char**)malloc(sizeof(char*) * CUR_MAX_ROW* CUR_MAX_COLUMN);//check if allocate complketed
    if (NULL == matrix) {
        printf("Memomry allocation failed\n");
    }
    for (i = 0; i < CUR_MAX_ROW; i++) {
        matrix[i] = (char*) malloc(CUR_MAX_COLUMN * sizeof(char));
        if (NULL == matrix) {
            printf("Memomry allocation failed\n");
        }
    }
    int row = 0;//current length of the line
    int column = 0;//current length of the column
    ch = getc(fp);

    while ((ch != EOF)) {
        if (column == CUR_MAX_COLUMN){
            CUR_MAX_COLUMN +=10; // expand to double the current size of anything similar.
            matrix = (char*)realloc(matrix[row],CUR_MAX_COLUMN); // re allocate memory.
            if (NULL == matrix) {
                printf("Memomry allocation failed\n");
            }
        }
        if (row == CUR_MAX_ROW) {
            CUR_MAX_ROW += 10; // expand to double the current size of anything similar.
            matrix = (char**)realloc(matrix, CUR_MAX_ROW); // re allocate memory.
            if (NULL == matrix) {
                printf("Memomry allocation failed\n");
            }
        }
        if (ch == '\n') {
            matrix[row][column] = ch;
            column =0;
            row += 1;
            ch = getc(fp);
        }
        matrix[row][column] = ch; // stuff in buffer.
        ch = getc(fp); // read from stream.
        column++;
    }
    printf(matrix);
    //free
    fclose(fp);
    return matrix;
}

char** decrypted_mat(char** matrix, int key) {
    int i, j;
 
}
