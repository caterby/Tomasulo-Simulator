/*
 * DictionaryRSRow.h
 *
 *  Created on: Oct 2, 2015
 *      Author: DebashisGanguly
 */

#ifndef GLOBAL_ADT_DICTIONARY_H_RS
#define GLOBAL_ADT_DICTIONARY_H_RS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include </afs/cs.pitt.edu/usr0/jih127/private/TomasuloSimulator/OurForm.h>
#include "../DataTypes.h"

//below JianfengHe
typedef struct _ReserSROW{
    char* Key;
    char name;
    OpCode op;
    int Busy;

    int intVj;
    int intVk;
    float fpVj;
    float fpVk;

    int Qj;
    int Qk;

    int Dest;
    int A;

    struct _ReserSROW *next;
}RSVRow;


char* UnitName[7];//= {"INT", "MULT", "LS", "FPadd", "FPmult", "FPdiv", "BU"};
int LenFuncUnit[7];// = {4, 2, 4, 3, 4, 2, 2};


//char* UnitName[7] = {"INT", "MULT", "LS", "FPadd", "FPmult", "FPdiv", "BU"};
//int LenFuncUnit[7] = {4, 2, 4, 3, 4, 2, 2};
//int LenFuncUnit[7];
//char* UnitName[7];

//upper JianfengHe


typedef int (*_getHashCode2)(char *key);
typedef int (*_compareValues2)(void *value1, void *value2);

typedef struct _dictionaryRSRowValue {
	RSVRow *value;
	struct _dictionaryRSRowValue *next;
} DictionaryRSRowValue;

typedef struct _dictionaryRSRowEntry {
	int hashKey;
	char *key;
	RSVRow *value;
	void *next;
} DictionaryRSVRowEntry;

typedef struct _dictionaryRSRow {
	DictionaryRSVRowEntry *head;
	_getHashCode2 getHashCode;
	_compareValues2 compareValues;
} DictionaryRSRow;

//below JianfengHe
static inline RSVRow* createRSRow(char* Key){
        RSVRow* res = (RSVRow*)malloc(sizeof(RSVRow));
        res->Key = Key;
        res->Busy = 0;
        res->Qj = -1;
        res->Qk = -1;
        res->Dest = -1;
        res->A = -1;
	res->next = NULL;
        return res;
}

static inline int getHashCode(int* key){

        return *key;
}

static inline int RS_getHashCode(char* key){
        char* Unitname[7] = {"INT", "MULT", "LS", "FPadd", "FPmult", "FPdiv", "BU"};
        int i = 0;
        for(i=0; i<7; i++){
                if (key == Unitname[i]){
                        return i;
}
}
        return -1;
}

static inline int compareValues(void* value1, void* value2){
        if(value1 == value2){
                return 0;
        }
        else{
                return 1;
        }
}

//Upper JianfengHe

static inline DictionaryRSRow *createDictionaryRSRow (_getHashCode2 getHashCode, _compareValues2 compareValues) {
	DictionaryRSRow *table = (DictionaryRSRow *)malloc (sizeof(DictionaryRSRow));
	table -> head = NULL;
	table -> getHashCode = getHashCode;
	table -> compareValues = compareValues;
	return table;
}


static inline DictionaryRSRowValue *createDictionaryRSRowValue (RSVRow *value)  {
	DictionaryRSRowValue *newValue = (DictionaryRSRowValue *)malloc (sizeof(DictionaryRSRowValue));
	newValue -> value = value;
	newValue -> next = NULL;
	return newValue;
}

static inline DictionaryRSVRowEntry *createDictionaryRSVRowEntry (DictionaryRSRow *table, char *key, RSVRow *value) {
	DictionaryRSVRowEntry *newEntry = (DictionaryRSVRowEntry *)malloc (sizeof(DictionaryRSVRowEntry));
	newEntry -> hashKey = table -> getHashCode (key);
	newEntry -> key = key;
	newEntry -> value = value;
	newEntry -> next = NULL;
//	printf("Entry Address is %d\n", newEntry);
	return newEntry;
}

static inline DictionaryRSVRowEntry *getValueChainByDictionaryRSRowKey (DictionaryRSRow *table, char *key) {
	DictionaryRSVRowEntry *match = NULL;
	DictionaryRSVRowEntry *current;

	int hashKey = table -> getHashCode (key);
	if (table != NULL) {
		for (current = table -> head; current != NULL; current = current -> next)
			if (current -> hashKey == hashKey) {
				match = current;
				break;
			}
	}
	return match;
}

static inline void addValueToDictionaryRSRowChain (DictionaryRSVRowEntry *existing, RSVRow *value, _compareValues2 compareValues, char* Key) {
	RSVRow *previous;
	RSVRow *current;
	RSVRow *match = NULL;

	for (current = existing -> value; current != NULL; previous = current, current = current -> next)
		if (compareValues (value, current) == 0) {
			match = current;
		}

	if (match == NULL)
		previous -> next = createRSRow(Key);
}

static inline void addDictionaryRSVRowEntry (DictionaryRSRow *table, char *key, RSVRow *value) {
	DictionaryRSVRowEntry *existing;

	if (table != NULL) {
		if (table -> head == NULL) {
			table -> head = createDictionaryRSVRowEntry(table, key, value);
		} else {
			if ((existing = getValueChainByDictionaryRSRowKey(table, key)) != NULL) {
				addValueToDictionaryRSRowChain (existing, value, table -> compareValues, char* key);
			} else {
				DictionaryRSVRowEntry *previous;
				DictionaryRSVRowEntry *current;

				for (current = table -> head; current != NULL; previous = current, current = current -> next);

				previous -> next = createDictionaryRSVRowEntry (table, key, value);
			}
		}
	}
}

static inline void removeDictionaryRSRowEntriesByKey (DictionaryRSRow *table, char *key) {
	DictionaryRSVRowEntry *previous;
	DictionaryRSVRowEntry *current;
	DictionaryRSVRowEntry *match = NULL;

	int hashKey = table -> getHashCode (key);

	if (table != NULL) {
		for (current = table -> head; current != NULL; previous = current, current = current -> next) {
			if (current -> hashKey == hashKey) {
				match = current;
				break;
			}
		}

		if (match != NULL) {
			if (match == table -> head) {
				if (match -> next == NULL) {
					table -> head = NULL;
					free (match);
				} else {
					table -> head = table -> head -> next;
					free (match);
				}
			} else {
				previous -> next = match -> next;
				free (match);
			}
		}
	}
}
/*
static inline void removeDictionaryRSVRowEntryByKeyValue (DictionaryRSRow *table, int *key, void *value) {
	DictionaryRSVRowEntry *matchedEntry = getValueChainByDictionaryRSRowKey(table, key);

	DictionaryRSRowValue *previous;
	DictionaryRSRowValue *current;
	DictionaryRSRowValue *match = NULL;

	if (matchedEntry != NULL) {
		for (current = matchedEntry -> value; current != NULL; previous = current, current = current -> next)
			if (table -> compareValues (value, current -> value) == 0) {
				match = current;
				break;
			}

		if (match != NULL) {
			if (match == matchedEntry -> value) {
				if (match -> next == NULL)
					removeDictionaryRSRowEntriesByKey (table, key);
				else {
					matchedEntry -> value = matchedEntry -> value -> next;
					free (match);
				}
			} else {
				previous -> next = current -> next;
				free (matchedEntry -> value);
			}
		}
	}
}
*/

DictionaryRSRow* RSV;
static inline void createRSV(){
	//DictionaryRSRow* RSV;
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
	printf("main iter = %d\n", jsqUnitKindNum);
        for (jsqUnitColNum = 0; jsqUnitColNum < LenFuncUnit[jsqUnitKindNum] - 1; jsqUnitColNum++){
        RSVRow* rsRowMidAfter;
        rsRowMidAfter = createRSRow(UnitName[jsqUnitKindNum]);
        rsRowMid -> next = rsRowMidAfter;
        rsRowMid = rsRowMidAfter;
	printf("Sub iter = %d\n", jsqUnitColNum);
}
}
printf("RSV created\n");
}

#endif /* GLOBAL_ADT_DICTIONARY_H_RS */
