#pragma 
/*
threads_manager.c
--------------------------------------------------------------------------------------------------
Description- this module responsible to create of all threds and thier functionality
*/

// Includes --------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
#include "thread.h"
#include "decrypted.h"

// defines --------------------------------------------------------------------

#define STATUS_CODE_FAILURE -2 
#define SUCCESS_CODE 0 
#define INITIAL_SIZE 10
#define ERROR_CODE_FILE -3

// Types -----------------------------------------------------------------------

typedef struct threads_arg {
	FILE* input;
	FILE* output;
	int start;
	int end;
	int key;
	char mode;
}threads_arg, * P_threads_arg;

// Function Declarations -------------------------------------------------------

/*--------------------------------------------------------------------------------------------
DESCRIPTION - create and manager all the threads.
PARAMETERS - read: pointer to file to read from
			 write: pinter to file to write in it
			 array: array with all the number of the chcarectrs when a line is reach to \n or EOF
			 key: the key for the Ceaser cipher
			 threds: number of threads that suppose to create
			 mode: e/d which mean encrypted/decrypted
RETURN -  integer(suppose to be 0 if everthing is good)
	--------------------------------------------------------------------------------------------*/
int threads_manager(FILE* read, FILE* write, int* array, int key, int threads,char mode);

/*--------------------------------------------------------------------------------------------
DESCRIPTION - function for the manage and funcionality of one thread
PARAMETERS - lpparam: pointer to the handle
			 file_name: the name of file that we want
RETURN - Dword 0 or 1
	--------------------------------------------------------------------------------------------*/
DWORD WINAPI handle_thread(LPVOID lpParam);

/*--------------------------------------------------------------------------------------------
DESCRIPTION - function to free a handle and the struct
PARAMETERS - hthread: handle to the thread
			 thread_arg: a struct for the parametres that we transfer to the function
RETURN - void (because the function suppose to free all)
	--------------------------------------------------------------------------------------------*/
void free_thread(HANDLE hthread, P_threads_arg threads_arg);

/*--------------------------------------------------------------------------------------------
counter the number of lines in the input file. thats the same number as the indexes in the array we made.
	--------------------------------------------------------------------------------------------*/
int counter_line(int* array);

/*-------------------------------------------------------------------------------------------
DESCRIPTION - function for the waiting until the thread finish hiw missions.
PARAMETERS -  hthread: handle to the thread
			  thread_arg: a struct for the parametres that we transfer to the function
RETURN - void (maybe send us to error handle
	--------------------------------------------------------------------------------------------*/
void wait_until_signal(HANDLE hThread, P_threads_arg threads_arg);

/*--------------------------------------------------------------------------------------------
DESCRIPTION - manage errors
PARAMETERS - err_code: number of the error
RETURN - void (only print)
	--------------------------------------------------------------------------------------------*/
void error_handler(int err_code);
