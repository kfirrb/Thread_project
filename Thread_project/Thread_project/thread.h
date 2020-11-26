#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define INITIAL_SIZE 10

int* end_lines(FILE* fp);
int count_end_line(char* fp, int* flag, int* counter);