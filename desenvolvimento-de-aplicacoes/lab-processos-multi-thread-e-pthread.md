# \[LAB\] Processos Multi-thread e PTHREAD

Uma das ferramentas mais importantes no desenvolvimento de uma aplicação em um sistema Linux embarcados é a utilização de multi-threading. Isto é, realizar os recursos disponíveis pelo kernel Linux \(escalonador, gerenciamento de recuso, ICP e etc\) para realizar o processamento de diversas tarefas simultaneamente.

Nesta atividade, vamos entender os conceitos básicos da criação de uma aplicação multi-threading.

### Utilizando a Biblioteca `PTHREAD`

Nesta primeira implementação vamos realizar a criação de `N_THREADs` threads genéricas e observar seu funcionamento. 

Para declarar uma thread devemos utilizar o tipo `pthread_t` já implementadona biblioteca `PTHREAD`. Esta variável armazenará um ID único que representa a thread criada, isto permite sua manipulação atuando como um handler para a thread, mecanismo similar aos file descriptors já utilizados.

```c
#define N_THREADS 20

pthread_t my_threads[N_THREADS];
```

Para criar, de fato, uma thread no sistema devemos utilizar a função `pthread_create`. Esta função espera como parâmetros o endereço do nosso handler `pthread_t`, um ponteiro para a estrutura de atributos \(caso deseje alterar os atributos padrões\) da thread, a função a ser atrelada a esta thread \(callback\) e por último um quarto parâmetro que representa um parâmetro a ser passado para a função.

O processo de criação da thread resulta em um número inteiro que representa se houve ou não problemas durante a criação da thread.

Para a prática iremos criar dois tipos de thread, estas serão definidas por um índice de criação. Caso o índice em questão seja par, a thread criada será vinculada à dunção `thread_function_1`. Caso o índice seja impar, esta thread será vinculada a uma função `thread_function_2` que recebe como parâmetro o índice, `i`,  atual.

```c
int32_t th_ret;
int32_t i;
	
for(i=0; i < N_THREADS; i++)
{
	if(i%2 == 0)
	{
		th_ret = pthread_create(&my_threads[i], NULL, thread_function_1, NULL);
	}
	else
	{
		th_ret = pthread_create(&my_threads[i], NULL, thread_function_2, i);
	}
}
```

Para encerrar uma thread basta executar a função `pthread_exit` e passar o handler da thread desejada, caso o argumento seja `NULL`, a thread encerrada será a própria que evocou a função.

```c
printf(">> main(): Created %u threads.\n\n", i);

pthread_exit(NULL);
```

Por fim, devemos definir o escopos das funções vinculadas as thread. Na função `thread_function_1` iremos apenas executar um simples `printf` e deletar a thread.

```c
void *thread_function_1(void *p_thread_arg)
{
	printf("Hello Embedded World! I'm a Thr	ead running function 1!\n\n");
	
	pthread_exit(NULL);
}
```

Já para a `thread_function_2` vamos realizar a conversão do nosso parâmetro, passado para a thread. E então, colocar a thread para dormir através do comando `sleep`. Por fim, iremos executar um `printf` com uma mensagem utilizando o argumento convertido e deletar a thread.

```c
void *thread_function_2(void *p_thread_arg)
{
	int32_t p_thread_id = (int32_t) p_thread_arg;

	sleep(2); 
	
	printf("Hello Embedded World! I'm the Thread %d and I'm running function 2!\n\n",p_thread_id);

	pthread_exit(NULL);
}
```

Ao executar o programa devemos observar o efeito da criação das threads, a ordem com que os eventos acontecem e também o impacto da função `sleep`.

```c
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
	 	 	 	 does not have a fixed order for scheduling threads and processes.*/

	printf("Hello Embedded World! I'm the Thread %d and I'm running function 2!\n\n",p_thread_id);

	/* Terminates the calling thread. */
	pthread_exit(NULL);
}
```

