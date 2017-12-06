/**
*	Project: IFJ17 Compiler
*
*	FILE: token.c
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

#include "Token.h"
#include "ManagedMalloc.h"
#include "errors.h"

// Basic allocated lenght of string
#define BasicLenghtOfString 10


/**
*  Function that initialize token
*/

void InitToken(tToken *Token)
{
	Token->IntVal = 0;
	Token->DoubleVal = 0.0;
	Token->String = NULL;
	Token->Lenght = 0;
}

/**
*  Function that initialize string of token.
*  When malloc is unsuccessful safe exit program with INTERNAL_ERR.
*/

tToken* InitString(tToken *Token)
{
	if ((Token->String = mmalloc(sizeof(char) * BasicLenghtOfString + 1)) == NULL)
	{
		exitSecurely(INTERNAL_ERR);
	}

	Token->String[0] = '\0';
	return Token;
}

/**
*  Function that add string into token.
*  When string has no space, realloc string.
*/

void AddToString(char c, tToken *Token, int LenghtOfString)
{
	if (Token->Lenght % 10 == 0)
	{
		LenghtOfString += 10;
		ReallocString(Token, LenghtOfString);
	}

	Token->Lenght = Token->Lenght + 1;
	Token->String[Token->Lenght] = '\0';
	Token->String[Token->Lenght - 1] = c;
}


/**
*  Function that realocate string by LenghtOfString.
*  When realloc is unsuccessful save exit program with internall error.
*/

void ReallocString(tToken *Token, int LenghtOfString)
{
	if ((Token->String = mrealloc(Token->String, sizeof(char) * (size_t)LenghtOfString)) == NULL)
	{
		exitSecurely(INTERNAL_ERR);
	}
}


void ConvertStringToInteger(tToken *Token, int numberType)
{
	Token->IntVal = strtol(Token->String, NULL, numberType);
	Token->Type = T_INTVALUE;
}

void ConvertStringToDouble(tToken *Token)
{
	Token->DoubleVal = strtod(Token->String, NULL);
	Token->Type = T_DOUBLEVALUE;
}
