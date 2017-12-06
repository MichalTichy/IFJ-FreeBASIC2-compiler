/**
*	Project: IFJ17 Compiler
*
*	FILE: token.h
*
*	File author:
*	  Michal Martinu, xmarti78
*
*	Project authors:
*	  Michal Tichy, xtichy26
*	  Michal Martinu, xmarti78
*	  Gabriel Mastny, xmast02
*	  Ondra Deingruber, xdeing00
*
**/

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

