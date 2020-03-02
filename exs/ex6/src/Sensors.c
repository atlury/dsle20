/*
 ============================================================================
 Name        : Sensors.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A full application
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#include <errno.h>	  /* Used to view the number of the last occurred error.*/
#include <mqueue.h>	  /* POSIX message queues. */
#include <pthread.h>	/* POSIX threads. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>	  /* String manipulation. (memcpy, memset, etc). */

#include "pigpio.h"

#include "structs.h"
#include "defines.h"
#include "mdan_task.h"
#include "gyro_task.h"
#include "telemetry_task.h"

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief A callback function which is attached to GPIO Pin. This function is
 * called always an edge transition is detected. The transition type is set by
 * the gpioSetISRFunc function.
 *
 *
 *
 * @param[in] gpio 		The gpio pin which has changed its edge level.
 * @param[in] level		The type of detected level change (transition).
 * @param[in] tick		The number of microseconds since boot.
 *
 * WARNING: From PIGPIO Library documentation: The tick level wraps around from
 * 			4294967295 to 0 roughly every 72 minutes.
 *
 */
static void signal_handler_io(
		int gpio,
		int level,
		uint32_t tick);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

/* A variable to store the number of microseconds since boot to the current
 * interrupt. */
uint32_t tick_spent;

/* The following both variables are used in the process of broadcasting a signal
 * to multiple threads (tasks). Such process is described in the tasks's source
 * files. Independently of their use, they must be initialized. They must be
 * globally declared in order to be available for multiple objects files.
 * */
pthread_mutex_t mut  = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond  = PTHREAD_COND_INITIALIZER;

//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{
	tick_spent = 0;

	mdan_t 	  mdan;
	gyros_t   gyros;
	sensors_t sensors;

	/* Fills the first "sizeof(structure)"bytes of the respective data structure
	 * with the value 0. In other words, zeroes the data structures. */
	memset(&mdan   , 0, sizeof(mdan_t));
	memset(&gyros  , 0, sizeof(gyros_t));
	memset(&sensors, 0, sizeof(sensors_t));

	/* The mqd_t data type represents the message queue file descriptor.*/
	mqd_t mdan_queue;
	mqd_t gyros_queue;
	mqd_t telemetry_queue;

	/* The data type mq_attr is required to change the default queue parameters.
	 * It is composed by the following fields:
	 *
	 * mq_flags: 	Flags (ignored for mq_open() call). It is used to retrieve
	 * 				the queue defined flags at the moment of opening it.
	 *
	 * mq_maxmsg:	Defines the size (# of messages) of a queue.
	 * mq_msgsize:	Defines the size in bytes of each message.
	 * mq_curmsgs:	# of messages currently in queue. (ignored for mq_open()
	 * 	call). Both mq_flags and mq_curmsgs are retrieved by the mq_getattr()
	 * 	call.
	 *
	 * */
	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = QUEUE_MSG_SIZE;
	attr.mq_curmsgs = 0;

	/* Creates or opens a new/existing POSIX message queue. In order to create
	 * a queue, the parameter O_CREAT must be inserted. Usually, it is necessary
	 * to pass 2 arguments for opening a queue. However, when the flag O_CREAT
	 * is specified, two additional arguments must be supplied:
	 *
	 * MDAN_QUEUE_NAME: (mandatory) A const char * which names (identifies) the
	 * queue. It must have a form "/somename".
	 *
	 * O_RDONLY | O_CREAT: (mandatory) The o_flag argument specifies flags that
	 * defines the operation types of the queue. In this case:
	 * 		- O_RDONLY: Opens the queue to receive (read) messages only;
	 * 		- O_CREAT:  Create a new queue if a queue named MDAN_QUEUE_NAME
	 * 					doesn't exists;
	 *
	 * S_IRUSR | S_IWUSR: (required only if the O_CREAT flag is set) The mode
	 * argument specifies the permissions to be placed on the new queue. (OS
	 * related, similar to the open() system call).
	 * 		- S_ISUSR: 	Read permission for the owner of the file (queue);
	 * 		- S_IWUSR:	Write permission for the owner of the file (queue);
	 *
	 *
	 * */
	mdan_queue 		= mq_open(MDAN_QUEUE_NAME,
							O_RDONLY| O_CREAT,
							S_IRUSR | S_IWUSR,
										&attr);

	gyros_queue	 	= mq_open(GYROS_QUEUE_NAME,
							 O_RDONLY| O_CREAT,
							 S_IRUSR | S_IWUSR,
							 	 	 	 &attr);

	telemetry_queue = mq_open(TELEMETRY_QUEUE_NAME,
								 O_WRONLY| O_CREAT, /* Opens the queue to send
							 	 	 	 	 	 	 (write) messages only; */
								 S_IRUSR | S_IWUSR,
								 	 	 	 &attr);

	/* Error verification for the mq_open calls. On error, mq_open returns -1
	 * with errno set to indicate the error. */
	if (mdan_queue < 0)
	{
		printf("error opening mdan_queue (main task): %s\r\n",
				strerror(errno));
	}

	if (gyros_queue < 0)
	{
		printf("error opening gyros_queue (main task): %s\r\n",
				strerror(errno));
	}

	if (telemetry_queue < 0)
	{
		printf("error opening telemetry_queue (main task): %s\r\n",
				strerror(errno));
	}

	/* Must be called before using the PIGPIO library.*/
	if (gpioInitialise() < 0)
	{
		printf("PIGPIO init error\n");
	}

	/* Sets the GPIO_PWM_PIN as output. It is used to generate a pwm.*/
	if (gpioSetMode(GPIO_PWM_PIN, PI_OUTPUT) != 0)
	{
		printf("Error PWM PIN\n");
	}

	/* Sets the GPIO_IRQ_PIN as input. It is used to attach a callback function
	 * to be ran always a edge transition is detected in such pin.*/
	if (gpioSetMode(GPIO_IRQ_PIN, PI_INPUT) != 0)
	{
		printf("Error IRQ PIN\n ");
	}

	int freq_ret;

	/* Sets a GPIO_PWM_FREQ Frequency, in Hz, for the GPIO_PWM_PIN.
	 * It returns the numerically closest frequency if OK.
	 * The frequency depends on other factors, please for
	 * further details check:
	 * http://abyz.me.uk/rpi/pigpio/cif.html#gpioSetPWMfrequency*/
	freq_ret = gpioSetPWMfrequency(GPIO_PWM_PIN, GPIO_PWM_FREQ);

	if (VERBOSE)
	{
		printf("Freq set: %d\n",freq_ret);
	}

	/* Selects the duty-cycle range to be used for the GPIO.
	 * Subsequent calls to gpioPWM will use a duty-cycle
	 * between 0 (off) and GPIO_PWM_RANGE (fully on).
	 * The range value can be: 25-40000 */
	gpioSetPWMrange(GPIO_PWM_PIN, GPIO_PWM_RANGE);

    /* Sets the GPIO_PWM_PIN duty-cycle. */
	gpioPWM(GPIO_PWM_PIN, (int)(GPIO_PWM_RANGE*GPIO_PWM_DUTY));

	/**
	 * Registers the signal_handler_io function to be called
	 * whenever an interrupt occurs on the GPIO_IRQ_PIN.
	 * The FALLING_EDGE parameter specifies an interrupt for falling edges.
	 * The parameter 100 indicates a 100ms timeout.
	 */
	gpioSetISRFunc(GPIO_IRQ_PIN, FALLING_EDGE, 100, signal_handler_io);

	/* The pthread IDs. One for each task. */
	pthread_t mdan_task_id;
	pthread_t gyros_task_id;
	pthread_t telemetry_task_id;

	/* Creates the mdan, gyro and telemetry tasks. The first NULL argument is
	 * used to change the default thread attributes (they aren't changed) and
	 * the second one is an argument for the task routine. */
	pthread_create(&mdan_task_id	 , NULL, mdan_task 	   , NULL);
	pthread_create(&gyros_task_id	 , NULL, gyro_task	   , NULL);
	pthread_create(&telemetry_task_id, NULL, telemetry_task, NULL);

	/* A buffer used to receive messages from the queue.*/
	char queue_buffer[QUEUE_MSG_SIZE];

	/* An interrupt counter. */
	uint32_t int_count = 0;
	/* An auxiliary variable to print (verbose) the sensory data each second. */
	uint8_t int_verb = 0;

	while(1)
	{
		/* Waits (blocks) for a message from mdan_task. It is possible to
		 * turn a mq_receive call in a non-blocking call by passing the flag
		 * O_NONBLOCK flag in the mq_open call. The parameters are:
		 *
		 * 		-- mdan_queue:   	The message queue file descriptor, which
		 * 							represents a queue to receive message from;
		 *
		 * 		-- queue_buffer: 	The buffer where the received message will
		 * 							be copied to;
		 *
		 * 		-- QUEUE_MSG_SIZE:	The size in bytes of the message. This is
		 * 							the same argument as the one defined in the
		 * 							attr.mq_msgsize variable;
		 *
		 * 		-- NULL:			This is an input parameter to read the
		 * 							priority associated with the received msg.
		 * 							A priority can be defined in the mq_send
		 * 							call.
		 * 							*/
		if( mq_receive(mdan_queue, queue_buffer, QUEUE_MSG_SIZE, NULL) )
		{
			/* Copies the received message, stored in the queue_buffer, to the
			 * mdan data structure object. */
			memcpy(&mdan, queue_buffer, sizeof(mdan_t));
		}
		else
		{
			printf("ERROR when receiving data from mdan_queue\n");
		}

		/* The same process as the above one. Just changed from mdan to gyros.*/
		if( mq_receive(gyros_queue, queue_buffer, QUEUE_MSG_SIZE, NULL) )
		{
			memcpy(&gyros, queue_buffer, sizeof(gyros_t));
		}
		else
		{
			printf("ERROR when receiving data from gyros_queue\n");
		}

		/* Increments the number of interrupts. */
		int_count++;
		int_verb++;

		/* Updates the sensors variable, which by the way is a sensors_t data
		 * structure. */
		sensors.count = int_count;
		sensors.mdan = mdan;
		sensors.gyro = gyros;

		/* Sends the collected sensors data, recently received from the mdan and
		 * gyro tasks, to telemetry task.
		 *
		 * 		-- telemetry_queue:	The message queue file descriptor, which
		 * 							represents a queue to send message to;
		 *
		 * 		-- (char*)&sensors: A pointer to the beginning of the data to be
		 * 							sent;
		 *
		 * 		-- QUEUE_MSG_SIZE:	The number of bytes to be sent, starting
		 * 							from the above pointer;
		 *
		 * 		-- 0:				The priority of the message to be sent;
		 **/
		if (mq_send(telemetry_queue, (char*)&sensors, QUEUE_MSG_SIZE, 0) < 0)
		{
			printf("Main task: error when sending from main to telemetry \n");
		}

		/* Prints the sensory data at each second (10Hz). */
		if (VERBOSE && int_verb == 10)
		{
			int_verb = 0;

			printf("\t\t Accel X\t Accel Y\t Accel Z\n");
			printf("DeltaV\t\t%2.6f\t%2.6f\t%2.6f\n",
					mdan.accel_x,
					mdan.accel_y,
					mdan.accel_z);

			printf("Accel Temp\t%2.4f\t\t%2.4f\t\t%2.4f\n",
					mdan.accel_x_temp,
					mdan.accel_y_temp,
					mdan.accel_z_temp);

			printf("VF Temp\t\t%2.4f\t\t%2.4f\t\t%2.4f\n",
					mdan.vf_x_temp,
					mdan.vf_y_temp,
					mdan.vf_z_temp);

			printf("Gyros\t\t%2.6e\t%2.6e\t%2.6e\n",
					gyros.gyro_x,
					gyros.gyro_y,
					gyros.gyro_z);

			printf("Gyros Temp\t%2.2f\t\t%2.2f\t\t%2.2f\n",
					gyros.gyro_x_temp,
					gyros.gyro_y_temp,
					gyros.gyro_z_temp);

			printf("Cycles\t\t%4u\t\t%4u\t\t%4u\n\n",
							mdan.count,
							gyros.count,
							sensors.count);
		}


	}

	/* Close (frees) the message queue file descriptors. */
	mq_close(mdan_queue);
	mq_close(gyros_queue);
	mq_close(telemetry_queue);

	/* Deletes the created queues, including their current messages. */
	mq_unlink(MDAN_QUEUE_NAME);
	mq_unlink(GYROS_QUEUE_NAME);
	mq_unlink(TELEMETRY_QUEUE_NAME);

	/* Similar to the gpioInitialise function, this one must be called at the end of
	 * your program.*/
	gpioTerminate();

	return EXIT_SUCCESS;
}


//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================


static void signal_handler_io(
		int gpio,
		int level,
		uint32_t tick)
{
	/* Sends a signal to wake up every thread waiting for it. */
	pthread_cond_broadcast(&cond);

	/* Prints the type of occurred interrupt and the number of
	 * spent ticks since last interrupt.
	 * */
	//printf("Interrupt Occurred! level-> %d, tick-> %d\n\n",
	//		level,
	//		tick - tick_spent);

	/* Updates the tick_spent variable with the number of
	 * ticks since boot. */
	tick_spent = tick;
}














