/*
 * structs.h
 *
 *  Created on: 29/02/2020
 *      Author: gbs
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct task_param_t
{
	char character;
	uint8_t count;
}task_param_t;

typedef struct task_t{
	task_param_t param;
	struct task_t *p_next;
}task_t;

#endif /* STRUCTS_H_ */

