#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define STATUS_CODE_FAILURE -2 
#define SUCCESS_CODE 0 
#define INITIAL_SIZE 10
#define ERROR_CODE_FILE -3

char* read_line(FILE* file, int* flag);
int decrypted(char* path, int key);
char* decrypted_line(char* line, int key);
int close_file(FILE* file, char* file_name);
FILE* open_file(FILE* file, char* file_name, char* file_open_type);
int write_line(FILE* output_file, char* line);

int decrypted(char *path, int key){
    // check that argv2 is int
    int flag;
    char* line = NULL;

    FILE* p_input_file = NULL;
    char* in_file_name = path;
    char* in_file_open_type = "r";

    FILE* p_output_file = NULL;
    char* out_file_name = "output.txt";
    char* out_file_open_type = "w";

    if (NULL == (p_input_file = open_file(p_input_file, in_file_name, in_file_open_type))) return ERROR_CODE_FILE;

    // Open file with check
    if (NULL == (p_output_file = open_file(p_output_file, out_file_name, out_file_open_type))) return ERROR_CODE_FILE;
    flag = 1;
    while (flag) {
        line = read_line(p_input_file, &flag);
        line = decrypted_line(line, key);
        if (0 != write_line(p_output_file, line)) return STATUS_CODE_FAILURE;
    }

    // Close file with check
    if (close_file(p_input_file, in_file_name) == STATUS_CODE_FAILURE) return ERROR_CODE_FILE;

    // Close file with check
    if (close_file(p_output_file, out_file_name) == STATUS_CODE_FAILURE) return ERROR_CODE_FILE;

    return 0;
}


char* read_line(FILE* file,int *flag) {
    char ch;
    int i=0;
    int CUR_MAX_ROW = INITIAL_SIZE;
    char* buffer;

    if (NULL == (buffer = (char*)malloc(sizeof(char) * CUR_MAX_ROW))) { //check if allocate complketed
        printf("Memomry allocation failed\n");
        return NULL;
    }

    for (ch = fgetc(file); ch != '\n'; ch = fgetc(file)) {
        if (i == CUR_MAX_ROW - 1) {
            CUR_MAX_ROW += 10; // expand to double the current size of anything similar.
            if (NULL == (buffer = (char*)realloc(buffer, CUR_MAX_ROW))) {
                printf("Memomry allocation failed\n");
                return NULL; // re allocate memory.
            }
        }
        if (ch == EOF) {
            *flag = 0;
            break;
        }
        buffer[i++] = ch;
    }
    buffer[i++] = '\n';
    buffer[i++] = '\0';
    //close_file(file);
    return buffer;
}

char* decrypted_line(char* line, int key) {
    int i;
    for (i = 0; i < strlen(line)-1; i++) {
        if (isdigit(line[i]))
            line[i] = ('0' + (line[i] - '0' - key) % 10);
        if (isalpha(line[i])) 
            if (isupper(line[i]))
                line[i] = ('A' + (line[i] - 'A' - key) % 26);
            else
                line[i] = ('a' + (line[i] - 'a' - key) % 26);
        
    }
    return line;
}

int close_file(FILE* file, char* file_name) {
    errno_t retval;
    // Close file
    retval = fclose(file);
    if (0 != retval)
    {
        printf("Failed to close file: %s\n", file_name);
        return STATUS_CODE_FAILURE;
    }
    return SUCCESS_CODE;
}

FILE* open_file(FILE* file, char* file_name, char* file_open_type){
    errno_t retval;
    // Open file
    retval = fopen_s(&file, file_name, file_open_type);
    if (0 != retval)
    {
        printf("Failed to open file: %s\n", file_name);
        return file;
    }
    return file;
}

int write_line(FILE* output_file, char* line) {
    fprintf(output_file, "%s", line);
    return 0;
}
