/*
 * RingBuffer.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Dylan
 */

#ifndef _RINGBUFFER_RINGBUFFER_H
#define _RINGBUFFER_RINGBUFFER_H

#include "GeneralPurposeBuffer.h"
#include "../queue/queue.h"

#define COAPT_MAX_EMG_CHANNELS    (8)

// structure that holds COAPT_MAX_EMG_CHANNELS # of queues
typedef struct
{

	t_Queue RingBuffer[COAPT_MAX_EMG_CHANNELS];
	uint8_t size;

} t_RingBuffer;

// public ring buffer functions
void GenericRingBufferInit(t_RingBuffer *rings, uint8_t numRings, uint8_t queueSize, t_QueueType queueType, size_t dataTypeSize);

#endif
