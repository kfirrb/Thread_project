#include "decrypted.h"

int decrypted(FILE* p_input_file, FILE* p_output_file, int start, int end, int key, char mode) {
    int CUR_MAX_ROW = 10;
    char* line;
    if (NULL == (line = (char*)malloc(sizeof(char) * CUR_MAX_ROW))) { //check if allocate complketed
        printf("Memomry allocation failed\n");
        return NULL;
    }
    int flag = 1;
    while ((start<end) && flag) {
        line = read_line(p_input_file, &flag);
        if (flag == 0) {
            if (NULL == (line = (char*)realloc(line, strlen(line) + 1))) {
                printf("Memomry allocation failed\n");
                return NULL; // re allocate memory.
            }
            line[-1] = EOF;
        }
        start += strlen(line);
        line = decrypted_line(line, key, mode);
        if (0 != write_line(p_output_file, line)) return STATUS_CODE_FAILURE;
    }
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
    return buffer;
}

char* decrypted_line(char* line, int key, char mode) {
    int i;
    char sign;
    if (mode == 'd')
        sign = 1;
    else
        sign = -1;
    key *= sign;
    for (i = 0; i < strlen(line)-1; i++) {
        if (isdigit(line[i]))
            line[i] = ('0' + (line[i] - '0' - key) % 10);
        if (isalpha(line[i])) {
            if (isupper(line[i])) {
                if ((line[i] - 'A' - key) < 0)
                    line[i] += 26;
                line[i] = 'A' + (line[i] - 'A' - key) % 26;
            }
            else{
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
    fprintf(output_file, "%s", line);
    return 0;
}
