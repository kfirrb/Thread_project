#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
#include "thread.h"
#include "decrypted.h"

#define STATUS_CODE_FAILURE -2 
#define SUCCESS_CODE 0 
#define INITIAL_SIZE 10
#define ERROR_CODE_FILE -3

typedef struct threads_arg {
	FILE* input;
	FILE* output;
	int start;
	int end;
	int key;
}threads_arg, * P_threads_arg;

int threads_manager(FILE* read, FILE* write, int* array, int key, int threads);
DWORD WINAPI handle_thread(LPVOID lpParam);
void free_thread(HANDLE hthread, P_threads_arg threads_arg);
int counter_line(int* array);
void wait_until_signal(HANDLE hThread, P_threads_arg threads_arg);
