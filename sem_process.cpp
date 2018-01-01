#include "bigHeader.h"
#include "sem_process.h"
#include "semun.h"


void semaphore_process_basic(
			int argument_count, 
			char *argument_array[]
			){
	
	char output_char  = 'O';
	int time_to_sleep = 0;
	/*
		function to create 
		a semaphore id
	*/
	sem_id = semget((key_t)1234,1,0666|IPC_CREAT);

	if(argument_count > 1){
		if(!set_semvalue()){
			fprintf(stderr,"Failed to initialize semaphore\n");
			return;
		}
		output_char = 'X';
		sleep(2);	
	}

	/*
	here we have a lop which enters and leaves the
	criical section 10 times,we first makea  call to
	semaphore_p which sets the semaphore to wait,
	as this program is about to enter the critical section
	*/

	for(int i = 0;i< 10; i++){
		
		if(!semaphore_p()){
			return;
		}
		
		printf("%c",output_char);
		fflush(stdout);
		time_to_sleep = rand()%3;
		sleep(time_to_sleep);
		printf("%c",output_char);
		fflush(stdout);
		
		/*
		After the critical section we call the 
		semaphore_v to amke the semaphore available
		again before going to the next iteration of the loop
		*/

		if(!semaphore_v()){
			return;
		}
		time_to_sleep = rand() %2;
		sleep(time_to_sleep);
	}

	/*
		After the finishing of all iteration
		call del_semvalue() to clearn the semaphore
	*/

	printf("\n%d - finished\n",getpid());
	if(argument_count > 1){
		sleep(10);
		del_semvalue();
	}	
	return;
}

/*
	function to set the semaphore
	value 		
*/

static int set_semvalue(){
	
	int status = 0;
	union semun sem_union;

	sem_union.val = 1;
	if(semctl(sem_id,0,SETVAL,sem_union) == -1){
		return status;
	}

	status = 1;
	return status;
}

/*
	function to sem_wait
	change the value
	of the semaphore by -1
	which means its in 
	the waiting state
*/

static int semaphore_p(){
	int status = 0;

	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op  = -1;
	sem_b.sem_flg = SEM_UNDO;

	if(semop(sem_id,&sem_b,1) == -1){
		fprintf(stderr,"semaphore_p failed\n");
		return status;
	}

	status = 1;
	return status;
}

/*
	function to sempost
*/

static int semaphore_v(){
	int status = 0;

	struct sembuf sem_b;
	
	sem_b.sem_num = 0;
	sem_b.sem_op  = 1;
	sem_b.sem_flg = SEM_UNDO;

	if(semop(sem_id,&sem_b,1) == -1){
		fprintf(stderr,"semaphore_v failed\n");
		return status;
	}
	status = 1;
	return status;
}

/*
	function to delete the 
	semaphore value
*/

static void del_semvalue(){
	union semun sem_union;
	if(semctl(sem_id,0,IPC_RMID,sem_union) == -1){
		fprintf(stderr,"Failed to delete semaphore\n");
	}
	return;
}

