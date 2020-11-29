#pragma once
/*
decrypted.h
--------------------------------------------------------------------------------------------------
Description- all the functionality of the Ceaser cipher in this module
*/

// includes ------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

// definitions  ---------------------------------------------------------------------------------

#define STATUS_CODE_FAILURE -2 
#define SUCCESS_CODE 0 
#define INITIAL_SIZE 10
#define ERROR_CODE_FILE -3

// Function Declarations ----------------------------------------------------------------------

/*--------------------------------------------------------------------------------------------
DESCRIPTION - read each line from the input text and return it.
PARAMETERS - file: input file
             flag: rexponisble to tell us when we reach to EOF
RETURN - pointer to the string with all the letters in the line include \n
    --------------------------------------------------------------------------------------------*/
char* read_line(FILE* file, int* flag);

/*--------------------------------------------------------------------------------------------
DESCRIPTION - responsible for decrypted the hole part of each thread from start to end
PARAMETERS - p_input_file: pinter for the input file
             p_output_file: pinter for the output file
             start: the charecter to start the decrypted/encrypted in the file
             end:the charecter to end the decrypted/encrypted in the file
             key: the key for the Ceaser cipher
             mode: e/d which mean encrypted/decrypted
RETURN -  integer(suppose to be 0 if everthing is good)
    --------------------------------------------------------------------------------------------*/
int decrypted(FILE* p_input_file, FILE* p_output_file, int start, int end, int key, char mode);

/*--------------------------------------------------------------------------------------------
DESCRIPTION - responsible for decrypted/encryped an array of charectes until '\0'
PARAMETERS - line:the array that we need to turn with Ceaser cipher
             key: holds the key to encrypte/ decrypte.
             mode: e/d which mean encrypted/decrypted
RETURN - pointer to the string after the encrypte/ decrypte is done
    --------------------------------------------------------------------------------------------*/
char* decrypted_line(char* line, int key, char mode);

/*--------------------------------------------------------------------------------------------
DESCRIPTION - close file properly
PARAMETERS - file: pointer to a open file
             file_name: the name of file that we want
RETURN - integer 0 or 1 depends if we succed
    --------------------------------------------------------------------------------------------*/
int close_file(FILE* file, char* file_name);

/*--------------------------------------------------------------------------------------------
DESCRIPTION - close file properly
PARAMETERS - file: pointer to a open file path
             file_name: the name of the file we wantr
             file_open_type: "w" or "r" depeds if this is the input or output file
RETURN - integer 0 or 1 depends if we succed
    --------------------------------------------------------------------------------------------*/
FILE* open_file(FILE* file, char* file_name, char* file_open_type);

/*--------------------------------------------------------------------------------------------
write line to the ouput file.
    --------------------------------------------------------------------------------------------*/
int write_line(FILE* output_file, char* line);
