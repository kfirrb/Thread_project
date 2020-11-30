/*
threads_manager.c
--------------------------------------------------------------------------------------------------
Description- this module responsible to create of all threds and thier functionality
*/

// includes -------------------------------------------------------

#include "threads_manager.h"

// Function---------------------------------------------------------

int threads_manager(FILE* read, FILE* write, int* array, int key, int threads,char mode) {
	DWORD   dwThread;
	HANDLE h_th;
	P_threads_arg threads_arg;
	float rows_remain = (float)counter_line(array);
	int end, start, i = 0;
	int num_rows_read;
	while (threads != 0) {
		threads_arg = (P_threads_arg)HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS,
			5*sizeof(threads_arg));
		if (threads_arg == NULL)
			return ERROR_CODE_FILE;
		num_rows_read = ceil(rows_remain / threads);
		if (rows_remain <= 0) {//open thread but because end=start dont do nothing
			start = 1;
			end = 1;
		}
		else {
			if (i == 0)
				start = 0;
			else
				start = array[i - 1] + 1;
			i += num_rows_read;
			end = array[i - 1];
		}
		threads_arg->input = read;
		threads_arg->output = write;
		threads_arg->end = end;
		threads_arg->key = key;
		threads_arg->mode = mode;
		threads_arg->start = start;
		h_th = CreateThread(NULL, 0, handle_thread, threads_arg, 0, &dwThread);
		if (h_th == NULL) {
			free_thread(h_th, threads_arg);
			return ERROR_CODE_FILE;
		}
		wait_until_signal(h_th, threads_arg);
		threads--;
		rows_remain -= num_rows_read;
	}
	return 0;
}

DWORD WINAPI handle_thread(LPVOID lpParam) {
	P_threads_arg  th_arg;
	th_arg = (P_threads_arg)lpParam;
	int status = 0;
	if (th_arg->start==0)
		if ((fseek(th_arg->input, (sizeof(char) * th_arg->start), SEEK_SET)) != 0)
			return ERROR_CODE_FILE;
	status = decrypted(th_arg->input, th_arg->output, th_arg->start, th_arg->end, th_arg->key, th_arg->mode);
	return status;
}

void free_thread(HANDLE hthread, P_threads_arg threads_arg) {
	CloseHandle(hthread);
	if (threads_arg != NULL) {
		HeapFree(GetProcessHeap(), 0, threads_arg);
		threads_arg = NULL;
	}
}

int counter_line(int* array) {
	int i = 0;
	while (*(array + i) != -1) {
		i++;
	}
	return i;
}

void wait_until_signal(HANDLE hThread, P_threads_arg threads_arg) {
	DWORD waitFreeObject = WaitForSingleObject(hThread,20000);
	free_thread(hThread, threads_arg);
	if (0 != waitFreeObject) {
		error_handler(waitFreeObject);
	}
}

void error_handler(int err_code) {

	printf("-------ERROR--------\n");
	printf("Error num %d", err_code);
	exit(err_code);
}