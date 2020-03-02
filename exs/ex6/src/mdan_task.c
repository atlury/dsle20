/*
 * mdan_task.c
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

void * mdan_task(void *p_arg)
{

  mqd_t main_queue;

  mdan_t mdan;

  static struct timespec tm_start_int, tm_stop_int;

  FILE *p_mdan_fd;

  p_mdan_fd = fopen(MDAN_LOG, "r");

  if (p_mdan_fd == NULL)
  {
    printf("error mdan_log_file\n");
  }

  uint32_t mdan_count = 0;
  float time_ms;

  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = QUEUE_MSG_SIZE;
  attr.mq_curmsgs = 0;

  main_queue = mq_open(MDAN_QUEUE_NAME, O_WRONLY, S_IRUSR | S_IWUSR, &attr);

  if (main_queue < 0)
  {
    printf("Error opening main queue (mdan task)\n");
  }

  if (VERBOSE)
  {
    printf("Mdan task initialized!\n");
  }

  clock_gettime(CLOCK_MONOTONIC, &tm_start_int);


  while(fread(&mdan, sizeof(mdan_t), 1, p_mdan_fd))
  {

    pthread_mutex_lock(&mut);
    pthread_cond_wait(&cond, &mut);
    pthread_mutex_unlock(&mut);

    clock_gettime(CLOCK_MONOTONIC, &tm_stop_int);

    time_ms = (tm_stop_int.tv_sec - tm_start_int.tv_sec) * 1000
            + ((tm_stop_int.tv_nsec - tm_start_int.tv_nsec) * 0.001)*0.001;

    tm_start_int = tm_stop_int;

    mdan_count++;

    mdan.count   = mdan_count;
    mdan.time_ms = time_ms;

    if ( mq_send(main_queue, (char*)&mdan, QUEUE_MSG_SIZE, 0) < 0 )
    {
      printf("error when sending from mdan_task to main\n");
    }
  }

  fclose(p_mdan_fd);

  mq_close(main_queue);
  mq_unlink(MDAN_QUEUE_NAME);

  pthread_exit(NULL);
}

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

