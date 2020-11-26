#include "decrypted.h"
#include "thread.c"
#include "threads_manager.h"

int main(int argc, char* argv[]){
	open_file();
	open_file();
	end_lines();
	threads_manager();
	int i = 0;
	i=decrypted("C:/Users/KfirRabinovitch/Documents/GitHub/Thread_project/Thread_project/Thread_project/test.txt", 3);
	handle_thread("C:/Users/KfirRabinovitch/Documents/GitHub/Thread_project/Thread_project/Thread_project/test.txt");
	return 0;
}