/*
 * telemetry_task.c
 *
 *  Created on: 11/01/2020
 *      Author: gbs
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#include <errno.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "defines.h"
#include "pigpio.h"
#include "structs.h"

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief Encapsulates the data structure package, of type sensors_t, into a
 * 		  buffer in order to send it via telemetry (serial port).
 *
 * @param[in] package   A sensors_t data structure containing the output data.
 *
 * @return              A buffer to be sent over serial port.
 */
static char * tlm_get_pack(
    sensors_t sensors);

 /**
  * @brief Calculates a simple CHK16 of the input buffer. The calculation is
  *        performed as follows:
  *
  *      A and B are two uint16_t variables assigned with:
  *
  *      A = 0x00FF; B = 0x00FF;
  *
  *      A loop that goes from the last to the initial byte of the buffer. For
  *      each byte, the following sums are computed:
  *
  *      A = A + byte;
  *      B = A + B;
  *
  *      After the loop, a variable uint16_t C is assigned as:
  *
  *      A = ( A & 0xFF) + (A >> 8); (sums both bytes of A)
  *      B = ( B & 0xFF) + (B >> 8); (sums both bytes of B)
  *
  *      C = (A << 8) | B;
  *
  *      that is, C is the result of the concatenation between the least
  *      significant byte of A shifted 8 bits left and the least significant
  *      byte of B.
  *
  * @param[in] buffer    The frame buffer to compute the CHK16.
  *
  * @return              The computed CHK16.
  */
static uint16_t chk_calc(
    char *p_buffer);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================


//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

void * telemetry_task(void *p_arg)
{
  mqd_t main_queue;
  sensors_t sensors;

  static struct timespec tm_start_int, tm_stop_int;

  /* A file descriptor to manipulate the SERIAL port.*/
  int serial_fd;

  char queue_buffer[QUEUE_MSG_SIZE];

  /* A variable to store the telemetry frame. */
  char *p_frame_out;

  /* A sent packets counter. */
  uint32_t telemetry_count = 0;

  float time_ms;

//==============================================================================
//                     CONFIGURING THE TASK
//==============================================================================

	struct mq_attr attr;

	attr.mq_flags = 0;					/* Flags: 0 or O_NONBLOCK */
	attr.mq_maxmsg = 10;				/* Max. # of messages on queue */
	attr.mq_msgsize = QUEUE_MSG_SIZE;   /* Max. message size (bytes) */
	attr.mq_curmsgs = 0;				/* # of messages currently in queue */

	/* Opens a queue to receive messages only, from main task. */
	main_queue = mq_open( TELEMETRY_QUEUE_NAME, O_RDONLY, S_IRUSR | S_IWUSR, &attr);

	/* Opens the serial port SERIAL_DEV and sets it with SERIAL_BAUD baud rate.
	 * */
	serial_fd = serOpen(SERIAL_DEV, SERIAL_BAUD, 0);

	if (serial_fd < 0)
	{
		printf("Telemetry task: - Failed to open SERIAL_DEV %s\r\n",
				strerror(errno));
	}

  if ( main_queue < 0 )
  {
  	printf("Telemetry task: - Failed to open telemetry_queue %s\r\n",
  			strerror(errno));
  }

  if(VERBOSE)
  {
	  printf("Telemetry task initialized!\n");
  }


//==============================================================================
//                               RUNNING THE TASK
//==============================================================================

	clock_gettime(CLOCK_MONOTONIC,  &tm_start_int);

  while(1)
  {
  	/* Waits (blocks) for a message from main task. */
  	if(mq_receive (main_queue, queue_buffer, QUEUE_MSG_SIZE, NULL))
	  {
  		/* When received, copies the data to the sensors variable. */
		memcpy(&sensors,&queue_buffer,sizeof(sensors_t));
	  }
	  else
	  {
		  printf("Telemetry Task: Failed to receive data from Main task:%s\n",
				  strerror( errno ));
	  }
    clock_gettime(CLOCK_MONOTONIC,  &tm_stop_int);

    time_ms = (tm_stop_int.tv_sec - tm_start_int.tv_sec) * 1000
                                  + ((tm_stop_int.tv_nsec - tm_start_int.tv_nsec) * 0.001) *0.001;

    clock_gettime(CLOCK_MONOTONIC,  &tm_start_int);

    telemetry_count++;

    /* Gets (mounts) the telemetry packet, from the received data (sensors),
     * to be sent over serial. */
    p_frame_out = tlm_get_pack(sensors);

    /* Sends p_frame_out[3] bytes, starting at the beginning of the telemetry
     * packet, over the serial port. Note: The p_frame_out[3] index contains
     * the size in bytes of the telemetry packet. */
    if (serWrite(serial_fd, (char*)p_frame_out, p_frame_out[3]) == 0)
    {
      if ((telemetry_count % 10) == 0)
      {
        printf("Tlm_packet successfully sent!\n");
        printf("Tlm count: %u\t Time_ms:%f\n\n", telemetry_count, time_ms);
      }
    }

    /* Frees the previously allocated memory, inside the tlm_get_packet,
     * for the telemetry packet. */
    free(p_frame_out);
  }

//==============================================================================
//                               FINISHING THE TASK
//==============================================================================

    mq_close(main_queue);
    mq_unlink(TELEMETRY_QUEUE_NAME);
    close(serial_fd);

    printf("Telemetry task finished!\n");

    pthread_exit(NULL);
}

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

static char * tlm_get_pack(
    sensors_t sensors)
{
    char *p_frame_out = malloc(102 * sizeof( char));

    /** Message start. */
    p_frame_out[0] = 0xAB;
    p_frame_out[1] = 0x55;

    /** Message ID. */
    p_frame_out[2] = 0x08;

    /** Message size (in bytes). */
    p_frame_out[3] = 102;

    /* The recommended way to copy data from a structure to a frame of bytes is
     * using the memcpy for each variable or doing manual byte shifting. This
     * approach is recommended for softening endianness incompatibility issues.
     *
     * The main problem relies on struct padding, which is the process of
     * inserting empty bytes between variables (memory addresses) in order to
     * align the data in memory. Another problem occurs when the structure has
     * a pointer inside, because the allocated memory for such pointer will not
     * be contiguous in the memory, regarding the allocated memory for the
     * structure.
     *  */
    memcpy(&p_frame_out[4] , &sensors.mdan.count	   , sizeof(uint32_t));
    memcpy(&p_frame_out[8] , &sensors.mdan.accel_x	   , sizeof(float));
    memcpy(&p_frame_out[12], &sensors.mdan.accel_x_temp, sizeof(float));
    memcpy(&p_frame_out[16], &sensors.mdan.vf_x_temp   , sizeof(float));
    memcpy(&p_frame_out[20], &sensors.mdan.accel_y	   , sizeof(float));
    memcpy(&p_frame_out[24], &sensors.mdan.accel_y_temp, sizeof(float));
    memcpy(&p_frame_out[28], &sensors.mdan.vf_y_temp   , sizeof(float));
    memcpy(&p_frame_out[32], &sensors.mdan.accel_z	   , sizeof(float));
    memcpy(&p_frame_out[36], &sensors.mdan.accel_z_temp, sizeof(float));
    memcpy(&p_frame_out[40], &sensors.mdan.vf_z_temp   , sizeof(float));
    memcpy(&p_frame_out[44], &sensors.mdan.v_5_ad	   , sizeof(float));
    memcpy(&p_frame_out[48], &sensors.mdan.v_5_reg	   , sizeof(float));
    memcpy(&p_frame_out[52], &sensors.mdan.v_15_ad	   , sizeof(float));
    memcpy(&p_frame_out[56], &sensors.mdan.v_m15_ad	   , sizeof(float));
    memcpy(&p_frame_out[60], &sensors.mdan.time_ms	   , sizeof(float));

    memcpy(&p_frame_out[64], &sensors.gyro.count	   , sizeof(uint32_t));
    memcpy(&p_frame_out[68], &sensors.gyro.gyro_x	   , sizeof(float));
    memcpy(&p_frame_out[72], &sensors.gyro.gyro_x_temp , sizeof(float));
    memcpy(&p_frame_out[76], &sensors.gyro.gyro_y	   , sizeof(float));
    memcpy(&p_frame_out[80], &sensors.gyro.gyro_y_temp , sizeof(float));
    memcpy(&p_frame_out[84], &sensors.gyro.gyro_z	   , sizeof(float));
    memcpy(&p_frame_out[88], &sensors.gyro.gyro_z_temp , sizeof(float));
    memcpy(&p_frame_out[92], &sensors.gyro.time_ms	   , sizeof(float));

    memcpy(&p_frame_out[96], &sensors.count			   , sizeof(uint32_t));

    uint16_t chk;

    /* Computes the CHK16 for the mounted frame (packet). */
    chk = chk_calc(p_frame_out);

    /* Splits the CHK16 between the last two bytes. */
    p_frame_out[100] = chk >> 8;
    p_frame_out[101] = chk;

    return p_frame_out;
}

static uint16_t chk_calc(
    char *p_buffer)
{
	uint16_t sum_a = 0xff;
	uint16_t sum_b = 0xff;
	uint16_t frame_size;
	uint16_t index;

    frame_size = p_buffer[3] - 3;

    for( index = frame_size; index > 0; index--)
    {
        sum_a += p_buffer[index];
        sum_b += sum_a;
    }

    sum_a += p_buffer[index];
    sum_b += sum_a;

    sum_a = (sum_a & 0xff) + (sum_a >> 8);
    sum_b = (sum_b & 0xff) + (sum_b >> 8);

    sum_a &= 0xFF;
    sum_b &= 0xFF;

    return ((sum_a << 8) | sum_b);
}
