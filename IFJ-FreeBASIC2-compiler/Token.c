#include <stdio.h>
#include "Token.h"

// Basic allocated lenght of string
#define int LenghtOfString = 10;

void InitToken()
{
	Token.Type;
	Token.IntVal = 0;
	Token.DoubleVal = 0.0;
	Token.String = NULL;
	Token.Lenght;
}

int InitString()
{
	if (Token.String = (char *)malloc(sizeof(char) * LenghtOfString) == NULL)
		return -1;
}

int ReallocString()
{
	if (Token.String = (char *)realloc(sizeof(char) * LenghtOfString) == NULL)
	{
		if (Token.String != NULL)
		{
			free(Token.String);
		}
		return -1;
	}	
}

void FreeString()
{
	free(Token.String);
}