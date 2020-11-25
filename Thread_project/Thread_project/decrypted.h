#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

char* read_file(FILE* file, int* flag);
int decrypted(char* path, int key);
char* decrypted_line(char* line, int key);
int close_file(FILE* file, char* file_name);
FILE* open_file(FILE* file, char* file_name, char* file_open_type);
int write_line(FILE* output_file, char* line);