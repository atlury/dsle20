/*
 * telemetry.h
 *
 *  Created on: 11/01/2020
 *      Author: gbs
 */

#ifndef TELEMETRY_TASK_H_
#define TELEMETRY_TASK_H_

//==============================================================================
//                    INTERFACE MACROS AND DATATYPE DEFINITIONS
//==============================================================================

//==============================================================================
//                          PUBLIC FUNCTIONS PROTOTYPES
//==============================================================================

/**
 * @brief The telemetry task is responsible for receiving the accelerometers and
 *    gyrometers data, from the main thread through a message queue, and send
 *    them by telemetry. In summary, it receives the data, packs them in a
 *    frame of bytes and send them over a serial port.
 */
void * telemetry_task(void *p_arg);

#endif /* TELEMETRY_TASK_H_ */
