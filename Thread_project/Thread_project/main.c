#include "threads_manager.h"

int check_arguments(int argc, char* argv[], char* a_mode);

int main(int argc, char* argv[]){
    char mode = NULL;
	int* array;
    check_arguments(argc, argv, &mode);
	long key = atoi(argv[2]);
	long threads	 = atoi(argv[3]);
	FILE* p_input_file = NULL;
	char* in_file_name = argv[1];
	char* in_file_open_type = "r";

	FILE* p_output_file = NULL;
	char* out_file_name = "output.txt";
	char* out_file_open_type = "w";

	if (NULL == (p_input_file = open_file(p_input_file, in_file_name, in_file_open_type))) return ERROR_CODE_FILE;
	if (NULL == (p_output_file = open_file(p_output_file, out_file_name, out_file_open_type))) return ERROR_CODE_FILE;

	array = end_lines(p_input_file);
	threads_manager(p_input_file,p_output_file,array,key,threads,mode);

	if (close_file(p_input_file, in_file_name) == STATUS_CODE_FAILURE) return ERROR_CODE_FILE;
	if (close_file(p_output_file, out_file_name) == STATUS_CODE_FAILURE) return ERROR_CODE_FILE;
	return 0;
}

int check_arguments(int argc, char* argv[], char* a_mode) {
    if (!strcmp(argv[4], "-d")) 
        *a_mode = 'd';
    else if (!strcmp(argv[4], "-e")) 
        *a_mode = 'e';
    else {
        printf("mode must be -d or -e.");
        return -1;
    }
    if (argc != 5) {
        printf("Incorrect number of arguments. %d requird.", 4);
        printf("\t%d given.", argc - 1);
        return -1;
    }

    char* pkey;
    char* pthreads;
    long key, threads;
    errno = 0;
    key = strtol(argv[2], &pkey, 10);

    if (errno != 0 || *pkey != '\0' || key < 0) {
        return -1;
    }

    threads = strtol(argv[3], &pthreads, 10);

    if (errno != 0 || *pthreads != '\0' || threads < 0) {
        return -1;
    }

    else {
        return 1;
    }
}
