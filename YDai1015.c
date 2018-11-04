/*tools for EXE and WB stages with Commit and BTB
 From: Yue Dai
 Date: Oct 15, Mon 8:06PM
 Version: 2.7.4
 Changes:   1. Added a while loop before get into ROB
            2. Rename state as State
            3. Force change void * get by functions in Unit CircularQueues to Unit*
*/

#include "./Global/TomasuloSimulator.h"
//#include "./DataTypes.h"
////Inner stage buffers for EXE/WB
//typedef struct Buffer {
//    int intFlag;         //1 represent it contains a result, 0 represent not, same in the following
//    int intResult;
////    int intDest;
//    RSVRow *intRSV;
//
//    int multFlag;
//    int multResult;
////    int multDest;
//    RSVRow *multRSV
//
//    int lsFlag;        //0---no value; 1---Load Int; 2---Load float; -1---save int; -2---save float
//    int lsIntResult;
//    double lsFpResult;
////    int lsDest;
//    int lsAddr;
//    RSVRow *lsRSV;
//
//    int fpaddFlag;
//    double fpaddResult;
////    int fpaddDest;
//    RSVRow *fpaddRSV;
//
//    int fpmultFlag;
//    double fpmultResult;
////    int fpmultDest;
//    RSVRow *fpmultRSV;
//
//    int fpdivFlag;
//    double fpdivResult;
////    int fpdivDest;
//    RSVRow *fpdivRSV;
//
//    int buFlag;
//    int buResult;
////    int buDest;
//    RSVRow *buRSV
//}Buffer;
//
////Unit count for unit latency;
//typedef struct unit{
//    int count;
//    RSVRow *rsv;
//}Unit;
//CircularQueue *INT = createCircularQueue (1);
//CircularQueue *MULT = createCircularQueue (4);
//CircularQueue *LS = createCircularQueue (1);
//CircularQueue *FPADD = createCircularQueue (3);
//CircularQueue *FPMULT = createCircularQueue (4);
//CircularQueue *FPDIV = createCircularQueue (1);
//CircularQueue *BU = createCircularQueue (1);
//
//Buffer *wbBuffer = (Buffer *)malloc(sizeof(wbBuffer));

//Commit functiontRenamingRegister
void commit(){
	void *addrPtr;
	void *valuePtr;
   	while(getCountCircularROBQueue(ROB) > 0){
        while(NB > 0 && getHeadCircularROBQueue(ROB)->Busy == 1 && getHeadCircularROBQueue(ROB)->State == 3){
            getHeadCircularROBQueue(ROB)->Busy = 0;
            getHeadCircularROBQueue(ROB)->State = 4;
            robRow *h = dequeueCircularROB(ROB);
            OpCode insOp =h -> InsROB -> op;
            int rr = h -> RenamingRegister;
            NB--;
            if(insOp == BEQZ || insOp == BNEZ || insOp == BEQ || insOp == BNE) {
                intRRcount[rr] = 0;
                //clean when branch mis-predicted
                if (cpu -> intRenamingRegister[rr] -> data != h -> InsROB -> predictFlag){
                    //Move cpu -> PC to right position
                    if (cpu -> intRenamingRegister[rr] -> data == 0){
                        cpu -> PC = h -> InsROB -> immediate;
                    }
                    if (cpu -> intRenamingRegister[rr] -> data == -1){
                        cpu -> PC = h -> InsROB -> InstructionPC + 4;
                    }
                    //flush ROB
                    int i = ROB -> head;
                    while(i != ROB -> tail){
                        free(ROB -> items[i]);
                        i = (i + 1) % ROB -> size;
                        ROB -> count--;
                    }
                    free(ROB -> items[ROB -> tail]);
                    ROB -> tail = ROB -> head;
                    //flush Register Status
                    for (i = 0; i < 32; i++){
                        intRegisterStatus[i] -> Busy = 0;
                        fpRegisterStatus[i] -> Busy = 0;
                    }
                    //flush RenamingRegister status
                    for (i = 0; i < 8; i++){
                        cpu -> intRenamingRegister[i] -> data= 0;
                        cpu -> fpRenamingRegister[i] -> data= 0;
                    }
                }
            } else if (insOp == SD){
                int data = cpu -> intRenamingRegister[rr] -> data;
                intRRcount[rr] = 0;
                *((int*)addrPtr) = h -> Destination;
                removeDictionaryEntriesByKey (dataCache, addrPtr);

                *((double*)valuePtr) = data;
                addDictionaryEntry (dataCache, addrPtr, valuePtr);
            } else if (insOp == S_D){
		double data = cpu -> fpRenamingRegister[rr] -> data;
                fpRRcount[rr] = 0;
                *((int*)addrPtr) = h -> Destination;
                removeDictionaryEntriesByKey (dataCache, addrPtr);

                *((double*)valuePtr) = data;
                addDictionaryEntry (dataCache, addrPtr, valuePtr);
            } else if (insOp == ADD_D || insOp == SUB_D|| insOp == MUL_D || insOp == DIV_D || insOp == L_D){
                cpu -> floatingPointRegisters[h -> Destination] -> data = cpu -> fpRenamingRegister[rr] -> data;
                fpRRcount[rr] = 0;
                fpRegisterStatus[h -> Destination] -> Busy = 0;
            } else {
                intRRcount[rr] = 0;
                cpu -> integerRegisters[h -> Destination] -> data = cpu -> intRenamingRegister[rr] -> data;
                intRegisterStatus[h -> Destination] -> Busy = 0;
            }
            free(h);
        }
    }
}

void writeBack(){
	if (NB > 0 && wbBuffer -> intFlag == 1){
		int Res = wbBuffer -> intResult;
		int Dest = wbBuffer -> intRSV -> Dest;
		wbBuffer -> intRSV -> Busy = 0;
		ROB -> items[Dest] -> State = 3;
		cpu -> intRenamingRegister[ROB -> items[Dest] -> RenamingRegister] -> data = Res;
		DictionaryRSVRowEntry *tmpEntry = RSV -> head;
		while(tmpEntry != NULL){
			RSVRow *tmp = tmpEntry -> value;
			while(tmp != NULL){
				if(tmp -> Qj == Dest){
					tmp -> intVj = Res;
					tmp -> Qj = 0;
				}	
				if(tmp -> Qk == Dest){
                    tmp -> intVk = Res;
                    tmp -> Qk = 0;
                        	}
				tmp = tmp -> next;
			}
			tmpEntry = tmpEntry -> next;
		}
		NB--;
		wbBuffer -> intFlag = 0;
		Unit *unit = (Unit *)dequeueCircular(INT);
		free(unit);
	}
	if (NB > 0 && wbBuffer -> multFlag == 1){
		int Res = wbBuffer -> multResult;
        	int Dest = wbBuffer -> multRSV -> Dest;
        	wbBuffer -> multRSV -> Busy = 0;
        	ROB -> items[Dest] -> State = 3;
        	cpu -> intRenamingRegister[ROB -> items[Dest] -> RenamingRegister] -> data = Res;
        	DictionaryRSVRowEntry *tmpEntry = RSV -> head;
        	while(tmpEntry != NULL){
                	RSVRow *tmp = tmpEntry -> value;
               		while(tmp != NULL){
                        	if(tmp -> Qj == Dest){
                                	tmp -> intVj = Res;
                                	tmp -> Qj = 0;
                        	}
                        	if(tmp -> Qk == Dest){
                                	tmp -> intVk = Res;
                                	tmp -> Qk = 0;
                        	}
                        	tmp = tmp -> next;
                	}
                tmpEntry = tmpEntry -> next;
        	}
        	NB--;
		wbBuffer -> multFlag = 0;
		Unit *unit = (Unit *)dequeueCircular(MULT);
		free(unit);
	}
	if (NB > 0 && wbBuffer -> lsFlag != 0){
		if (wbBuffer -> lsFlag == 1){
			int Res = wbBuffer -> lsIntResult;
			int Dest = wbBuffer -> lsRSV -> Dest;
			wbBuffer -> lsRSV -> Busy = 0;
			ROB -> items[Dest] -> State = 3;
            		cpu -> intRenamingRegister[ROB -> items[Dest] -> RenamingRegister] -> data = Res;
            		DictionaryRSVRowEntry *tmpEntry = RSV -> head;
            		while(tmpEntry != NULL){
                    		RSVRow *tmp = tmpEntry -> value;
                    		while(tmp != NULL){
                            	if(tmp -> Qj == Dest){
                                    tmp -> intVj = Res;
                                    tmp -> Qj = 0;
                            	}
                            	if(tmp -> Qk == Dest){
                                    tmp -> intVk = Res;
                                    tmp -> Qk = 0;
                            	}
                            	tmp = tmp -> next;
                    		}
                    		tmpEntry = tmpEntry -> next;
            		}
		}
		if (wbBuffer -> lsFlag == 2){
			double Res = wbBuffer -> lsFpResult;
			int Dest = wbBuffer -> lsRSV -> Dest;
            		wbBuffer -> lsRSV -> Busy = 0;
            		ROB -> items[Dest] -> State = 3;
            		cpu -> fpRenamingRegister[ROB -> items[Dest] -> RenamingRegister] -> data = Res;
            		DictionaryRSVRowEntry *tmpEntry = RSV -> head;
            		while(tmpEntry != NULL){
                    		RSVRow *tmp = tmpEntry -> value;
                    		while(tmp != NULL){
                            	if(tmp -> Qj == Dest){
                                    tmp -> fpVj = Res;
                                    tmp -> Qj = 0;
                            	}
                            	if(tmp -> Qk == Dest){
                                    tmp -> fpVk = Res;
                                    tmp -> Qk = 0;
                            	}
                            	tmp = tmp -> next;
                    		}	
                    		tmpEntry = tmpEntry -> next;
            		}
		}
		if (wbBuffer -> lsFlag == -1){
			int Res = wbBuffer -> lsIntResult;
			int Dest = wbBuffer -> lsRSV -> Dest;
			int Addr = wbBuffer -> lsAddr;
			wbBuffer -> lsRSV -> Busy = 0;
			ROB -> items[Dest] -> State = 3;
			ROB -> items[Dest] -> Destination = wbBuffer -> lsAddr;
                        cpu -> intRenamingRegister[ROB -> items[Dest] -> RenamingRegister] -> data = Res;
		}
		if (wbBuffer -> lsFlag == -2){
            		double Res = wbBuffer -> lsFpResult;
            		int Dest = wbBuffer -> lsRSV -> Dest;
			int Addr = wbBuffer -> lsAddr;
            		wbBuffer -> lsRSV -> Busy = 0;
            		ROB -> items[Dest] -> State = 3;
			ROB -> items[Dest] -> Destination = wbBuffer -> lsAddr;
            		cpu -> fpRenamingRegister[ROB -> items[Dest] -> RenamingRegister] -> data = Res;
        	}
		NB--;
		wbBuffer -> lsFlag = 0;
		Unit *unit = (Unit *)dequeueCircular(LS);
		free(unit);
    }
	
	if(NB > 0 && wbBuffer -> fpaddFlag == 1){
		double Res = wbBuffer -> fpaddResult;
        	int Dest = wbBuffer -> fpaddRSV -> Dest;
        	wbBuffer -> fpaddRSV -> Busy = 0;
        	ROB -> items[Dest] -> State = 3;
        	cpu -> fpRenamingRegister[ROB -> items[Dest] -> RenamingRegister] -> data = Res;
        	DictionaryRSVRowEntry *tmpEntry = RSV -> head;
		while(tmpEntry != NULL){
			RSVRow *tmp = tmpEntry -> value;
			while(tmp != NULL){
				if(tmp -> Qj == Dest){
					tmp -> fpVj = Res;
					tmp -> Qj = 0;
				}
				if(tmp -> Qk == Dest){
					tmp -> fpVk = Res;
					tmp -> Qk = 0;
				}
				tmp = tmp -> next;
			}
			tmpEntry = tmpEntry -> next;
		}
                NB--;
		wbBuffer -> fpaddFlag = 0;
		Unit *unit = (Unit *)dequeueCircular(FPADD);
		free(unit);
	}

	if (NB > 0 && wbBuffer -> fpmultFlag == 1 ){
		double Res = wbBuffer -> fpmultResult;
        	int Dest = wbBuffer -> fpmultRSV -> Dest;
        	wbBuffer -> fpmultRSV -> Busy = 0;
        	ROB -> items[Dest] -> State = 3;
        	cpu -> fpRenamingRegister[ROB -> items[Dest] -> RenamingRegister] -> data = Res;
        	DictionaryRSVRowEntry *tmpEntry = RSV -> head;
		while(tmpEntry != NULL){
			RSVRow *tmp = tmpEntry -> value;
			while(tmp != NULL){
				if(tmp -> Qj == Dest){
					tmp -> fpVj = Res;
					tmp -> Qj = 0;
				}
				if(tmp -> Qk == Dest){
					tmp -> fpVk = Res;
					tmp -> Qk = 0;
				}
				tmp = tmp -> next;
			}
			tmpEntry = tmpEntry -> next;
		}
        	NB--;
		wbBuffer -> fpmultFlag = 0;
		Unit *unit = (Unit *)dequeueCircular(FPMULT);
		free(unit);
	}
	
	if (NB > 0 && wbBuffer -> fpdivFlag == 1 ){
        	double Res = wbBuffer -> fpdivResult;
        	int Dest = wbBuffer -> fpdivRSV -> Dest;
        	wbBuffer -> fpdivRSV -> Busy = 0;
        	ROB -> items[Dest] -> State = 3;
        	cpu -> fpRenamingRegister[ROB -> items[Dest] -> RenamingRegister] -> data = Res;
        	DictionaryRSVRowEntry *tmpEntry = RSV -> head;
		while(tmpEntry != NULL){
			RSVRow *tmp = tmpEntry -> value;
			while(tmp != NULL){
				if(tmp -> Qj == Dest){
					tmp -> fpVj = Res;
					tmp -> Qj = 0;
				}
				if(tmp -> Qk == Dest){
					tmp -> fpVk = Res;
					tmp -> Qk = 0;
				}
				tmp = tmp -> next;
			}
			tmpEntry = tmpEntry -> next;
		}
        	NB--;
		wbBuffer -> fpdivFlag = 0;
		Unit *unit = (Unit *)dequeueCircular(FPDIV);
		free(unit);
        }

	if (NB > 0 && wbBuffer -> buFlag == 1){
		int Res = wbBuffer -> buResult;
		int Dest = wbBuffer -> buRSV -> Dest;
		wbBuffer -> buRSV -> Busy = 0;
		ROB -> items[Dest] -> State = 3;
        	cpu -> intRenamingRegister[ROB -> items[Dest] -> RenamingRegister]-> data = Res;
		NB--;
		wbBuffer -> buFlag = 0;
		Unit *unit = (Unit *)dequeueCircular(BU);
		free(unit);
	}
}



void executeStage(){

	DictionaryEntry *dataCacheElement;
	
	DictionaryRSVRowEntry *tmpEntry;
	RSVRow *tmpRSV;

	void *addrPtr;
        void *valuePtr;

	//INT unit execution
	if(getCountCircularQueue(INT) == 0){
		//Check input
		tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "INT");
        	tmpRSV = tmpEntry -> value;
        	while(tmpRSV != NULL){
            		if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
                    		Unit *newINT = (Unit *)malloc(sizeof(Unit));
                    		newINT -> count = 1;
                    		newINT -> rsv = tmpRSV;
                    		enqueueCircular(INT, newINT);
                    		break;
            		}
            		tmpRSV = tmpRSV -> next;
        	}
	}
	//do execution
    	if (getCountCircularQueue(INT) > 0){
		if(((Unit *)getHeadCircularQueue(INT)) -> count == 1 && wbBuffer -> intFlag == 0){
			tmpRSV = ((Unit *)getHeadCircularQueue(INT)) -> rsv;
			wbBuffer -> intRSV = tmpRSV;
			wbBuffer -> intFlag = 1;
			switch(tmpRSV -> op){
				case ANDI:
					wbBuffer -> intResult = tmpRSV -> intVj & tmpRSV -> A;
					break;
				case AND:
					wbBuffer -> intResult = tmpRSV -> intVj & tmpRSV -> intVk;
					break;
				case ORI:
					wbBuffer -> intResult = tmpRSV -> intVj | tmpRSV -> A;
					break;
				case OR:
					wbBuffer -> intResult = tmpRSV -> intVj | tmpRSV -> intVk;
					break;
				case SLTI:
					wbBuffer -> intResult = tmpRSV -> intVj < tmpRSV -> A ? 1 : 0;
					break;
				case SLT:
					wbBuffer -> intResult = tmpRSV -> intVj < tmpRSV -> intVk ? 1 : 0;
					break;
				case DADDI:
					wbBuffer -> intResult = tmpRSV -> intVj + tmpRSV -> A;
					break;
				case DADD:
					wbBuffer -> intResult = tmpRSV -> intVj + tmpRSV -> intVk;
					break;
				case DSUB:
					wbBuffer -> intResult = tmpRSV -> intVj - tmpRSV -> intVk;
					break;
				default:
					break;
			}
		}
	}

	//MULT unit execution
	if(getCountCircularQueue(MULT) > 0){
		if(((Unit *)getHeadCircularQueue(MULT)) -> count < 4){
			//do count++
			int i = MULT -> head;
			int k = getCountCircularQueue(MULT);
			while(k > 0){
				((Unit *)(MULT -> items[i])) -> count++;
				i = (i + 1) % MULT -> size;
				k--;
			}
			//check unit output
			if(((Unit *)getHeadCircularQueue(MULT)) -> count == 4){
				tmpRSV = ((Unit *)getHeadCircularQueue(MULT)) -> rsv;
                		wbBuffer -> multRSV = tmpRSV;
                		wbBuffer -> multResult = tmpRSV -> intVj * tmpRSV -> intVk;
				wbBuffer -> multFlag = 1;
			}
			//check unit input
			tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "MULT");
			tmpRSV = tmpEntry -> value;
			while(tmpRSV != NULL){
                if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
                                    Unit *newMULT = (Unit *)malloc(sizeof(Unit));
                                    newMULT -> count = 1;
                                    newMULT -> rsv = tmpRSV;
                                    enqueueCircular(MULT, newMULT);
                                    break;
                            }
                            tmpRSV = tmpRSV -> next;
			}
		}
	} else {
		//check unit input
		tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "MULT");
        	tmpRSV = tmpEntry -> value;
		while(tmpRSV != NULL){
			if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
				Unit *newMULT = (Unit *)malloc(sizeof(Unit));
				newMULT -> count = 1;
				newMULT -> rsv = tmpRSV;
				enqueueCircular(MULT, newMULT);
				break;
			}
			tmpRSV = tmpRSV -> next;
		}
	}



	//FPadd unit execution
	if(getCountCircularQueue(FPADD) > 0){
		if(((Unit *)getHeadCircularQueue(FPADD)) -> count < 3){
			//do count++
			int i = FPADD -> head;
			int k = getCountCircularQueue(FPADD);
			while(k > 0){
				((Unit *)(FPADD -> items[i])) -> count++;
				i = (i + 1) % FPADD -> size;
				k--;
			}
			//check unit output
			if(((Unit *)getHeadCircularQueue(FPADD)) -> count == 3){
				tmpRSV = ((Unit *)getHeadCircularQueue(FPADD)) -> rsv;
                		wbBuffer -> fpaddRSV = tmpRSV;
				switch(tmpRSV -> op){
					case ADD_D: 
						wbBuffer -> fpaddResult = tmpRSV -> fpVj + tmpRSV -> fpVk;
						break;
					case SUB_D:
                        			wbBuffer -> fpaddResult = tmpRSV -> fpVj - tmpRSV -> fpVk;
                        			break;
					default:
						break;
				}
				wbBuffer -> fpaddFlag = 1;
			}
			//check unit input
			tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "FPadd");
            		tmpRSV = tmpEntry -> value;
			while(tmpRSV != NULL){
                    		if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
                            	Unit *newFPADD = (Unit *)malloc(sizeof(Unit));
                            	newFPADD -> count = 1;
                            	newFPADD -> rsv = tmpRSV;
                            	enqueueCircular(FPADD, newFPADD);
                            	break;
                    		}
                    	tmpRSV = tmpRSV -> next;
            		}
		}
	} else {
		//check unit input
		tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "FPadd");
		tmpRSV = tmpEntry -> value;
		while(tmpRSV != NULL){
			if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
				Unit *newFPADD = (Unit *)malloc(sizeof(Unit));
				newFPADD -> count = 1;
				newFPADD -> rsv = tmpRSV;
				enqueueCircular(FPADD, newFPADD);
				break;
			}
			tmpRSV = tmpRSV -> next;
		}
	}	
	


	
	//FPmult unit execution
    	if(getCountCircularQueue(FPMULT) > 0){
            if(((Unit *)getHeadCircularQueue(FPMULT)) -> count < 4){
                    //do count++
                    	int i = FPMULT -> head;
                    	int k = getCountCircularQueue(FPMULT);
                    	while(k > 0){
                            	((Unit *)(FPMULT -> items[i])) -> count++;
                            	i = (i + 1) % FPMULT -> size;
                            	k--;
                    	}
                    //check unit output
                    	if(((Unit *)getHeadCircularQueue(FPMULT)) -> count == 4){
                            	tmpRSV = ((Unit *)getHeadCircularQueue(FPMULT)) -> rsv;
                            	wbBuffer -> fpmultRSV = tmpRSV;
                            	wbBuffer -> fpmultResult = tmpRSV -> fpVj * tmpRSV -> fpVk;
                            	wbBuffer -> fpmultFlag = 1;
                    	}
                    //check unit input
                    	tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "FPmult");
			tmpRSV = tmpEntry -> value;
            		while(tmpRSV != NULL){
                        	if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
                                	Unit *newFPMULT = (Unit *)malloc(sizeof(Unit));
                                	newFPMULT -> count = 1;
                                	newFPMULT -> rsv = tmpRSV;
                                	enqueueCircular(FPMULT, newFPMULT);
                                	break;
                        	}
                        tmpRSV = tmpRSV -> next;
                    	}
            }
    	} else {
        //check unit input
        	tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "FPmult");
        	tmpRSV = tmpEntry -> value;
        	while(tmpRSV != NULL){
            		if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
                	Unit *newFPMULT = (Unit *)malloc(sizeof(Unit));
                	newFPMULT -> count = 1;
                	newFPMULT -> rsv = tmpRSV;
                	enqueueCircular(FPMULT, newFPMULT);
               		break;
                	}
            	tmpRSV = tmpRSV -> next;
            	}
    	}
		
	//FPdiv unit execution
	if(getCountCircularQueue(FPDIV) > 0){
		if(((Unit *)getHeadCircularQueue(FPDIV)) -> count < 8){
                	((Unit *)getHeadCircularQueue(FPDIV)) -> count++;
			if(((Unit *)getHeadCircularQueue(FPDIV)) -> count == 8){
                		tmpRSV = ((Unit *)getHeadCircularQueue(FPDIV)) -> rsv;
                		wbBuffer -> fpdivRSV = tmpRSV;
				wbBuffer -> fpdivResult = tmpRSV -> fpVj / tmpRSV -> fpVk;
                	wbBuffer -> fpdivFlag = 1;
			}
		}
	} else {
		//check unit input
        	tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "FPdiv");
		tmpRSV = tmpEntry -> value;
        	while(tmpRSV != NULL){
                	if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
                        	Unit *newFPDIV = (Unit *)malloc(sizeof(Unit));
                        	newFPDIV -> count = 1;
                        	newFPDIV -> rsv = tmpRSV;
                        	enqueueCircular(FPDIV, newFPDIV);
                        	break;
                	}
                	tmpRSV = tmpRSV -> next;
        	}
	}

	
	//LS unit execution
	if (getCountCircularQueue(LS) > 0){
		if(((Unit *)getHeadCircularQueue(LS)) -> count == 1 && wbBuffer -> lsFlag == 0){
			tmpRSV = ((Unit *)getHeadCircularQueue(LS)) -> rsv;
			wbBuffer -> lsRSV = tmpRSV;
			switch(tmpRSV -> op){
				case LD:
					wbBuffer -> lsAddr = tmpRSV -> intVj + tmpRSV -> A;
					//Check memory address confliction
					int conflict = 0;
					int i = ROB -> head;
					while(i != (ROB -> tail + 1) % ROB -> size){
						if (ROB -> items[i] -> InsROB -> op == SD && ROB -> items[i] -> Destination == wbBuffer -> lsAddr){
							conflict = 1;
							break;
						}
						i++;
					}
					//load value if no confliction
					if (conflict == 0){
						wbBuffer -> lsFlag = 1;
						*((int*)addrPtr) = wbBuffer -> lsAddr;
						dataCacheElement = getValueChainByDictionaryKey (dataCache, addrPtr);
		
						valuePtr = dataCacheElement -> value -> value;
						wbBuffer -> lsIntResult =  (int) *((double*)valuePtr);
					}
					break;
				case L_D:
					wbBuffer -> lsAddr = tmpRSV -> intVk + tmpRSV -> A;
                                        //Check memory address confliction
					conflict = 0;
                    			i = ROB -> head;
                    			while(i != (ROB -> tail + 1) % ROB -> size){
                        			if (ROB -> items[i] -> InsROB -> op == S_D && ROB -> items[i] -> Destination == wbBuffer -> lsAddr){
                                			conflict = 1;
                                			break;
                        			}
                        			i++;
                    			}
					//load value if no confliction
                    			if (conflict == 0){
                        			wbBuffer -> lsFlag = 2;
                        			*((int*)addrPtr) = wbBuffer -> lsAddr;
                        			dataCacheElement = getValueChainByDictionaryKey (dataCache, addrPtr);

                        			valuePtr = dataCacheElement -> value -> value;
                        			wbBuffer -> lsFpResult = *((double*)valuePtr);
                    			}
                    			break;
				case SD:
					wbBuffer -> lsAddr = tmpRSV -> intVk + tmpRSV -> A;
					wbBuffer -> lsIntResult = tmpRSV -> intVk;
					wbBuffer -> lsFlag = -1;
					break;
				case S_D:
                    			wbBuffer -> lsAddr = tmpRSV -> intVj + tmpRSV -> A;
                    			wbBuffer -> lsFpResult = tmpRSV -> fpVk;
                    			wbBuffer -> lsFlag = -2;
                    			break;
					default:
						break;
			}
		}
	} else {
		//check unit input
        	tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "LS");
		tmpRSV = tmpEntry -> value;
        	while(tmpRSV != NULL){
                	if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
                        	Unit *newLS = (Unit *)malloc(sizeof(Unit));
                        	newLS -> count = 1;
                        	newLS -> rsv = tmpRSV;
                        	enqueueCircular(LS, newLS);
                        	break;
                	}
                	tmpRSV = tmpRSV -> next;
        	}
	}	
	
	//BU unit execution
	if (getCountCircularQueue(BU) > 0){
		if(((Unit *)getHeadCircularQueue(BU)) -> count == 1 && wbBuffer -> lsFlag == 0){
			tmpRSV = ((Unit *)getHeadCircularQueue(BU)) -> rsv;
			wbBuffer -> lsRSV = tmpRSV;
			//get result 0---taken -1---not taken
			switch(tmpRSV -> op){
				case BNE:
					wbBuffer -> buResult = tmpRSV -> intVj != tmpRSV -> intVk ? 0 : -1;
					break;
				case BNEZ:
					wbBuffer -> buResult = tmpRSV -> intVj != 0 ? 0 : -1;
					break;
				case BEQ:
                        		wbBuffer -> buResult = tmpRSV -> intVj == tmpRSV -> intVk ? 0 : -1;
                        		break;
                		case BEQZ:
                        		wbBuffer -> buResult = tmpRSV -> intVj == 0 ? 0 : -1;
					break;
					default:
						break;
			}
			//Update BTB
			if (wbBuffer -> buResult == 0 && ROB -> items[tmpRSV -> Dest] -> InsROB -> predictFlag == -1){
				int i;
				for (i = 0; i < 16; i++){
					if (BTB[i] -> InstructionPC == -1){
						BTB[i] -> InstructionPC = ROB -> items[tmpRSV -> Dest] -> InsROB -> InstructionPC;
						BTB[i] -> PredictedPC = tmpRSV -> A;
						break;
					}
				}
			}
			if (wbBuffer -> buResult == -1 && ROB -> items[tmpRSV -> Dest] -> InsROB -> predictFlag == 0){
                    		int i;
                    		for (i = 0; i < 16; i++){
                            		if (BTB[i] -> InstructionPC == ROB -> items[tmpRSV -> Dest] -> InsROB -> InstructionPC){
                                    		BTB[i] -> InstructionPC = -1;
                                    		BTB[i] -> PredictedPC = -1;
                                    		break;
                            		}
                    		}
            		}
		}
	} else {
		//check unit input
        	tmpEntry = RSV -> head;
        	tmpEntry = getValueChainByDictionaryRSRowKey(RSV, "BU");
        	tmpRSV = tmpEntry -> value;
		while(tmpRSV != NULL){
            		if (tmpRSV -> Busy == 1 && tmpRSV -> Qj == 0 && tmpRSV -> Qk == 0){
                    		Unit *newBU = (Unit *)malloc(sizeof(Unit));
                    		newBU -> count = 1;
                    		newBU -> rsv = tmpRSV;
                    		enqueueCircular(BU, newBU);
                    		break;
            		}
            		tmpRSV = tmpRSV -> next;
        	}
	}
	
}
