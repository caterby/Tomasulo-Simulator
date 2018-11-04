#include "./Global/TomasuloSimulator.h"


//=========================================tructionsInFQueuebegin fQueue ===================================
//int NF = 4;
//int NI = 8;
//CircularQueue *fQueue = createCircularQueue (NF);
//CircularQueue *dQueue = createCircularQueue (NI);



//========================================== begin decode ============================

Instruction *DecodedInstruction(char* charInstructionToBeDecoded){

	printf ("Instruction To Be Decoded:%s\n", charInstructionToBeDecoded);

	Instruction *instruction;

    char *token = (char *) malloc (sizeof(char) * MAX_LINE);

    OpCode op; 

    int rd; 
    int rs; 
    int rt; 

    int rsValue;
    int rtValue;

    int fd; 
    int fs; 
    int ft; 

    double fsValue;
    double ftValue;

    int immediate;

    int target;
        

	op = NOOP, rd = -1, rs = -1, rt = -1, rsValue = -1, rtValue = -1, fd = -1, fs = -1, ft = -1, fsValue = -1, ftValue = -1, immediate = 0, target = 0;

	token = (char *) malloc (sizeof(char) * MAX_LINE);

	strcpy (token, charInstructionToBeDecoded);

	token = strtok(token, " ,()\t\n");

	if(strcmp(token, "AND") == 0) {
		op = AND;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "ANDI") == 0) {
		op = ANDI;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);
	} else if(strcmp(token, "OR") == 0) {
		op = OR;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "ORI") == 0) {
		op = ORI;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);
	} else if(strcmp(token, "SLT") == 0) {
		op = SLT;
		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "SLTI") == 0) {
		op = SLTI;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);
	} else if(strcmp(token, "DADD") == 0) {
		op = DADD;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "DADDI") == 0) {
		op = DADDI;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");

		immediate = atoi(token);
	} else if(strcmp(token, "DSUB") == 0) {
		op = DSUB;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "DMUL") == 0) {
		op = DMUL;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "LD") == 0) {
		op = LD;

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);
	} else if(strcmp(token, "SD") == 0) {
		op = SD;

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);
	} else if(strcmp(token, "L.D") == 0) {
		op = L_D;

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);
	} else if(strcmp(token, "S.D") == 0) {
		op = S_D;

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);
	} else if(strcmp(token, "ADD.D") == 0) {
		op = ADD_D;

		token = strtok(NULL, " ,()RF\t\n");
		fd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		fs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);
	} else if(strcmp(token, "SUB.D") == 0) {
		op = SUB_D;

		token = strtok(NULL, " ,()RF\t\n");
		fd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		fs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);
	} else if(strcmp(token, "MUL.D") == 0) {
		op = MUL_D;

		token = strtok(NULL, " ,()RF\t\n");
		fd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		fs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);
	} else if(strcmp(token, "DIV.D") == 0) {
		op = DIV_D;

		token = strtok(NULL, " ,()RF\t\n");
		fd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		fs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);
	} else if(strcmp(token, "BEQZ") == 0) {
		op = BEQZ;

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()\t\n");
	} else if(strcmp(token, "BNEZ") == 0) {
		op = BNEZ;

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()\t\n");
	} else if(strcmp(token, "BEQ") == 0) {
		op = BEQ;

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);

		token = strtok(NULL, " ,()\t\n");
	} else if(strcmp(token, "BNE") == 0) {
		op = BNE;

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);

		token = strtok(NULL, " ,()\t\n");
	} else {
		printf("Invalid instruction %s...\n", charInstructionToBeDecoded);
		exit (EXIT_FAILURE);
	}

	if (op == BEQZ || op == BNEZ || op == BEQ || op == BNE) {
		DictionaryEntry *codeLabel = getValueChainByDictionaryKey (codeLabels, (void *) token);

		if (codeLabel == NULL) {
			printf("Invalid code label cannot be resolved...\n");
			exit (EXIT_FAILURE);
		} else {
			target = *((int*)codeLabel -> value -> value);
		}
	}

	instruction = (Instruction *) malloc (sizeof(Instruction));

	instruction -> op = op;

	instruction -> rd = rd;
	instruction -> rs = rs;
	instruction -> rt = rt;

	instruction -> rsValue = rsValue;
	instruction -> rtValue = rtValue;

	instruction -> fd = fd;
	instruction -> fs = fs;
	instruction -> ft = ft;

	instruction -> fsValue = fsValue;
	instruction -> ftValue = ftValue;

	instruction -> immediate = immediate;

	instruction -> target = target;

	printf("Decoded :%s -> %s, rd=%d, rs=%d, rt=%d, fd=%d, fs=%d, ft=%d, immediate=%d, target=%d\n", charInstructionToBeDecoded,
		 getOpcodeString ((int) op), rd, rs, rt, fd, fs, ft, immediate, target);

	return instruction;

}

//========================================== end decode ==============================




void buildFetchQueue(){
    
    int i = 0;
    int numberOfInstructionsInFQueue = 0;
    // first, fetched instruction queue begins
    while(numberOfInstructionsInFQueue < NF){

       void *currentAddress = malloc(sizeof(int));
       *((int*)currentAddress) = cpu -> PC;

	   void *addrPtr = malloc(sizeof(int));
	   //strcpy (*((int*)addrPtr), currentAddress);
	   *((int*)addrPtr) =*((int*) currentAddress);

	   DictionaryEntry *currentInstruction = getValueChainByDictionaryKey (instructionCache, addrPtr);

       char *instruction_str = (char *) malloc (sizeof(char) * MAX_LINE);
       strcpy (instruction_str, ((char*)currentInstruction -> value -> value));
       printf ("Fetched %d:%s\n", cpu -> PC, instruction_str);

	   // judge whether the current address is out of boundary
	   if(*((int*)addrPtr) > (instructionCacheBaseAddress + cacheLineSize * numberOfInstruction)){
	       printf("The currentAddress is out of instructionCache boundary\n");
	       break;
	    }
        
        Instruction *fecthedInstruction = (Instruction *) malloc (sizeof(Instruction));
        fecthedInstruction = (Instruction*)DecodedInstruction(instruction_str);
        fecthedInstruction -> InstructionPC =*((int*) currentAddress);
        //strcpy (fecthedInstruction, ((Instruction*)decodeInstruction(instruction_str)));
        
        // judge the branch, and update the PC
        if (fecthedInstruction -> op == BEQZ || fecthedInstruction -> op == BNEZ || fecthedInstruction -> op == BEQ || fecthedInstruction -> op == BNE){
            for(i = 0; i < 16; i++){
                if(BTB[i] -> InstructionPC == fecthedInstruction -> InstructionPC){
                   cpu -> PC = BTB[i] -> PredictedPC;
                   currentAddress += BTB[i] -> PredictedPC;
                   fecthedInstruction -> predictFlag = 0;
                }else{
                   cpu -> PC += 4;
                   currentAddress += 4;
                   fecthedInstruction -> predictFlag = -1;
                }
            }

        }

        // if the number of fecthedInstruction is less than 4, add currentInstruction into fetchedInstructionQueue 
	    if(isFullCircularQueue(fQueue) != 1){
	       enqueueCircular (fQueue, fecthedInstruction);
	    }
      
        //free(instruction_str);  
        free(currentAddress);   

	}
}

//========================================== end fQueue ==============================


//========================================= begin fQueue =============================

void buildDecodeQueue(){
    // second, decode instrution queue begins
	while(isFullCircularQueue(dQueue) != 1){
        if(fQueue -> count <= 0){
           printf("No instructions can be decoded from the fetched instruction queue");
           break;
        }       
        Instruction *decodeInstruction = (Instruction *) malloc (sizeof(Instruction));
        decodeInstruction = (Instruction*)dequeueCircular(fQueue);
        //strcpy (decodeInstruction, ((Instruction*)dequeueCircular(fQueue)));
        enqueueCircular (dQueue, decodeInstruction);
    }
}

//========================================== end  decode =============================



//======================= begin Issue Int Unit With immediate ==========================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueIntUnitWithImmediate(Instruction *instruction){
	
	int i;
	int indexRR = 99;
	for(i = 0; i < 8; i++){
        if(intRRcount[i] == 1){
           indexRR = i;
        }
	}

    if(indexRR >= 0 && indexRR < 8){
        // DictionaryRSVRowEntry needs to be defined as a global variable 
        RSVRow* rsRowcurrent = createRSRow(UnitName[0]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;

        // researvation station has empty space, then begin issue
       while (rsRowcurrent != NULL){
		if(rsRowcurrent -> Busy == 0){ 
            int h;
			int registerStatusIndex = instruction -> rs - 1;
			
			if(intRegisterStatus[registerStatusIndex] -> Busy == 1){
			    h = intRegisterStatus[registerStatusIndex] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> intVj = robItem -> RenamingRegister;
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{
				rsRowcurrent -> intVj = cpu -> integerRegisters [instruction -> rs] -> data;
			    rsRowcurrent -> Qj = 0;
	        } 

	        // If the rt is an immediate.
			rsRowcurrent -> intVk = instruction -> immediate;
		    rsRowcurrent -> Qk = 0;
		    
		    // update all States, b is the entry number in the ROB, need to be changed after discussing with Jianfeng and YueDai
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op;

            int index = instruction -> rt - 1;
            intRegisterStatus[index] -> reorderNum = b;
            intRegisterStatus[index] -> Busy = 1;
            robRow *newRobItemUpdated = (robRow*) malloc (sizeof(robRow));
			newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Destination = instruction -> rt;
			newRobItemUpdated -> Busy = 1;
			newRobItemUpdated -> RenamingRegister = indexRR;
			enqueueCircularROB (ROB, newRobItemUpdated);

		}

        rsRowcurrent = rsRowcurrent ->next;
	  }
    }

}

//============================== end Issue Int Unit With Immediate ==============================



//============================= begin Issue Int Unit Without immediate ==========================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueIntUnitWithoutImmediate(Instruction *instruction){

	int i;
	int indexRR = 99;
	for(i = 0; i < 8; i++){
        if(intRRcount[i] == 1){
           indexRR = i;
        }
	}
	// Reservation stations from 1 to 4 is for Int Unit
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[0]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;

        // researvation station has empty space, then begin issue
       while (rsRowcurrent != NULL){

		if(rsRowcurrent -> Busy == 0){
            int h;
            int registerStatusIndexRS = instruction -> rs - 1;


			if(intRegisterStatus[registerStatusIndexRS] -> Busy == 1){
			    h = intRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem = (robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> intVj = robItem -> RenamingRegister;
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{
				rsRowcurrent -> intVj = cpu -> integerRegisters [instruction -> rs] -> data;
			    rsRowcurrent -> Qj = 0;
	        } 

            
            int registerStatusIndexRT = instruction -> rt - 1;

			if(intRegisterStatus[registerStatusIndexRT] -> Busy == 1){
			    h = intRegisterStatus[registerStatusIndexRT] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> intVk = robItem -> RenamingRegister;
				    rsRowcurrent -> Qk = 0;
			    }else{
				    rsRowcurrent -> Qk = h;
				}
			}else{
				rsRowcurrent -> intVk = cpu -> integerRegisters[instruction -> rt] -> data;
			    rsRowcurrent -> Qk = 0;
	        } 
		   

		    // update all States, b is the entry number in the ROB
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op;

            int registerStatusIndexRD = instruction -> rd - 1;
            intRegisterStatus[registerStatusIndexRD] -> Busy = 1;
            intRegisterStatus[registerStatusIndexRD] -> reorderNum = b;

           
            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);
			newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Destination = instruction -> rd;
			newRobItemUpdated -> Busy = 1;
			newRobItemUpdated -> RenamingRegister = indexRR;
			enqueueCircularROB (ROB, newRobItemUpdated);

		}

		rsRowcurrent = rsRowcurrent ->next;
	  }
        
    }

}

//=============================== end Issue Int Unit Without Immediate ========================


//==================================== start Issue MULT Unit  =================================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueMultUnit(Instruction *instruction){
	
	int i;
	int indexRR = 99;
	for(i = 0; i < 8; i++){
        if(intRRcount[i] == 1){
           indexRR = i;
        }
	}
       
	// Reservation stations from 1 to 4 is for Int Unit
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[1]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;

        
        // researvation station has empty space, then begin issue
       while (rsRowcurrent != NULL){
		if(rsRowcurrent -> Busy == 0){
            int h;

            int registerStatusIndexRS = instruction -> rs - 1;
            
			
			if(intRegisterStatus[registerStatusIndexRS] -> Busy == 1){
			    h = intRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> intVj = robItem -> RenamingRegister;
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{
				rsRowcurrent -> intVj = cpu -> integerRegisters[instruction -> rs] -> data;
			    rsRowcurrent -> Qj = 0;
	        } 

	        // If the rt is a register entry number
	        int registerStatusIndexRT = instruction -> rt - 1;

		    

			if(intRegisterStatus[registerStatusIndexRT] -> Busy == 1){
			    h = intRegisterStatus[registerStatusIndexRT] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> intVk = robItem -> RenamingRegister;
				    rsRowcurrent -> Qk = 0;
			    }else{
				    rsRowcurrent -> Qk = h;
				}
			}else{
				rsRowcurrent -> intVk = cpu -> integerRegisters[instruction -> rt] -> data;
			    rsRowcurrent -> Qk = 0;
	        } 
		    
		    
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op;

            int registerStatusIndexRD = instruction -> rd - 1;
            intRegisterStatus[registerStatusIndexRD] -> Busy = 1;
            intRegisterStatus[registerStatusIndexRD] -> reorderNum = b;

            
            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);
			newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Destination = instruction -> rd;
			newRobItemUpdated -> Busy = 1;
			newRobItemUpdated -> RenamingRegister = indexRR;
			enqueueCircularROB (ROB, newRobItemUpdated);

		}

		rsRowcurrent = rsRowcurrent ->next;

	  }
        
    }

}

//====================================== end Issue MULT Unit  =================================



//=================================begin Issue Float Point Add Unit  ==============================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueFPAddUnit(Instruction *instruction){
	int i;
    int indexRR = 99;
	for(i = 0; i < 8; i++){
        if(fpRRcount[i] == 1){
           indexRR = i;
        }
	}

	// Reservation stations from 5 to 6 is for MULT Unit
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[3]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;

        
        // researvation station has empty space, then begin issue
       while(rsRowcurrent != NULL){
		if(rsRowcurrent -> Busy == 0){
            int h;           
            int registerStatusIndexRS = instruction -> rs - 1;

			if((fpRegisterStatus[registerStatusIndexRS] -> Busy) == 1){
			    h = fpRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> fpVj = robItem -> RenamingRegister;
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{
				rsRowcurrent -> fpVj = cpu -> floatingPointRegisters[instruction -> rs] -> data;
			    rsRowcurrent -> Qj = 0;
	        } 

	        // the rt is a register entry number
		    int registerStatusIndexRT = instruction -> rt - 1;

			if((fpRegisterStatus[registerStatusIndexRT] -> Busy) == 1){
			    h = fpRegisterStatus[registerStatusIndexRT] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> fpVk = robItem -> RenamingRegister;
				    rsRowcurrent -> Qk = 0;
			    }else{
				    rsRowcurrent -> Qk = h;
				}
			}else{
				rsRowcurrent -> fpVk = cpu -> floatingPointRegisters[instruction -> rt] -> data;
			    rsRowcurrent -> Qk = 0;
	        } 
		    

		    // update all States, b is the entry number in the ROB
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op;

            int registerStatusIndexRD = instruction -> rd - 1;
            fpRegisterStatus[registerStatusIndexRD] -> Busy = 1;
            fpRegisterStatus[registerStatusIndexRD] -> reorderNum = b;

            
            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);
			newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Destination = instruction -> rd;
			newRobItemUpdated -> Busy = 1;
			newRobItemUpdated -> RenamingRegister = indexRR;
			enqueueCircularROB (ROB, newRobItemUpdated);

		}

		rsRowcurrent = rsRowcurrent ->next;

	  }
        
    }

}

//============================== end Issue Float Point Add Unit  ==============================



//=================================begin Issue Float Point Mult Unit  ==============================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueFPMultUnit(Instruction *instruction){
	int i;
    int indexRR = 99;
	for(i = 0; i < 8; i++){
        if(fpRRcount[i] == 1){
           indexRR = i;
        }
	}

	// Reservation stations from 5 to 6 is for MULT Unit
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[4]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;

        
        // researvation station has empty space, then begin issue
       while(rsRowcurrent != NULL){
		if(rsRowcurrent -> Busy == 0){
            int h;           
            int registerStatusIndexRS = instruction -> rs - 1;

			if((fpRegisterStatus[registerStatusIndexRS] -> Busy) == 1){
			    h = fpRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> fpVj = robItem -> RenamingRegister;
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{
				rsRowcurrent -> fpVj = cpu -> floatingPointRegisters[instruction -> rs] -> data;
			    rsRowcurrent -> Qj = 0;
	        } 

	        // the rt is a register entry number
		    int registerStatusIndexRT = instruction -> rt - 1;

			if((fpRegisterStatus[registerStatusIndexRT] -> Busy) == 1){
			    h = fpRegisterStatus[registerStatusIndexRT] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> fpVk = robItem -> RenamingRegister;
				    rsRowcurrent -> Qk = 0;
			    }else{
				    rsRowcurrent -> Qk = h;
				}
			}else{
				rsRowcurrent -> fpVk = cpu -> floatingPointRegisters[instruction -> rt] -> data;
			    rsRowcurrent -> Qk = 0;
	        } 
		    

		    // update all States, b is the entry number in the ROB
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op;

            int registerStatusIndexRD = instruction -> rd - 1;
            fpRegisterStatus[registerStatusIndexRD] -> Busy = 1;
            fpRegisterStatus[registerStatusIndexRD] -> reorderNum = b;

            
            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);
			newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Destination = instruction -> rd;
			newRobItemUpdated -> Busy = 1;
			newRobItemUpdated -> RenamingRegister = indexRR;
			enqueueCircularROB (ROB, newRobItemUpdated);

		}

		rsRowcurrent = rsRowcurrent ->next;

	  }
        
    }

}

//============================== end Issue Float Point Mult Unit  ==============================



//=================================begin Issue Float Point Div Unit  ==============================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueFPDivUnit(Instruction *instruction){
	int i;
    int indexRR = 99;
	for(i = 0; i < 8; i++){
        if(fpRRcount[i] == 1){
           indexRR = i;
        }
	}

	// Reservation stations from 5 to 6 is for MULT Unit
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[5]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;

        
        // researvation station has empty space, then begin issue
       while(rsRowcurrent != NULL){
		if(rsRowcurrent -> Busy == 0){
            int h;           
            int registerStatusIndexRS = instruction -> rs - 1;

			if((fpRegisterStatus[registerStatusIndexRS] -> Busy) == 1){
			    h = fpRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> fpVj = robItem -> RenamingRegister;
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{
				rsRowcurrent -> fpVj = cpu -> floatingPointRegisters[instruction -> rs] -> data;
			    rsRowcurrent -> Qj = 0;
	        } 

	        // the rt is a register entry number
		    int registerStatusIndexRT = instruction -> rt - 1;

			if((fpRegisterStatus[registerStatusIndexRT] -> Busy) == 1){
			    h = fpRegisterStatus[registerStatusIndexRT] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> fpVk = robItem -> RenamingRegister;
				    rsRowcurrent -> Qk = 0;
			    }else{
				    rsRowcurrent -> Qk = h;
				}
			}else{
				rsRowcurrent -> fpVk = cpu -> floatingPointRegisters[instruction -> rt] -> data;
			    rsRowcurrent -> Qk = 0;
	        } 
		    

		    // update all States, b is the entry number in the ROB
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op;

            int registerStatusIndexRD = instruction -> rd - 1;
            fpRegisterStatus[registerStatusIndexRD] -> Busy = 1;
            fpRegisterStatus[registerStatusIndexRD] -> reorderNum = b;

            
            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);
			newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Destination = instruction -> rd;
			newRobItemUpdated -> Busy = 1;
			newRobItemUpdated -> RenamingRegister = indexRR;
			enqueueCircularROB (ROB, newRobItemUpdated);

		}

		rsRowcurrent = rsRowcurrent ->next;

	  }
        
    }

}

//============================== end Issue Float Point Div Unit  ==============================



//================================= begin Issue Int Load Unit  =================================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueIntLoadUnit(Instruction *instruction){
	
	int i;
    int indexRR = 99;
    
	for(i = 0; i < 8; i++){
        if(intRRcount[i] == 1){
            indexRR = i;
        }
	}
	// Reservation stations from 1 to 4 is for Int Unit
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[2]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;

        
        // researvation station is empty, then begin issue
      while (rsRowcurrent != NULL){
		if(rsRowcurrent -> Busy == 0){
            int h;
            int registerStatusIndexRS = instruction -> rs - 1;

			if((intRegisterStatus[registerStatusIndexRS] -> Busy) == 1){
			    h = intRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> intVj = robItem -> RenamingRegister;
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{			    
                rsRowcurrent -> intVj = cpu -> integerRegisters [instruction -> rs] -> data;
			    rsRowcurrent -> Qj = 0;
	        } 
             
            rsRowcurrent -> A = instruction -> immediate ;
       

		    // update all States, b is the entry number in the ROB
            
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op;


            int registerStatusIndexRT = instruction -> rt - 1;
            
 
            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);
            newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Destination = instruction -> rt;
			newRobItemUpdated -> Busy = 1;

            
            newRobItemUpdated -> RenamingRegister = indexRR;
            intRegisterStatus[registerStatusIndexRT] -> Busy = 1;
            intRegisterStatus[registerStatusIndexRT] -> reorderNum = b;
            
			enqueueCircularROB (ROB, newRobItemUpdated);

		}

		rsRowcurrent = rsRowcurrent ->next;

	  }
        
    }

}

//================================== end Issue Int Load Unit  =================================




//================================= begin Issue Float Load Unit  =================================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueFloatLoadUnit(Instruction *instruction){
	
	int i;
    int indexRR = 99;

	for(i = 0; i < 8; i++){
        if(fpRRcount[i] == 1){
           indexRR = i;
        }
	}
	// Reservation stations from 1 to 4 is for Int Unit
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[2]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;

        
        // researvation station is empty, then begin issue
      while (rsRowcurrent != NULL){
		if(rsRowcurrent -> Busy == 0){
            int h;
            int registerStatusIndexRS = instruction -> rs - 1;

			if((fpRegisterStatus[registerStatusIndexRS] -> Busy) == 1){
			    h = fpRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
                    rsRowcurrent -> fpVj = robItem -> RenamingRegister;				    
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{
			    
                rsRowcurrent -> fpVj = cpu -> floatingPointRegisters [instruction -> rs] -> data;			    
			    rsRowcurrent -> Qj = 0;
	        } 
             
            rsRowcurrent -> A = instruction -> immediate ;
       

		    // update all States, b is the entry number in the ROB
            
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op;

            int registerStatusIndexRT = instruction -> rt - 1;
            
 
            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);
            newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Destination = instruction -> rt;
			newRobItemUpdated -> Busy = 1;

            
            newRobItemUpdated -> RenamingRegister = indexRR;
            fpRegisterStatus[registerStatusIndexRT] -> Busy = 1;
            fpRegisterStatus[registerStatusIndexRT] -> reorderNum = b;
            
			enqueueCircularROB (ROB, newRobItemUpdated);

		}

		rsRowcurrent = rsRowcurrent ->next;

	  }
        
    }

}

//================================== end Issue Float Load Unit  =================================




//================================ begin Issue Int Store Unit  ================================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueIntStoreUnit(Instruction *instruction){
	
	int i;
    int indexRR = 99;
    
    for(i = 0; i < 8; i++){
        if(intRRcount[i] == 1){
            indexRR = i;
        }
	}
	// Reservation stations from 1 to 4 is for Int Unit
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[2]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;


        // researvation station has empty space, then begin issue
        while(rsRowcurrent != NULL){
		if(rsRowcurrent -> Busy == 0){
            int h;
            int registerStatusIndexRS = instruction -> rs - 1;

            
			if((intRegisterStatus[registerStatusIndexRS] -> Busy) == 1){
			    h = intRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    if(instruction -> op == SD){
				        rsRowcurrent -> intVj = robItem -> RenamingRegister;
				    }
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{
			    if(instruction -> op == SD){
                    rsRowcurrent -> intVj = cpu -> integerRegisters[instruction -> rs] -> data;
			    }
			    rsRowcurrent -> Qj = 0;
	        } 

	       
            rsRowcurrent -> A = instruction -> immediate;
       
		    // update all States, b is the entry number in the ROB
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op; 

            int registerStatusIndexRT = instruction -> rt - 1;
            

            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);
			newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Busy = 1;

            
            newRobItemUpdated -> RenamingRegister = indexRR;
            intRegisterStatus[registerStatusIndexRT] -> Busy = 1;
            intRegisterStatus[registerStatusIndexRT] -> reorderNum = b;
            
			enqueueCircularROB (ROB, newRobItemUpdated);
			
		}

		rsRowcurrent = rsRowcurrent ->next;

		}
        
    }

}

//================================== end Issue Int Store Unit  =================================



//================================ begin Issue Float Store Unit  ================================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueFloatStoreUnit(Instruction *instruction){
	
	int i;
    int indexRR = 99;
    
    for(i = 0; i < 8; i++){
        if(fpRRcount[i] == 1){
           indexRR = i;
        }
	}
	// Reservation stations from 1 to 4 is for Int Unit
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[2]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;


        // researvation station has empty space, then begin issue
        while(rsRowcurrent != NULL){
		if(rsRowcurrent -> Busy == 0){
            int h;
            int registerStatusIndexRS = instruction -> rs - 1;

            
			if((fpRegisterStatus[registerStatusIndexRS] -> Busy) == 1){
			    h = fpRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????				    
                    rsRowcurrent -> fpVj = robItem -> RenamingRegister;
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{

                rsRowcurrent -> fpVj = cpu -> floatingPointRegisters[instruction -> rs] -> data;
			    rsRowcurrent -> Qj = 0;
	        } 

	       
            rsRowcurrent -> A = instruction -> immediate;
       
		    // update all States, b is the entry number in the ROB
            int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op; 

            int registerStatusIndexRT = instruction -> rt - 1;
            

            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);
			newRobItemUpdated -> InsROB = instruction;
			//strcpy ((Instruction*)newRobItemUpdated -> instruction, instruction);
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Busy = 1;

        
            newRobItemUpdated -> RenamingRegister = indexRR;
            fpRegisterStatus[registerStatusIndexRT] -> Busy = 1;
            fpRegisterStatus[registerStatusIndexRT] -> reorderNum = b;
            
			enqueueCircularROB (ROB, newRobItemUpdated);
			
		}

		rsRowcurrent = rsRowcurrent ->next;

		}
        
    }

}

//================================== end Issue Float Store Unit  =================================




//================================== begin Issue BU Unit  =================================

// if the dqueue is not empty and the corresponding reservation station has empty space, then issue 
void issueBUUnit(Instruction *instruction){
	
	int i;
    int indexRR = 99;
    for(i = 0; i < 8; i++){
        if(intRRcount[i] == 1){
           indexRR = i;
        }
	}
	
    if(indexRR >= 0 && indexRR < 8){

        RSVRow* rsRowcurrent = createRSRow(UnitName[6]);
        DictionaryRSVRowEntry* rsRowcurrentEntry = getValueChainByDictionaryRSRowKey(RSV, (rsRowcurrent->Key));
        rsRowcurrent = rsRowcurrentEntry -> value;

        
        // researvation station is empty, then begin issue
      while(rsRowcurrent != NULL){
		if((rsRowcurrent -> Busy) == 0){
            int h;
            
			int registerStatusIndexRS = instruction -> rs - 1;

			if((intRegisterStatus[registerStatusIndexRS] -> Busy) == 1){
			    h = intRegisterStatus[registerStatusIndexRS] -> reorderNum;
			    robRow *robItem =(robRow*) malloc (sizeof(robRow));
			    robItem = getNumthCircularROBQueue(ROB, h);
				if(robItem -> Busy == 0){
				    // find the value in the coresponding RR??????
				    rsRowcurrent -> intVj = robItem -> RenamingRegister;
				    rsRowcurrent -> Qj = 0;
			    }else{
				    rsRowcurrent -> Qj = h;
				}
			}else{
				rsRowcurrent -> intVj = cpu -> integerRegisters [instruction -> rs] -> data;
			    rsRowcurrent -> Qj = 0;
	        } 

	                    
            if(instruction -> op == BEQZ || instruction -> op == BNEZ){
				rsRowcurrent -> A = instruction -> rt;
			}else{
                rsRowcurrent -> A = instruction -> rt ;
                int registerStatusIndexRT = instruction -> rt - 1;

			    if((intRegisterStatus[registerStatusIndexRT] -> Busy) == 1){
			       h = intRegisterStatus[registerStatusIndexRT] -> reorderNum;
			       robRow *robItem =(robRow*) malloc (sizeof(robRow));
			       robItem = getNumthCircularROBQueue(ROB, h);
				   if(robItem -> Busy == 0){
				        // find the value in the coresponding RR??????
				        rsRowcurrent -> intVk = robItem -> RenamingRegister;
				        rsRowcurrent -> Qk = 0;
			        }else{
				        rsRowcurrent -> Qk = h;
				    }
			    }else{
				    rsRowcurrent -> intVk = cpu -> integerRegisters[instruction -> rt] -> data;
			        rsRowcurrent -> Qk = 0;
	            } 

			}

		    // update all States, b is the entry number in the ROB
		    int b;
		    b = ROB -> tail + 1 % ROB -> size;
            rsRowcurrent -> Busy = 1;
            rsRowcurrent -> Dest = b;
            rsRowcurrent -> op = instruction -> op;

            //registerStatusRow -> reorderNum = instruction -> rd;
            //registerStatusRow -> Busy = 1;
            robRow *newRobItemUpdated =(robRow*) malloc (sizeof(robRow));
			//newRobItemUpdated = getNumthCircularROBQueue(ROB, b);

			newRobItemUpdated -> InsROB = instruction;
			newRobItemUpdated -> State = 1;
			newRobItemUpdated -> Busy = 1;
			newRobItemUpdated -> RenamingRegister = indexRR;
			enqueueCircularROB (ROB, newRobItemUpdated);

		}

        rsRowcurrent = rsRowcurrent ->next;
	  }
        
    }

}

//================================== end Issue BU Unit  ===============================




//=================== begin Issue instructions in the dQueue ==========================

void ISSUE(){
	
	int halt = 0;
	int numberOfStallsByROB = 0;
	// no more than NW = 4 instructions can be issued in one clock cycle
	int issueCount = 0;
	while((issueCount < NW) && (!halt)){
	   // if the ROB is full, can not issue any instructions
	   if((ROB -> count) >= NR){
			numberOfStallsByROB++;
			halt = 1;
			break;
		}
        
        // the dQueue is empty
        if((dQueue-> count) <= 0){
			printf("The dQueue is empty, break from the loop");
			break;
		}else{
		    Instruction *instruction = (Instruction *) malloc (sizeof(Instruction));
		    instruction = (Instruction*)dequeueCircular(dQueue);
		    //strcpy (instruction, ((Instruction*)dequeueCircular (dQueue)));
		

		switch (instruction -> op){
		   case ANDI:
                  issueIntUnitWithImmediate(instruction);
		          break;
		   case AND:
                  issueIntUnitWithoutImmediate(instruction); 
		          break;
		   case ORI:
                  issueIntUnitWithImmediate(instruction);
		          break;
		   case OR:
                  issueIntUnitWithoutImmediate(instruction);
		          break;
		   case SLTI:
                  issueIntUnitWithImmediate(instruction);
		          break;
		   case SLT:
                  issueIntUnitWithoutImmediate(instruction);
		          break;
		   case DADDI:
                  issueIntUnitWithImmediate(instruction);
		          break;
		   case DADD:
                  issueIntUnitWithoutImmediate(instruction);
		          break;
		   case DSUB:
                  issueIntUnitWithoutImmediate(instruction);
		          break;
           case DMUL:
                  issueMultUnit(instruction);
		          break;
           case ADD_D:
                  issueFPAddUnit(instruction);
		          break;
           case SUB_D:
                  issueFPAddUnit(instruction); 
		          break;
           case MUL_D:
                  issueFPMultUnit(instruction);
		          break;
           case DIV_D:
                  issueFPDivUnit(instruction);
		          break;
           case L_D:
                  issueFloatLoadUnit(instruction);
                  break;
           case LD:
                  issueIntLoadUnit(instruction);
                  break;
           case SD:
                  issueIntStoreUnit(instruction);
                  break;
           case S_D:
                  issueFloatStoreUnit(instruction);
                  break;
           case BNE:
                  issueBUUnit(instruction);
                  break;
           case BNEZ:
                  issueBUUnit(instruction);
                  break;
           case BEQ:
                  issueBUUnit(instruction);
                  break;
           case BEQZ:
                  issueBUUnit(instruction);
                  break;
           default:
                  break;
		}//JLiu add end symbol at here
		}
           issueCount++;
	}
    
}

//================================== end Issue Process  ===============================



//====================================== clear Queue ==================================
void clearQueue(CircularQueue *inputQueue){
    if(inputQueue -> count <= 0){
       printf("The fetched queue is already clear");
    }else{
       while(inputQueue -> count > 0){
           dequeueCircular(inputQueue);
       }
    }  
}
























