/*
 * CircularROBQueue.h
 *
 *  Created on: Sep 29, 2015
 *      Author: DebashisGanguly
 */

#ifndef GLOBAL_ADT_CIRCULARQUEUE_H_ROB
#define GLOBAL_ADT_CIRCULARQUEUE_H_ROB

#include <stdio.h>
#include <stdlib.h>

typedef struct _ROBRow{
        int* Key;
        int Busy;
        Instruction* InsROB;
        int State;//assue 0 - Not start anything, 1-issue, 2-execute, 3-write result, 4-commit
        int Destination;
        int RenamingRegister;
 }robRow;

typedef struct _circularROBQueue {
	int head;
	int tail;
	int count;
	int size;
	robRow **items;
} CircularROBQueue;

//below is JFHe's code
	
CircularROBQueue *ROB;
int UpperSizeOfROB;
//Upper is JFHe's code

static inline CircularROBQueue *createCircularROBQueue (int size) {
	CircularROBQueue *circularROBQueue = malloc (sizeof(CircularROBQueue));

	circularROBQueue -> head = 0;
	circularROBQueue -> tail = 0;
	circularROBQueue -> count = 0;
	circularROBQueue -> size = size;
	circularROBQueue -> items = (robRow **) malloc (size * sizeof(robRow *));

	return circularROBQueue;
}

static inline int getCountCircularROBQueue (CircularROBQueue *circularROBQueue) {
	if (circularROBQueue == NULL)
		return 0;
	else
		return circularROBQueue -> count;
}

static inline int isFullCircularROBQueue (CircularROBQueue *circularROBQueue) {
	if (circularROBQueue == NULL)
		return -1;
	else
		return circularROBQueue -> size == circularROBQueue -> count;
}

static inline void enqueueCircularROB (CircularROBQueue *circularROBQueue, robRow* value) {
	if (!isFullCircularROBQueue (circularROBQueue)) {
		circularROBQueue -> items [circularROBQueue -> tail] = value;
		circularROBQueue -> tail = (circularROBQueue -> tail + 1) % circularROBQueue -> size;
		circularROBQueue -> count++;
	}
}

static inline robRow *dequeueCircularROB (CircularROBQueue *circularROBQueue) {
	robRow* value = NULL;

	if (getCountCircularROBQueue (circularROBQueue) != 0) {
		value = circularROBQueue -> items [circularROBQueue -> head];
		circularROBQueue -> head = (circularROBQueue -> head + 1) % circularROBQueue -> size;
		circularROBQueue -> count--;
	}

	return value;
}

static inline robRow *getHeadCircularROBQueue (CircularROBQueue *circularROBQueue) {
	robRow* value = NULL;

		if (getCountCircularROBQueue (circularROBQueue) != 0) {
			value = circularROBQueue -> items [circularROBQueue -> head];
		}

		return value;
}


// Below is added by JianfengHe
static inline robRow *getNumthCircularROBQueue (CircularROBQueue *circularROBQueue, int entryNum) {
// return the pointer of the ROBRow having same enryNum (start counting from 0 ranther than 1)
        robRow* value = NULL;

                if (getCountCircularROBQueue (circularROBQueue) != 0) {
                        value = circularROBQueue -> items [entryNum];
                }

                return value;
}
// Upper is added by JianfengHe
#endif /* GLOBAL_ADT_CIRCULARQUEUE_H_ROB */
