#ifndef Global_Others_Related_H_
#define Global_Others_Related_H_

#include "./DictionaryRSRow.h"
#include "./CircularQueue.h"

typedef struct Buffer {
        int intFlag;             
        int intResult;
        RSVRow *intRSV;

        int multFlag;
        int multResult;
        RSVRow *multRSV;

        int lsFlag;             
        int lsIntResult;
        double lsFpResult;
        int lsAddr;
        RSVRow *lsRSV;

        int fpaddFlag;
        double fpaddResult;
        RSVRow *fpaddRSV;

        int fpmultFlag;
        double fpmultResult;
        RSVRow *fpmultRSV;

        int fpdivFlag;
        double fpdivResult;
        RSVRow *fpdivRSV;

        int buFlag;
        int buResult;
        RSVRow *buRSV;
}Buffer;

typedef struct unit{
        int count;
        RSVRow *rsv;
}Unit;

CircularQueue *INT;
CircularQueue *MULT;
CircularQueue *LS;
CircularQueue *FPADD;
CircularQueue *FPMULT;
CircularQueue *FPDIV;
CircularQueue *BU;

Buffer *wbBuffer;

//int CDB;

//below from Jie
int NF;
int NI;
int NW;
int NR;
int NB;
//int fpRRcount[8];
//int intRRcount[8];

CircularQueue *fQueue;
CircularQueue *dQueue;

//int LenFuncUnit[7] = {4, 2, 4, 3, 4, 2, 2};
//char* UnitName[7] = {"INT", "MULT", "LS", "FPadd", "FPmult", "FPdiv", "BU"};


//void issue();
//void buildDecodeQueue();
//void buildFetchQueue();
Instruction *DecodedInstruction(char* charInstructionToBeDecoded);

#endif /* Global_Others_Related_H_ */
