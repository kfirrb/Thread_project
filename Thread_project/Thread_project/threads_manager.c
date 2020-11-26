#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define STATUS_CODE_FAILURE -2 
#define SUCCESS_CODE 0 
#define INITIAL_SIZE 10
#define ERROR_CODE_FILE -3

void threads_manager(FILE *read,FILE* write, int* array, int key, int threads) {
	int rows_remain = (int)(sizeof(array) / sizeof(array[0]));
	int i = 0;
	while (threads != 0) {

	}
}