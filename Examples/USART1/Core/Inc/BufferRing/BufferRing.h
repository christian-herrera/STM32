/*
 * BufferRing.h
 *
 *  Created on: Apr 15, 2023
 *      Author: christian
 */

#ifndef BUFFER_RING_H
#define BUFFER_RING_H

#define MAX_LENGTH 30

#include "inttypes.h"


struct VarBuffRing {
	uint8_t buffer[MAX_LENGTH+1];
	uint8_t index, tail, num, val;
};


void BufferRing_init(struct VarBuffRing *p);

void BufferRing_add(struct VarBuffRing *p, uint8_t k);
uint8_t BufferRing_read(struct VarBuffRing *p);

uint8_t BufferRing_available(struct VarBuffRing *p);

void BufferRing_incrementTail(struct VarBuffRing *p);
void BufferRing_incrementIndex(struct VarBuffRing *p);


#endif /* BUFFER_RING_H */
