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
	S_BlockcommentOrDivide,
	S_Assign,
	S_Semicolon,
	S_Colon,
	S_Add,
	S_Sub,
	S_Multiply,
	S_Intdivide,
	S_LeftBracket,
	S_RightBracket,
	S_EOL,
	S_EOF,
	S_Base,
	S_BINARY,
	S_OCTANE,
	S_HEXA

} tState;

tToken *ReturnStateType(tToken *Token, TokenType mType);
TokenType CompareWithKeywords(char* string);
tToken* ScannerError(tToken* Token);
tToken* GetNextToken();
tToken* LoadToken();
tToken* ReturnToken();
void ResetScanner();
int CheckEOL(char c);
int CheckIfEscapeSeuquenceIsValid(char c, tToken *Token);
int CheckIfMathSymbol(char c);
int BlockCommentClear(tToken *Token);
void AddEscapeSequenceToString(char val_1, char val_2, char val_3, tToken* Token, int Lenght);


#endif
