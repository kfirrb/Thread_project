#include "threads_manager.h"

int check_arguments(int argc, char* argv[], char* a_mode);

int main(int argc, char* argv[]){
    char mode = NULL;
	int* array;
    if (check_arguments(argc, argv, &mode) != 1) {
        printf("Error handle with arguments\n");
        return -1;
    }
	long key = atoi(argv[2]);
	long threads = atoi(argv[3]);
	FILE* fp_input_file = NULL;
	char* in_file_name = argv[1];
	char* in_file_open_type = "r";

	FILE* fp_output_file = NULL;
    char* out_file_name = NULL;
    if (mode=='d')
        out_file_name = "decrypted.txt";
    else
        out_file_name = "encrypted.txt";
	char* out_file_open_type = "w";

	if (NULL == (fp_input_file = open_file(fp_input_file, in_file_name, in_file_open_type))) return ERROR_CODE_FILE;
	if (NULL == (fp_output_file = open_file(fp_output_file, out_file_name, out_file_open_type))) return ERROR_CODE_FILE;

	array = end_lines(fp_input_file);
	threads_manager(fp_input_file,fp_output_file,array,key,threads,mode);

	if (close_file(fp_input_file, in_file_name) == STATUS_CODE_FAILURE) return ERROR_CODE_FILE;
	if (close_file(fp_output_file, out_file_name) == STATUS_CODE_FAILURE) return ERROR_CODE_FILE;
	return 0;
}

int check_arguments(int argc, char* argv[], char* mode) {
    if (!strcmp(argv[4], "-d")) 
        *mode = 'd';
    else if (!strcmp(argv[4], "-e")) 
        *mode = 'e';
    else {
        printf("mode must be -d or -e\n");
        return -1;
    }
    if (argc != 5) {
        printf("Incorrect number of arguments. %d requird\n", 4);
        printf("\t%d given\n", argc - 1);
        return -1;
    }

    char* p_key;
    char* p_threads;
    long key, threads;
    errno = 0;
    key = strtol(argv[2], &p_key, 10);

    if (errno != 0 || *p_key != '\0' || key < 0) 
        return -1;

    threads = strtol(argv[3], &p_threads, 10);

    if (errno != 0 || *p_threads != '\0' || threads < 0) 
        return -1;
    else 
        return 1;
}
