#ifndef SEM_PROCESS_H
#define SEM_PROCESS_H

/*
	functions declared as static has 
	scope on the same translational unit
	it is not visible to outside
	other than this file
*/

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);
static int sem_id;

void semaphore_process_basic(
			int argument_count,
			char *argument_array[]
			);


#endif // SEM_PROCESS_H
