#include "threads_manager.h"

typedef struct threads_arg {
	FILE* input;
	FILE* output;
	int start;
	int end;
	int key;
}threads_arg, *P_threads_arg;

int threads_manager(FILE *read,FILE* write, int* array, int key, int threads) {
	DWORD   dwThread, waitFreeObject;
	HANDLE h_th;
	float rows_remain = (int)(sizeof(array) / sizeof(array[0]));
	int end,start,i = 0;
	int num_rows_read;
	threads_arg* threads_arg= NULL;
	while (threads != 0) {
		threads_arg = (P_threads_arg)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			sizeof(threads_arg));
		num_rows_read = ceil(rows_remain / threads);
		start = array[i]+1;
		if (i = 0)
			start = array[i];
		end = array[i + num_rows_read];
		i = num_rows_read;
		threads_arg->input = read;
		threads_arg->output = write;
		threads_arg->start = start;
		threads_arg->end = end;
		threads_arg->key = key;
		h_th = CreateThread(NULL,0, handle_thread, threads_arg,0, &dwThread);
		waitFreeObject = WaitForSingleObject;
		/*switch (waitFreeObject) {
		case (WAIT_ABANDONED): {
			free_thread(dwThread, threads_arg);
			return -1;
		}
		case (WAIT_OBJECT_0): {
			free_thread(dwThread, threads_arg);
			return 0;
		}
		case (WAIT_TIMEOUT): {
			free_thread(dwThread, threads_arg);
			return -1;
		}
		case (WAIT_FAILED): {
			free_thread(dwThread, threads_arg);
			return -1;
		}
		}*/
		threads--;
		rows_remain -= num_rows_read;
	}
	return 0;
}

DWORD WINAPI handle_thread(LPVOID lpParam) {
	threads_arg *th_arg;
	th_arg = (P_threads_arg)lpParam;
	int status = 0;
	status = decrypted(th_arg->input, th_arg->output, th_arg-> start, th_arg-> end, th_arg-> key);
	return status;
}

//void free_thread(HANDLE thread, threads_arg* threads_arg) {
//	CloseHandle(thread);
//	if (threads_arg != NULL) {
//		HeapFree(GetProcessHeap(),0,threads_arg);
//	}
//}
