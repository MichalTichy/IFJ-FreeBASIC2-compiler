#include <stdio.h>
#include "Token.h"

// Basic allocated lenght of string
#define LenghtOfString 10

void InitToken(tToken *Token)
{
	if (Token = (tToken *)malloc(sizeof(tToken)) == NULL)
	{
		return NULL;
	}

	Token->IntVal = 0;
	Token->DoubleVal = 0.0;
	Token->String = NULL;
	Token->Lenght;
}

void InitString(tToken *Token)
{
	if (Token->String = (char *)malloc(sizeof(char) * LenghtOfString) == NULL)
	{
		Token->Type = T_ERR;
	}
}

void ReallocString(tToken *Token)
{
	if (Token->String = (char *)realloc(sizeof(char) * LenghtOfString) == NULL)
	{
		if (Token->String != NULL)
		{
			free(Token->String);
		}
		Token->Type = T_ERR;
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