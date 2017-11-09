#include <stdio.h>
#include "Token.h"

// Basic allocated lenght of string
#define int LenghtOfString = 10;

tToken* InitToken()
{
	tToken Token;

	if (Token.String = (char *)malloc(sizeof(tToken)) == NULL)
	{
		return NULL;
	}

	Token.IntVal = 0;
	Token.DoubleVal = 0.0;
	Token.String = NULL;
	Token.Lenght;
}

int InitString(tToken *Token)
{
	if (Token->String = (char *)malloc(sizeof(char) * LenghtOfString) == NULL)
	{
		return -1;
	}
}

int ReallocString(tToken *Token)
{
	if (Token->String = (char *)realloc(sizeof(char) * LenghtOfString) == NULL)
	{
		if (Token->String != NULL)
		{
			free(Token->String);
		}
		return -1;
	}	
}

void FreeToken(tToken *Token)
{
	if (Token->String != NULL)
	{
		free(Token->String);
	}
	free(Token);
}