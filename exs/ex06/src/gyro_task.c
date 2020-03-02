/*
 * gyro_task.c
 *
 *  Created on: 11/01/2020
 *      Author: gbs
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#include <mqueue.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "defines.h"
#include "structs.h"

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

/* This thread has exactly the same format as the mdan_task. The only difference
 * is the type of data read (gyros here, while accelerometers on the mdan task).
 * */
void * gyro_task(void *p_arg)
{
  mqd_t main_queue;
  gyros_t gyros;

  static struct timespec tm_start_int, tm_stop_int;

  FILE *p_gyros_fd;

  p_gyros_fd = fopen(GYROS_LOG, "r");

  if (p_gyros_fd == NULL)
  {
    printf("error gyros_log_file\n");
  }

  uint32_t gyros_count = 0;
  float time_ms;

  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = QUEUE_MSG_SIZE;
  attr.mq_curmsgs = 0;

  main_queue = mq_open(GYROS_QUEUE_NAME, O_WRONLY, S_IRUSR | S_IWUSR, &attr);

  if (main_queue < 0)
  {
    printf("Error opening main queue (gyro task)\n");
  }

  if (VERBOSE)
  {
    printf("Gyro task initialized!\n");
  }

  clock_gettime(CLOCK_MONOTONIC, &tm_start_int);

  while(fread(&gyros, sizeof(gyros_t), 1, p_gyros_fd))
  {
    pthread_mutex_lock(&mut);
    pthread_cond_wait(&cond, &mut);
    pthread_mutex_unlock(&mut);

    clock_gettime(CLOCK_MONOTONIC, &tm_stop_int);

    time_ms = (tm_stop_int.tv_sec - tm_start_int.tv_sec) * 1000
            + ((tm_stop_int.tv_nsec - tm_start_int.tv_nsec)*0.001)*0.001;

    tm_start_int = tm_stop_int;

    gyros_count++;

    gyros.count = gyros_count;
    gyros.time_ms = time_ms;

    if(mq_send(main_queue, (char *)&gyros, QUEUE_MSG_SIZE, 0) < 0)
    {
      printf("error when sending from gyros_task to main\n");
    }
  }

  fclose(p_gyros_fd);

  mq_close(main_queue);
  mq_unlink(GYROS_QUEUE_NAME);

  pthread_exit(NULL);
}

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================


