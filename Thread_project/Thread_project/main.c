#include "threads_manager.h"

int main(int argc, char* argv[]){
	int* array;
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
	threads_manager(p_input_file,p_output_file,array,key,threads);

	if (close_file(p_input_file, in_file_name) == STATUS_CODE_FAILURE) return ERROR_CODE_FILE;
	if (close_file(p_output_file, out_file_name) == STATUS_CODE_FAILURE) return ERROR_CODE_FILE;
	return 0;
}