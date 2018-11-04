/*
 * TomasuloSimulator.h
 *
 *  Created on: Oct 1, 2015
 *      Author: DebashisGanguly
 */

#ifndef GLOBAL_TOMASULOSIMULATOR_H_
#define GLOBAL_TOMASULOSIMULATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./DataTypes.h"
#include "./ADT/CircularQueue.h"
#include "./ADT/Dictionary.h"

//below is our head files
#include "./ADT/CircularQueueROB.h"
#include "./ADT/DictionaryRSRow.h"
#include "./ADT/DictionaryRegsRow.h"
#include "./ADT/DictionaryBTB.h"

#include "./ADT/OtherRelated.h"

//upper is our head files


//macros for parsing and tokenizing
#define DATA_LABEL "DATA"
#define WHITE_SPACE " \t\n"
#define LINE_TERMINATOR "\n"
#define LABEL_TERMINATOR ":"
#define LABEL_TERMINATOR_CHAR ':'
#define MEMORY_LABEL "Mem"
#define MEMORY_SEPARATOR " )(=\n"

#define MAX_LINE  4096

void commit();
void writeBack();
void executeStage();
void ISSUE();
void buildDecodeQueue();
void buildFetchQueue();



//global variables populated from configuration 
int numberOfIntRegisters; //NIR
int numberOfFPRegisters; //NFPR

int instructionCacheBaseAddress; //ICBA

int cacheLineSize; //CLS

int numberOfInstruction;

Dictionary *instructionCache;
Dictionary *dataCache;
Dictionary *codeLabels;


CPU *cpu;
//below is our variable shengming
int fpRRcount[8];
int intRRcount[8];
DictionaryRSRow* RSV;
//upper is our variable shengming
void fillInstructionAndDataCache (char *fileName);

void initializeCPU ();

int runClockCycle ();

void printInstructionCache ();
void printCodeLabels ();
void printDataCache ();
void printIntegerRegisters ();
void printFPRegisters ();

//below is our function shengming
//upper is our function shengming

//below is our function define
//upper is our function define

#endif /* GLOBAL_TOMASULOSIMULATOR_H_ */
