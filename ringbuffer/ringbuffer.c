/*
 * RingBuffer.c
 *
 *  Created on: Jun 2, 2022
 *      Author: Dylan
 */

#include "RingBuffer.h"
#include <stdio.h>

/*
 * \brief	Wrapper to initialize a ring buffer object for general purposes using the queue_init() function in queue.c, caller must provide their own object
 * \param	t_RingBuffer *rings:	pointer to the ring buffer object to be initialized
 * 			uint8_t queueSize:			desired size of the ring buffer's queue
 * 			t_QueueType queueType:	desired queue type (static or dynamic)
 * \return	N/A
 */
void GenericRingBufferInit(t_RingBuffer *rings, uint8_t numRings, uint8_t queueSize, t_QueueType queueType, size_t dataTypeSize)
{

	// set the ring buffer's size
	rings->size = numRings;

	// initialize each ring buffer one-by-one
	for (uint8_t i = 0; i < rings->size; i++)
		queue_init(&rings->RingBuffer[i], queueSize, queueType, dataTypeSize);

}