#pragma once

#include "TokenType.h"

typedef struct {
	TokenType Type;
	int IntVal;
	double DoubleVal;
	char *String;
	int Lenght;
} tToken;

void InitToken(tToken *Token);
void InitString(tToken *Token);
void ReallocString(tToken *Token);
void FreeToken(tToken *Token);
