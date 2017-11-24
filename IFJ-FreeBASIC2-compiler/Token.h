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
tToken* InitString(tToken *Token, long unsigned int LenghtOfString);
void ReallocString(tToken *Token, long unsigned int LenghtOfString);
void FreeToken(tToken *Token);

#endif

