/*
 * gyro_task.h
 *
 *  Created on: 11/01/2020
 *      Author: gbs
 */

#ifndef GYRO_TASK_H_
#define GYRO_TASK_H_

//==============================================================================
//                    INTERFACE MACROS AND DATATYPE DEFINITIONS
//==============================================================================

//==============================================================================
//                          PUBLIC FUNCTIONS PROTOTYPES
//==============================================================================

/**
 * @brief The gyro task is responsible for reading the gyrometers data. At
 *    each synchronism signal, which by the way is controlled by the
 *    pthread_cond_broadcast (main task, the sender) and the
 *    pthread_cond_wait (mdan and gyro tasks, the receivers), the gyro task
 *    reads the simulated sensor (gyros log) and then sends the recently read
 *    data to the main thread through a message queue.
 *
 */
void * gyro_task(void *p_arg);

#endif /* GYRO_TASK_H_ */
