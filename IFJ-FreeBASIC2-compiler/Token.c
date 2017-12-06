#include "Token.h"
#include "ManagedMalloc.h"
#include "errors.h"

// Basic allocated lenght of string
#define BasicLenghtOfString 10

void InitToken(tToken *Token)
{
	Token->IntVal = 0;
	Token->DoubleVal = 0.0;
	Token->String = NULL;
	Token->Lenght = 0;
}

tToken* InitString(tToken *Token)
{
	if ((Token->String = mmalloc(sizeof(char) * BasicLenghtOfString + 1)) == NULL)
	{
		exitSecurely(INTERNAL_ERR);
	}

	Token->String[0] = '\0';
	return Token;
}

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
