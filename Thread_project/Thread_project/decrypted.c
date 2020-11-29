/*
decrypted.c
--------------------------------------------------------------------------------------------------
Description- all the functionality of the Ceaser cipher in this module
*/

// includes -------------------------------------------------------

#include "decrypted.h"

// Function---------------------------------------------------------

int decrypted(FILE* p_input_file, FILE* p_output_file, int start, int end, int key, char mode) {
    int CUR_MAX_ROW = 10;
    char* line;
    int flag = 1;
    while ((start<end) && flag) {
        line = read_line(p_input_file, &flag);//get the line
        start += strlen(line);//check how much charectes till the end
        line = decrypted_line(line, key, mode);//decrypt her
        if (0 != write_line(p_output_file, line)) return STATUS_CODE_FAILURE;
        free(line);
    }
    
    return 0;
    }

char* read_line(FILE* file,int *flag) {
    char ch;
    int i=0;
    int CUR_MAX_ROW = INITIAL_SIZE;
    char* buffer=NULL;
    char* buffer_1=NULL;

    if (NULL == (buffer = (char*)malloc(sizeof(char) * CUR_MAX_ROW))) { //check if allocate complketed
        printf("Memomry allocation failed\n");
        return NULL;
    }

    for (ch = fgetc(file); ch != '\n'; ch = fgetc(file)) {
        if (i == CUR_MAX_ROW - 2) {//if we are close to the end of the allocatin
            CUR_MAX_ROW *= 2;
            if (NULL == (buffer_1 = (char*)realloc(buffer, CUR_MAX_ROW))) {
                printf("Memomry allocation failed\n");
                free(buffer);
                return NULL; // re allocate memory.
            }
            buffer = buffer_1;
        }
        if (ch == EOF) {
            *flag = 0;//help us in the outer functions
            break;
        }
        buffer[i++] = ch;
    }
    if (*flag) {
        buffer[i++] = '\n';
    }
    buffer[i++] = '\0';
    return buffer;
}

char* decrypted_line(char* line, int key, char mode) {
    unsigned int i;
    char sign;
    if (mode == 'd')
        sign = 1;
    else
        sign = -1;
    key *= sign;//the mode is now can get into the equations
    for (i = 0; i < strlen(line); i++) {//3 cases
        if (isdigit(line[i]))//interger
            line[i] = ('0' + (line[i] - '0' - key) % 10);
        if (isalpha(line[i])) {
            if (isupper(line[i])) {//uppper
                if ((line[i] - 'A' - key) < 0)
                    line[i] += 26;
                line[i] = 'A' + (line[i] - 'A' - key) % 26;
            }
            else{//lower
                if ((line[i] - 'a' - key) < 0)
                    line[i] += 26;
                line[i] = 'a' + (line[i] - 'a' - key) % 26;
            }
        }
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
    fprintf(output_file, "%s", line);//print line to output file
    return 0;
}
