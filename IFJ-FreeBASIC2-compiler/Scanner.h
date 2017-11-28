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

TokenType CompareWithKeywords(char* string);
tToken* ScannerError(tToken* Token);
tToken* GetNextToken();
tToken* LoadToken();
tToken* ReturnToken();
void ResetScanner();
int CheckEOL(char c);
int CheckIfEscapeSeuquenceIsValid(char c, tToken *Token);
int CheckIfMathSymbol(char c);

#endif
