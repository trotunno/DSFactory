/*
 * queue.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Dylan
 */

#ifndef _QUEUE_QUEUE_H
#define _QUEUE_QUEUE_H

#include "../generalpurposebuffer/generalpurposebuffer.h"

// enum for queue types.
// STATIC queues are intended for windowing purposes where data history is needed.
// DYNAMIC queues are intended for queueing up samples to be processed FIFO style.
typedef enum
{

	STATIC = 0x00,						// top of the queue (first in, aka oldest sample) will always be at queue[0], never changing its index
	DYNAMIC = 0x01						// top of the queue (first in, aka oldest sample) will always be at queue[oldestSampleIndex] which changes index

} t_QueueType;

// generic queue structure
typedef struct
{

	void *queue;					// buffer to hold the queue's samples, type-agnostic and size-agnostic
	size_t size;					// size of the queue's buffer
	t_QueueType type;				// denotes the type of the queue

	size_t dataTypeSize;			// holds the size of the data type the queue stores

	uint8_t oldestDataIndex;		// holds the index of the oldest sample in the queue
	uint8_t empty;					// flag denoting whether or not the queue is empty
	uint8_t initialized;			// flag denoting whether or not the queue has been initialized

} t_Queue;

// public queue functions
void queue_init(t_Queue *Q, uint8_t queueSize, t_QueueType queueType, size_t dataTypeSize);
void queue_push(t_Queue *Q, const void *data);
void queue_pop(t_Queue *);

#endif
