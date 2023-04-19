/*
 * BufferRing.c
 *
 *  Created on: Apr 15, 2023
 *      Author: christian
 */


#include "BufferRing.h"

extern void BufferRing_incrementTail(struct VarBuffRing *p);
extern void BufferRing_incrementIndex(struct VarBuffRing *p);



void BufferRing_init(struct VarBuffRing *p){
	BufferRing_clear(p, 1);
}


void BufferRing_add(struct VarBuffRing *p, uint8_t k){
	p->buffer[p->index] = k;
	(p->num)++;

	BufferRing_incrementIndex(p);

	if(p->index == p->tail){
		BufferRing_incrementTail(p);
		(p->num)--;
	}
}


uint8_t BufferRing_read(struct VarBuffRing *p){
	if(p->num > 0){
		p->val = p->buffer[p->tail];
		BufferRing_incrementTail(p);
		(p->num)--;
		return(p->val);
	}
	return(0);
}

uint8_t BufferRing_available(struct VarBuffRing *p){
	return(p->num);
}

void BufferRing_clear(struct VarBuffRing *p, uint8_t clear_vector){
	p->index = 0;
	p->tail = 0;
	p->num = 0;

	if(clear_vector){
		for(uint8_t i = 0; i < MAX_LENGTH; i++){
			p->buffer[i] = '\0';
		}
	}
}



extern void BufferRing_incrementTail(struct VarBuffRing *p){
	if(p->tail == MAX_LENGTH){
		p->tail = 0;
	} else {
		(p->tail)++;
	}
}



extern void BufferRing_incrementIndex(struct VarBuffRing *p){
	if(p->index == MAX_LENGTH){
		p->index = 0;
	} else {
		(p->index)++;
	}
}
