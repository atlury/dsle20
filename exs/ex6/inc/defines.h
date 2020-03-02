/*
 * defines.h
 *
 *  Created on: 11/01/2020
 *      Author: gbs
 */


#ifndef DEFINES_H_
#define DEFINES_H_

#define MDAN_LOG  "logs/mdanbin"
#define GYROS_LOG "logs/gyrosbin"

#define MDAN_QUEUE_NAME       "/mdan_queue"
#define GYROS_QUEUE_NAME      "/gyros_queue"
#define TELEMETRY_QUEUE_NAME  "/telemetry_queue"

#define QUEUE_MSG_SIZE 128

#define SERIAL_DEV "/dev/ttyS0"
#define SERIAL_BAUD 115200

#define VERBOSE 1

#define GPIO_PWM_PIN    23
#define GPIO_PWM_FREQ   10
#define GPIO_PWM_DUTY   0.5
#define GPIO_PWM_RANGE  1000
#define GPIO_IRQ_PIN    20

extern pthread_mutex_t mut;
extern pthread_cond_t cond;

#endif /* DEFINES_H_ */
