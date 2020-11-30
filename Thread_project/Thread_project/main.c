// main.c
/*AUTHORS - Shai Maor 308244748 and Kfir Rabinovitc 312141237
PROJECT - CAESAR/THREADS
DESCRIPTION - This program serves as a tool for encrypted or decypred code with key. the code is
 work with Ceaser cipher.
*
* Ceaser cipher is a encryption techniqu that work with a key and sertion cipher for
every sitauatio, include upper and lower letters and integers.
 we decided to split our project to 3 modules:
        threads_Manager - creates and operates threads.
        thread - handles with amount of lines for each thread
        decrypted - responsible on encrypet and decrypt techniques.
*/


// Includes --------------------------------------------------------------------

#include "threads_manager.h"

// Function Declarations -------------------------------------------------------

/*--------------------------------------------------------------------------------------------
DESCRIPTION - functions that help to cheack our arguments
PARAMETERS - args: number of args in the command line
             argv[]: array of paramtrs in the commnd line
             mode: the mode of the cipher
RETURN - integer 0 or 1 depends if the arguments were fine or not.
    --------------------------------------------------------------------------------------------*/

int check_arguments(int argc, char* argv[], char* mode);

// Function ----------------------------------------------------------------------

int main(int argc, char* argv[]){
    char mode;
	int* array;
    if (check_arguments(argc, argv, &mode) != 1) {
        printf("Error handle with arguments\n");
        return -1;
    }
	long key = atoi(argv[2]);
	long threads = atoi(argv[3]);
    //inputs
	FILE* fp_input_file = NULL;
	char* in_file_name = argv[1];
	char* in_file_open_type = "r";
    //outputs
	FILE* fp_output_file = NULL;
    char* out_file_name = NULL;
    if (mode=='d')
        out_file_name = "decrypted.txt";
    else
        out_file_name = "encrypted.txt";
	char* out_file_open_type = "w";

	if (NULL == (fp_input_file = open_file(fp_input_file, in_file_name, in_file_open_type))) 
        return ERROR_CODE_FILE;
	if (NULL == (fp_output_file = open_file(fp_output_file, out_file_name, out_file_open_type)))
        return ERROR_CODE_FILE;

	array = end_lines(fp_input_file);
    if (array != NULL) {
        threads_manager(fp_input_file, fp_output_file, array, key, threads, mode);
        free(array);
    }

	if (close_file(fp_input_file, in_file_name) == STATUS_CODE_FAILURE)
        return ERROR_CODE_FILE;
	if (close_file(fp_output_file, out_file_name) == STATUS_CODE_FAILURE)
        return ERROR_CODE_FILE;
	return 0;
}

int check_arguments(int argc, char* argv[], char* mode) {
    if (argc != 5) {
        printf("Incorrect number of arguments. %d requird\n", 4);
        printf("\t%d given\n", argc - 1);
        return -1;
    }
    if (!strcmp(argv[4], "-d")) 
        *mode = 'd';
    else if (!strcmp(argv[4], "-e")) 
        *mode = 'e';
    else {
        printf("mode must be -d or -e\n");
        return -1;
    }

    char* p_key;
    char* p_threads;
    long key, threads;
    errno = 0;
    key = strtol(argv[2], &p_key, 10);

    if (errno != 0 || *p_key != '\0' ) 
        return -1;

    threads = strtol(argv[3], &p_threads, 10);

    if (errno != 0 || *p_threads != '\0' || threads < 0) 
        return -1;
    else 
        return 1;
}
