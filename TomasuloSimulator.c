/*
 * TomasuloSimulator.c
 *
 *  Created on: Oct 1, 2015
 *      Author: DebashisGanguly
 */

#include "./Global/TomasuloSimulator.h"
int numberOfIntRegisters = 32; //NIR
int numberOfFPRegisters = 32; //NFPR


int instructionCacheBaseAddress = 1000; //ICBA

//below is our parameters define
int parameters[5];
//above is our parameters define

int cacheLineSize = 4; //CLS


//below is our function define
int NF = 4;
int NI = 8;
int NW = 4;
int NR = 4;
int NB = 4;
//upper is our function define

int main(int argc, char** argv) {
	//Validate command line argument
	if (argc != 2) {
		printf ("USAGE: TomasuloSimulator <benchmark_file>\n");
		exit (EXIT_FAILURE);
	}
//below is our function usage

//below get parameters from configs
//	GetParameters(argv[1], parameters);
//above get parameters from configs


//initialize from Jay
int fucI;
for(fucI = 0; fucI < 8; fucI++){
	fpRRcount[fucI] = 0;
	intRRcount[fucI] = 0;
}
//initialize ROB
UpperSizeOfROB = 4;
ROB = createCircularROBQueue(UpperSizeOfROB);

//initialize FunctionUnits
INT = createCircularQueue(1);
MULT = createCircularQueue(4);
LS = createCircularQueue(1);
FPADD = createCircularQueue(3);
FPMULT = createCircularQueue(4);
FPDIV = createCircularQueue(1);
BU = createCircularQueue(1);

//initialize buffer
wbBuffer = (Buffer *)malloc(sizeof(wbBuffer));

//initialze CDB
//CDB = 4;

/*

char* UnitName[7] = {"INT", "MULT", "LS", "FPadd", "FPmult", "FPdiv", "BU"};
int LenFuncUnit[7] = {4, 2, 4, 3, 4, 2, 2};

void createRSV(){
        int jsqUnitKindNum;
        int jsqUnitColNum;
        RSV = createDictionaryRSRow(RS_getHashCode, compareValues);
        jsqUnitKindNum = 0;
        jsqUnitColNum = 0;
	for (jsqUnitKindNum = 0; jsqUnitKindNum < 7; jsqUnitKindNum++){
        RSVRow* rsRowFull;
        rsRowFull = createRSRow(UnitName[jsqUnitKindNum]);
        addDictionaryRSVRowEntry(RSV, UnitName[jsqUnitKindNum], rsRowFull);
        RSVRow* rsRowMid;
        rsRowMid = rsRowFull;
        for (jsqUnitColNum = 0; jsqUnitColNum < LenFuncUnit[jsqUnitKindNum] - 1; jsqUnitColNum++){
        RSVRow* rsRowMidAfter;
        rsRowMidAfter = createRSRow(UnitName[jsqUnitKindNum]);
        rsRowMid -> next = rsRowMidAfter;
        rsRowMid = rsRowMidAfter;
	}
}
}

*/
//initialize RSV
//UnitName[7] = {"INT", "MULT", "LS", "FPadd", "FPmult", "FPdiv", "BU"};
//LenFuncUnit[7] = {4, 2, 4, 3, 4, 2, 2};
UnitName[0] = "INT";
UnitName[1] = "MULT";
UnitName[2] = "LS";
UnitName[3] = "FPadd";
UnitName[4] = "FPmult";
UnitName[5] = "FPdiv";
UnitName[6] = "BU";
LenFuncUnit[0] = 4;
LenFuncUnit[1] = 2;
LenFuncUnit[2] = 4;
LenFuncUnit[3] = 3;
LenFuncUnit[4] = 4;
LenFuncUnit[5] = 2;
LenFuncUnit[6] = 2;
createRSV();

//initialize RegsTable
createRegsTable();

//initialize BTBTable
CreateDictionaryBTB(BTB, 16);	

//upper is our function usage


	fillInstructionAndDataCache (argv[1]); //call loader to fill caches

	printInstructionCache (); //print instruction cache

	printDataCache ();

	printCodeLabels (); //print data cache

	initializeCPU (); //initialize CPU data structure

	while (runClockCycle()); //loop emulating simulator clock cycles

	printDataCache (); //print data cache


	printIntegerRegisters (); //print integer registers
	printFPRegisters (); //print floating point registers
	free(wbBuffer);
	return 0;
}
