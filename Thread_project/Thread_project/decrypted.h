#pragma once
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
int decrypted(FILE* p_input_file, FILE* p_output_file, int start, int end, int key);
char* decrypted_line(char* line, int key);
int close_file(FILE* file, char* file_name);
FILE* open_file(FILE* file, char* file_name, char* file_open_type);
int write_line(FILE* output_file, char* line);
