/*
 ============================================================================
 Name        : ex05.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A threaded task-list example.
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#define _GNU_SOURCE             /* See feature_test_macros(7) */

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include <termios.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/types.h>


#include "structs.h"

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* On Linux, the default scheduler uses a dynamic priority which is calculated
 * based on the nice value, and how often a given thread is not scheduled.
 * Such nice value ranges from -20 to 19, where -20 is the highest priority.
 * When creating a new thread, the default nice value is 0.
 * In order to increase the priority levels, (0-99), one should change the schedule
 * policy to RR (round robin) or FIFO.
 *
 *	The below definitions represents, in fact, NICE values.
 *
 * */
#define PRODUCER_NICENESS -20
#define WORKER_A_NICENESS  5
#define WORKER_B_NICENESS -10

/* The number of tasks to be generated by the producer at each execution cycle.*/
#define PRODUCER_N_TASKS  10

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief A function to verify if any key was pressed on terminal. Adapted from
 *
 *  https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
 *
 *
 * @return TRUE     If a key was pressed.
 * @return FALSE    Otherwise.
 */
static int kbhit(void);

/**
 * @brief Initializes the task_list.
 *
 * @param[inout] pp_head	An empty pointer which will become the head
 * 							of the task_list.
 *
 */
void task_list_initialize(
	task_t **pp_head);

/**
 * @brief Empties a linked list of tasks.
 *
 * @param[in] pp_head       The singly linked list's head.
 */
void task_list_finalize(
	task_t **pp_head);

/**
 * @brief Adds a new task to the linked list of tasks.
 *
 * @param[inout] pp_head  The task list's head.
 * @param[in] my_param    The task parameters.
 */
void task_add(
	task_t **pp_head,
	task_param_t my_param);

/**
 * @brief Checks if the task-list is empty.
 *
 * @param[in] pp_head The linked list's head to be checked.
 *
 * @return 1 	If the list is empty.
 * @return 0 	If the list is not empty.
 */
int is_task_list_empty(task_t **pp_head);


/**
 * @brief Removes a task from the linked list of tasks.
 *
 * @param[inout] pp_head  The task list's head.
 *
 * @return				  The removed task.
 */
task_t task_remove(task_t **pp_head);


/**
 * @brief Prints the task-list on screen.
 *
 * @param[in] pp_head       The singly linked list's head.
 */
void task_list_print(task_t **pp_head);


/**
 * @brief The producer thread. It generates 10 tasks per second.
 * Each task is saved in a node list and added to the task-list.
 *
 * A task is represented through two randomly generated numbers:
 * a character and a counter. So, at each execution cycle (1s),
 * the producer thread generates 10 times:
 * a random char and a random counter and adds them in the task-list.
 */
void * producer_thread(void *p_thread_arg);

/**
 * @brief The worker thread.
 *
 * It processes each node (task) from the task-list. A task is
 * processed by printing the character "counter" times. See the thread
 * definition for further details.
 */
void * worker_thread_a(void *p_thread_arg);


/**
 * @brief The same as the above thread. The difference relies on its
 * nice (priority) value.
 */
void * worker_thread_b(void *p_thread_arg);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

/* The mutex used to protect a shared resource between the Producer and worker
 * threads. Such resource is the task-list. */
pthread_mutex_t task_list_mutex = PTHREAD_MUTEX_INITIALIZER;

/* A semaphore is used to indicate the number of tasks currently in the task list.
 * That is, worker threads wait for the producer notifying them (through the semaphore)
 * that there is task to process. */
sem_t task_list_count;

/* A variable to indicate to worker threads that the producer is still running.
 * When the producer exits, the worker threads do also.*/
volatile uint8_t producer_alive;

/* The below variables are used to demonstrate how the difference between the worker's
 * nice values influence in which thread processes more tasks.*/
unsigned worker_a;
unsigned worker_b;

//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{
	/* The head of the task list. */
	task_t *p_head;

	producer_alive = 1;
	worker_a = 0;
	worker_b = 0;

	/* The following variables are used to specify in which core a thread will run. */
	cpu_set_t  cpu_mask;
	pthread_attr_t attr;

	/* Reads the number of cores/processors in a machine.*/
	int numberOfProcessors = sysconf(_SC_NPROCESSORS_ONLN);
	printf("Number of processors: %d\n", numberOfProcessors);

	task_list_initialize(&p_head);

	/* The pthread IDs. */
	pthread_t thread_id[4];

	int setname_ret;

	/* "zeroes" the variable cpu_mask. */
	CPU_ZERO(&cpu_mask);
	/* Sets it to core 0. */
	CPU_SET(0, &cpu_mask);

	/* Initializes the attr structure. It is necessary before manipulating it. Also,
	 * it is used to manipulate many thread attributes. */
	pthread_attr_init(&attr);

	/* Sets the affinity attribute. It indicates in which core the thread will run.*/
	pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_mask);

	/* Creates the producer thread with the previous defined CPU mask (core 0). */
	pthread_create(&thread_id[0], &attr, &producer_thread, &p_head);

	/* Sets the producer thread's name. It can be visualized on htop app.*/
	setname_ret = pthread_setname_np(thread_id[0], "producer");

	if (setname_ret)
	{
		errno = setname_ret;
		perror("Could not set the producer name");
	}

	/* It is necessary to zero the cpu_mask again before changing the core number. */
	CPU_ZERO(&cpu_mask);
	/* Sets it to core 1. */
	CPU_SET(0, &cpu_mask);

	/* from now... is the same process as the producer thread. */
	pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_mask);

	pthread_create(&thread_id[1], &attr, &worker_thread_a, &p_head);
	setname_ret = pthread_setname_np(thread_id[1], "worker_a");
	if (setname_ret)
	{
		errno = setname_ret;
		perror("Could not set worker_a name");
	}

	/* It is necessary to zero the cpu_mask again before changing the core number. */
	CPU_ZERO(&cpu_mask);
	/* Sets it to core 2. */
	CPU_SET(0, &cpu_mask);

	/* from now... is the same process as the producer thread. */
	pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_mask);

	pthread_create(&thread_id[2], &attr, &worker_thread_b, &p_head);
	setname_ret = pthread_setname_np(thread_id[2], "worker_b");
	if (setname_ret)
	{
		errno = setname_ret;
		perror("Could not set worker_b name");
	}

	/* It is necessary to zero the cpu_mask again before changing the core number. */
	CPU_ZERO(&cpu_mask);
	/* Sets it to core 3. */
	CPU_SET(0, &cpu_mask);

	/* from now... is the same process as the producer thread. */
	pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_mask);

	pthread_create(&thread_id[3], &attr, &worker_thread_a, &p_head);
	setname_ret = pthread_setname_np(thread_id[3], "worker_a2");
	if (setname_ret)
	{
		errno = setname_ret;
		perror("Could not set worker_a2 name");
	}

	/* Waits for the specified thread to terminate. */
	if(pthread_join(thread_id[0],NULL) == 0)
	{
		printf("Producer finalized!\n");
	}

	if(pthread_join(thread_id[1],NULL) == 0)
	{
		printf("Worker A finalized!\n");
	}

	if(pthread_join(thread_id[2],NULL) == 0)
	{
		printf("Worker B finalized!\n");
	}

	if(pthread_join(thread_id[3],NULL) == 0)
	{
		printf("Worker A2 finalized!\n");
	}

	task_list_finalize(&p_head);

	return EXIT_SUCCESS;
}

/*
 * NOTE: Try to change the core where each thread runs. For example, put one thread
 * on each RPi3 core. What did you see? How much the niceness influence in such conditions?
 */

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

void task_list_initialize(
		task_t **pp_head)
{
	*pp_head = NULL;
	sem_init(&task_list_count,0,0); /* The second and third parameters indicates
	 	 	 	 	 	 	 	 	   if the sem is shared between processes
	 	 	 	 	 	 	 	 	   and the initial value of the semaphore.
	 	 	 	 	 	 	 	 	   0 means no sharing and sem_wait calls
	 	 	 	 	 	 	 	 	   must wait for a sem_post.*/
}

void task_add(
	task_t **pp_head,
	task_param_t my_param)
{
	task_t *p_new_task;

	/* Allocates the required memory for the new task and fills it with the task
	 * parameters.*/
	p_new_task 		   = malloc(sizeof(task_t));
	p_new_task->param  = my_param;
	p_new_task->p_next = NULL;

	/* If the task_list is empty, the new task becomes the head of the task-list.
	 * Otherwise, the new task points to the current head and then it becomes the
	 * new head. */
	if (is_task_list_empty(pp_head))
	{
		*pp_head   		 = p_new_task;	
	}
	else
	{
		p_new_task->p_next = *pp_head;
		*pp_head = p_new_task;
	}
}

int is_task_list_empty(task_t **pp_head)
{
	uint8_t ret;

	if(*pp_head == NULL)
	{
		ret = 1;
	}
	else
	{
		ret = 0;
	}

	return ret;
}

task_t task_remove(task_t **pp_head)
{
	task_t ret;
	task_t *p_aux;

	p_aux    = *pp_head;
	*pp_head = p_aux->p_next;
	ret      = *p_aux;

	free(p_aux);
	return ret;
}


void task_list_finalize(task_t **pp_head)
{
    task_t *p_aux;
    p_aux = *pp_head;
	
    uint8_t task_count = 0;

    while(!is_task_list_empty(pp_head))
    {
        p_aux = p_aux->p_next;

        free(*pp_head);
        task_count++;

        *pp_head = p_aux;
    }

		printf("Task-list finalized: %d tasks were freed!\n", task_count);
}

void task_list_print(task_t **pp_head)
{
	task_t *p_aux;
	p_aux = *pp_head;

	printf("Task List:\n");

    while(p_aux != NULL)
    {
    	printf("(char:%c number of prints:%u)->\n",
    			p_aux->param.character,
				p_aux->param.count);

    	p_aux = p_aux->p_next;
    }

    printf("\n\n\n");
}


void char_print(task_param_t param)
{
	uint8_t i;

	printf("Processing Task:\t");

	for(i = 0; i < param.count; i++)
	{
		printf("%c",param.character);
	}

	printf("\tTask Done\n");
}

void * producer_thread(void *p_thread_arg)
{
	/* Copy (and casts) the thread argument, which by the way is the head of the task-list.*/
	task_t **pp_head = (task_t**) p_thread_arg;

	/* A variable to store the kernel thread ID. */
	pid_t tid;

	/* Glibc does not provide a wrapper for this system call;
	 * So it must be called through syscall. It returns the thread ID.*/
	tid = syscall(SYS_gettid);

	/* The scheduling priority (nice value) of the process, process group, or user,
	 * as indicated by which (1st parameter) and who (2nd parameter) is obtained
	 * with the getpriority() call and set with the setpriority() call.
	 * In order to change the niceness of a single thread, we should pass the thread ID
	 * as "who". The macro PRIO_PROCESS indicates we wish to manipulate the process
	 * (or thread) priority (and not user or group).
	 * The third parameter is the nice value, something between -20 and 19.
	 *
	 */
	int th_ret = setpriority(PRIO_PROCESS, tid, PRODUCER_NICENESS);

	if (th_ret < 0) /* Checks and exhibits if an error occurred when setting a new nice value. */
	{
		printf("ERROR: Failed to change the producer's nice value. Returned error is %d\n", th_ret);
		printf("Code %d= %s\n",th_ret,strerror(th_ret));
	}

	/* Gets the new nice value and shows it.*/
	th_ret = getpriority(PRIO_PROCESS, tid);

	printf("I'm the producer (tid-> %d )\n",tid);

	printf("Producer Niceness -> %d\n\n", th_ret);

	/* Makes use of the internal clock to choice the seed for "random number generation".
	 * Since time is continually changing, the seed is also changing.
	 * If the seed number remains the same, the sequence of numbers will be repeated for
	 * each run of the program. */
	srand(time(NULL));

	/* The data structure used to represent a new task. */
	task_param_t new_task;

	uint8_t i;

	/* While a key from the keyboard isn't pressed... */
	while(!kbhit())
	{
		/* A task is based on randomly generated character (ASCII table) and
		 * a randomly generated counter. A worker thread will process such task
		 * by printing the character "counter" times. */
		for(i = 0; i < PRODUCER_N_TASKS; i++)
		{
			new_task.count     = (rand() % 10) + 1;		// Generates a count value between 1 and 10.
			new_task.character = (rand() % 26) + 65;	//  between 65 and 90 (Capital letter from A to Z).

			/* Locks the mutex. */
			pthread_mutex_lock(&task_list_mutex);

			/* Adds a new task to the task list.
			 * Note that the pp_head always change when a new task is added, that is,
			 * it is a common variable shared between the threads. */
			task_add(pp_head,new_task);

			/* Increments (unlocks) the semaphore pointed to by task_list_count. So, the worker_threads,
			 * which probably will be locked at "sem_wait" call, will be informed that there is new tasks
			 * to be proceesed and consequently, released.*/
			sem_post(&task_list_count);

			/* Unlocks the mutex.*/
			pthread_mutex_unlock(&task_list_mutex);
		}

		/* Waits 1 second before generating another 10 tasks.*/
		sleep(1);

	}

	producer_alive = 0;

	/* Generates at least three more tasks in order to release the workers from the call sem_wait.*/
	for(i = 0; i < 3; i++)
	{
		new_task.count     = (rand() % 10) + 1;		// Generates a count value between 1 and 10.
		new_task.character = (rand() % 26) + 65;	//  between 65 and 90 (Capital letter from A to Z).

		/* Locks the mutex. */
		pthread_mutex_lock(&task_list_mutex);

		/* Adds a new task to the task list.
		 * Note that the pp_head always change when a new task is added, that is,
		 * it is a common variable shared between the threads. */
		task_add(pp_head,new_task);

		/* Increments (unlocks) the semaphore pointed to by task_list_count. So, the worker_threads,
		 * which probably will be locked at "sem_wait" call, will be informed that there is new tasks
		 * to be proceesed and consequently, released.*/
		sem_post(&task_list_count);

		/* Unlocks the mutex.*/
		pthread_mutex_unlock(&task_list_mutex);
	}

	printf("There is no task to produce!\n");

	/* Terminates the calling thread. */
	pthread_exit(NULL);

}

void * worker_thread_a(void *p_thread_arg)
{
	/* Copy (and casts) the thread argument, which by the way is the head of the task-list.*/
	task_t **pp_head = (task_t**) p_thread_arg;

	/* A variable to store a copy of the task to be processed. This approach avoids keeping
	 * the mutex locked while a task is being processed. Infstead, its content is copied and
	 * the mutex released thereafter.*/
	task_t current_task;

	/* A variable to store the kernel thread ID. */
		pid_t tid;

	/* Glibc does not provide a wrapper for this system call;
	 * So it must be called through syscall. It returns the thread ID.*/
	tid = syscall(SYS_gettid);

	/* The scheduling priority (nice value) of the process, process group, or user,
	 * as indicated by which (1st parameter) and who (2nd parameter) is obtained
	 * with the getpriority() call and set with the setpriority() call.
	 * In order to change the niceness of a single thread, we should pass the thread ID
	 * as "who". The macro PRIO_PROCESS indicates we wish to manipulate the process
	 * (or thread) priority (and not user or group).
	 * The third parameter is the nice value, something between -20 and 19. */
	int th_ret = setpriority(PRIO_PROCESS, tid, WORKER_A_NICENESS);

	if (th_ret < 0) /* Checks and exhibits if an error occurred when setting a new nice value. */
	{
		printf("ERROR: Failed to change the worker_thread_a's nice value. Returned error is %d\n", th_ret);
		printf("Code %d= %s\n",th_ret,strerror(th_ret));
	}

	/* Gets the new nice value and shows it.*/
	th_ret = getpriority(PRIO_PROCESS, tid);

	printf("I'm the Worker A (tid-> %d )\n",tid);

	printf("Worker A Niceness -> %d\n\n", th_ret);
  /* A variable to store a copy of the task to be processed. This approach avoids
   * keeping the mutex locked while a task is being processed. Instead, its content
   * is copied and the mutex released there after. */
  /* A variable to store a copy of the task to be processed. This approach avoids
   * keeping the mutex locked while a task is being processed. Instead, its content
   * is copied and the mutex released there after. */
  /* A variable to store a copy of the task to be processed. This approach avoids
   * keeping the mutex locked while a task is being processed. Instead, its content
   * is copied and the mutex released there after. */

	/* It will run while the producer is running. */
	while(producer_alive)
	{
		/* Blocks and waits for a new task to be added.
		 * (waits for a semaphore increment). */
		sem_wait(&task_list_count);

		/* Lock the mutex to process the current task. */
		pthread_mutex_lock(&task_list_mutex);

		/* Prints the current task list. */
		task_list_print(pp_head);

		/* Removes and copies the content of the task to
		 * be processed.*/
		current_task = task_remove(pp_head);

		/* Releases the mutex. */
		pthread_mutex_unlock(&task_list_mutex);

		printf("Worker A Processing count -> %d \n", worker_a++);

		/* Processes the task. */
		char_print(current_task.param);

	}

	/* Terminates the calling thread. */
	pthread_exit(NULL);
}

/* Exactly the same thread as Worker A. The only difference is the WORKER_B_NICENESS value. */
void * worker_thread_b(void *p_thread_arg)
{

	task_t **pp_head = (task_t**) p_thread_arg;
	task_t current_task;

	pid_t tid;
	tid = syscall(SYS_gettid);

	int th_ret = setpriority(PRIO_PROCESS, tid, WORKER_B_NICENESS);

	if (th_ret < 0) /* Checks and exhibits if an error occurred when setting a new nice value. */
	{
		printf("ERROR: Failed to change the worker_thread_b's nice value. Returned error is %d\n", th_ret);
		printf("Code %d= %s\n",th_ret,strerror(th_ret));
	}

	/* Gets the new nice value and shows it.*/
	th_ret = getpriority(PRIO_PROCESS, tid);

	printf("I'm the Worker B (tid-> %d )\n",tid);
	printf("Worker B Niceness -> %d\n\n", th_ret);

	while(producer_alive)
	{
		sem_wait(&task_list_count);

		pthread_mutex_lock(&task_list_mutex);

		task_list_print(pp_head);

		current_task = task_remove(pp_head);

		pthread_mutex_unlock(&task_list_mutex);

		printf("Worker B Processing count -> %d \n", worker_b++);

		char_print(current_task.param);
	}

	pthread_exit(NULL);
}

static int kbhit(void)
{
    struct termios oldt, newt;

    int ch;
    int oldf;

    /** Gets the attributes from the standard input file descriptor. */
    tcgetattr(STDIN_FILENO, &oldt);

    /** Enables raw input. (unprocessed). */
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    /** Sets the new attributes. */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    /** Gets the file access mode and status flags. */
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    /** Sets the same above read values + the O_NONBLOCK flag. */
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    /** Checks if there is a char on the standard terminal. (nonblock). */
    ch = getchar();

    /** Make changes now, without waiting for data to complete. */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    /** Removes the O_NONBLOCK flag. */
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    /** If any key was hitted, return true. And puts back the pressed key onto
     *  the terminal. */
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
