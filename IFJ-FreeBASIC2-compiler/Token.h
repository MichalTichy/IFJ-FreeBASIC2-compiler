#ifndef TOKEN
#define TOOKEN
#include <stdio.h>
#include <stdlib.h>
#include "TokenType.h"

typedef struct {
	TokenType Type;
	long int IntVal;
	double DoubleVal;
	char *String;
	int Lenght;
} tToken;

void InitToken(tToken *Token);
tToken* InitString(tToken *Token);
void AddToString(char c, tToken *Token, int LenghtOfString);
void ReallocString(tToken *Token, int LenghtOfString);
void ConvertStringToInteger(tToken *Token, int numberType);
void ConvertStringToDouble(tToken *Token);


#endif

