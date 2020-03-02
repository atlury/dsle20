/*
 * mdan_task.h
 *
 *  Created on: 11/01/2020
 *      Author: gbs
 */

#ifndef MDAN_TASK_H_
#define MDAN_TASK_H_

//==============================================================================
//                    INTERFACE MACROS AND DATATYPE DEFINITIONS
//==============================================================================

//==============================================================================
//                          PUBLIC FUNCTIONS PROTOTYPES
//==============================================================================

/**
 * @brief The mdan task is responsible for reading the accelerometers data. At
 *    each synchronism signal, which by the way is controlled by the
 *    pthread_cond_broadcast (main task, the sender) and the
 *    pthread_cond_wait (mdan and gyro tasks, the receivers), the mdan task
 *    reads the simulated sensor (mdan log) and then sends the recently read
 *    data to the main thread through a message queue.
 *
 */
void * mdan_task(void *p_arg);

#endif /* MDAN_TASK_H_ */
