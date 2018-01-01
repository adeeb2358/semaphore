#include "bigHeader.h"
#include "sem_process.h"


int main(int argc,char *argv[]){
	int start_s = clock();

	/*
		code block to execute
	*/

	semaphore_process_basic(argc,argv);

	int a      = 0;
	int stop_s = clock();
	std::cout <<"\nExecutionTime:- " <<  (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
	std::cout <<"\nPress enter key to exit\n";
	int ch     = std::cin.get();

	return 0;
}