/*
 ============================================================================
 Name        : ex04.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program which demonstrates the Pthread library.
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#include <pthread.h>   /* The POSIX Threads Library. */
#include <stdint.h>	   /* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>	   /* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>	   /* General (standard) Library. (EXIT_SUCCESS. */
#include <string.h>    /* String manipulation. (strerror). */
#include <unistd.h>	   /* Complement (flags, constants, definitions..)
									for the POSIX API. */

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* The number of threads to create. */
#define N_THREADS 20

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief An example of function to be ran by a thread. Without arguments.
 */
void *thread_function_1(void *p_thread_arg);

/**
 * @brief An example of function to be ran by a thread. With arguments. See the
 * function definition.
 *
 * @param[in] p_thread_arg 		According to the POSIX Library, You should always
 * 							pass a single argument (void *) to the function that
 * 							your new thread will run. If you need more than one
 * 							argument, you must put those in a data structure.
 */
void *thread_function_2(void *p_thread_arg);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{

	/* The pthread_t data type acts as a handle for a new created thread. It stores
	 * a unique id which allows for manipulating such thread. */
	pthread_t my_threads[N_THREADS];

	int32_t th_ret;
	int32_t i;

	for(i=0; i < N_THREADS; i++)
	{

		/* Just a trick to differ odd and even values of the i variable. */
		if(i%2 == 0)
		{
			/* Attaches the thread_function1 to a new thread when "i" is even.
			 *
			 * The pthread_create function takes 4 parameters:
			 *
			 * <pthread_t *thread_id> - my_threads[i]
			 * This parameter stores a unique thread ID. It is returned from the
			 * pthread_create function call. From the pthread_create man page:
			 * "... this identifier is used to refer to the thread in subsequent
			 * calls to other pthreads (Library) functions".
			 *
			 * <const pthread_attr_t *attributes> - NULL
			 * This structure is used to change
			 * the attributes of the thread creation process. When NULL is passed,
			 * the new thread is created with the default attributes.
			 *
			 * <void *(*thread_function)(void *)> - thread_function_1
			 * The third argument must have a signature of a function that takes a
			 * SINGLE void pointer as argument and returns a void pointer. This is because
			 * there is no way for a start function know what kind of data the developer
			 * wishes to pass into and return. This is the function the created thread
			 * will run.
			 *
			 * <void *arguments> - NULL
			 * the fourth and last parameter is a void pointer and it represents the
			 * arguments of the function passed in as third parameter. It must be "casted"
			 * before and inside the function, when necessary. It is allowed only a single
			 * parameter in the ptrhead_create function, so, if you wish to design a function
			 * with more than one parameter, you should group them into a data structure,for
			 * example. When NULL is used, no arguments are passed to the function.
			 *
			 * */
			th_ret = pthread_create(&my_threads[i], NULL, thread_function_1, NULL);

			if(th_ret) /* Checks and exhibits if an error occurred when creating a new thread. */
			{
				printf("ERROR: Failed to call pthread_create(). Returned error is %d\n", th_ret);
				printf("Code %d= %s\n",th_ret,strerror(th_ret));

				return EXIT_FAILURE;
			}

		}
		else
		{
			/* Attaches the thread_function2 to a new thread when "i" is odd. It is very similar to
			 * the previous process. However, note that in this case, the variable "i" is passed as
			 * an argument to the thread_function_2. */
			th_ret = pthread_create(&my_threads[i], NULL, thread_function_2, (void *)i);

			if (th_ret) /* Checks and exhibits if an error occurred when creating a new thread. */
			{
				printf("ERROR: Failed to call pthread_create(). Returned error is %d\n", th_ret);
				printf("Code %d= %s\n",th_ret,strerror(th_ret));

				return EXIT_FAILURE;
			}

		}

	}

  printf(">> main(): Created %u threads.\n\n", i);

  /* In addition to closing the main program, when the pthread_exit is called by
   * the Main function, it allows other threads to continue execution, after its
   * closure. */
  pthread_exit(NULL);
}

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

void *thread_function_1(void *p_thread_arg)
{
  /* Takes no arguments.*/
  printf("Hello Embedded World! I'm a Thread running function 1!\n\n");

  /* Terminates the calling thread. */
  pthread_exit(NULL);
}

void *thread_function_2(void *p_thread_arg)
{
  /* Casts the void* p_thread_arg argument to int32_t, which is the type of
   * the argument passed in the previously called pthread_create function. */
  int32_t p_thread_id = (int32_t) p_thread_arg;

  sleep(2); /* Just a 2s sleep, in order to demonstrate that the Linux scheduler
             * does not have a fixed order for scheduling threads and processes.*/

  printf("Hello Embedded World! I'm the Thread %d and I'm running function 2!\n\n", p_thread_id);

  /* Terminates the calling thread. */
  pthread_exit(NULL);
}
