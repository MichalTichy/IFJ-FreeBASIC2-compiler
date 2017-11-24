#ifndef SCANNER
#define SCANNER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "List.h"

typedef enum {

	S_Start,
	S_Number,
	S_ID,
	S_Less,
	S_Greater,
	S_ExcString,
	S_Double,
	S_Exp,
	S_ExpSign,
	S_Comment,
	S_BlockcommentOrDivide

}tState;

void AddToString(char c, tToken *Token);
void RemoveString(tToken *Token);
void ConvertStringToInteger(tToken *Token);
void ConvertStringToDouble(tToken *Token);
TokenType CompareWithKeywords(char* string);
tToken* GetNextToken();
tToken* LoadToken();
tToken* ReturnToken();
void ResetScanner();
int CheckEOL(char c);

#endif
