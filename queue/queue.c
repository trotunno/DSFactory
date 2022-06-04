/*
 * queue.c
 *
 *  Created on: Jun 2, 2022
 *      Author: Dylan Rotunno
 */

#include <stdint.h>
#include <string.h>												// for memcpy() function access
#include <stdlib.h>												// for malloc() function access

#include "queue.h"

#define QUEUE_OFFSET			   			  (1)				// how many NEW elements the queue must account for with each push/pop cycle

// Initializes all data entries of a queue as well as its configuration parameters
void queue_init(t_Queue *Q, uint8_t queueSize, t_QueueType queueType, size_t dataTypeSize)
{

	// if this queue was already initialized before, free the memory from the old queue
	if (Q->initialized == 1)
	{
		free(Q->queue);
		Q->queue = NULL;
	}

	Q->dataTypeSize = dataTypeSize;									// set the queue's data type size
	Q->size = queueSize;											// set how many samples the queue holds
	Q->oldestDataIndex = Q->size;									// set initial index of oldest data in the queue (static queues will not use this)
	Q->type = queueType;											// set type of queue (static or dynamic, specifies where the top of the queue is guaranteed to be)
	Q->empty = 1;													// mark queue as empty
	Q->queue = malloc(Q->size * dataTypeSize);				// allocate memory for the queue
	memset(Q->queue, 0, Q->size*dataTypeSize);						// zero out all queue entries
	Q->initialized = 1;												// mark queue as initialized

}

// pushes data into the queue, how it is pushed depends on the queue's type
void queue_push(t_Queue *Q, const void *data)
{
	// if the queue or data are NULL, don't bother. We don't want a seg fault.		TODO: report an error
	if (Q == NULL || data == NULL)
		return;

	void *src;				// pointer to source memory location
	void *dest;				// pointer to destination memory location
	size_t size;			// size of the memory being operated on

	if (Q->type == DYNAMIC)
	{

		// shift all data that needs to be shifted over by QUEUE_OFFSET to make room for the new data
		src  = Q->queue + ( Q->oldestDataIndex * Q->dataTypeSize);
		dest = Q->queue + ( (Q->oldestDataIndex - QUEUE_OFFSET) * Q->dataTypeSize );
		size = (Q->size - Q->oldestDataIndex) * Q->dataTypeSize;
		memmove(dest, src, size);

		// place new data at the back of the queue
		dest = Q->queue + ((Q->size - QUEUE_OFFSET) * Q->dataTypeSize);
		size = Q->dataTypeSize * QUEUE_OFFSET;
		memcpy(dest, data, size);

		Q->oldestDataIndex -= QUEUE_OFFSET;					    // update oldest data index
		Q->empty = 0;											// queue is no longer empty

	}
	else if (Q->type == STATIC)
	{

		// set data at back of queue
		dest = Q->queue + ((Q->size - QUEUE_OFFSET) * Q->dataTypeSize);
		size = Q->dataTypeSize * QUEUE_OFFSET;
		memcpy(dest, data, size);

	}

}

// pops an element from the queue, what element is popped depends on the queue's type.
void queue_pop(t_Queue *Q)
{

	// if the queue is NULL, don't bother. We don't want a seg fault		TODO: report an error
	if (Q == NULL)
		return;

	void *src;						// pointer to source memory location (unused if source data is a literal)
	void *dest;						// pointer to destination memory location
	size_t size;					// size of the memory being operated on

	if (Q->type == DYNAMIC)
	{

		// if there are no elements that can be popped, just return
		if (Q->empty)
			return;

		// remove the oldest data from the queue, update the oldest data index
		dest = Q->queue + (Q->oldestDataIndex * Q->dataTypeSize);
		size = Q->dataTypeSize * QUEUE_OFFSET;
		memset(dest, 0, size);

		Q->oldestDataIndex += QUEUE_OFFSET;				// update oldest data index

		// if the oldest data index in the queue is equal to the queue's size, mark queue as empty
		Q->empty = (Q->oldestDataIndex == Q->size) ? 1 : 0;

	}

	else if (Q->type == STATIC)
	{
		// move the most recent (queue size - queue offset) # of data elements to make room for the next queue_offset # of data points
		src  = Q->queue + (Q->dataTypeSize * QUEUE_OFFSET);
		dest = Q->queue;
		size = Q->dataTypeSize * (Q->size - QUEUE_OFFSET);
		memmove(dest, src, size);

		// zero out QUEUE_OFFSET # of elements at the front of the queue
		dest = Q->queue + ((Q->size - QUEUE_OFFSET) * Q->dataTypeSize);
		size = Q->dataTypeSize * QUEUE_OFFSET;
		memset(dest, 0, size);

	}

}
