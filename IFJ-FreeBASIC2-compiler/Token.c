#include <stdio.h>
#include "Token.h"

// Basic allocated lenght of string
#define int lenghtOfString = 10;

void InitToken()
{
	Token.type;
	Token.intVal = 0;
	Token.doubleVal = 0.0;
	Token.string = NULL;
}

int InitString()
{
	if (Token.string = (char *)malloc(sizeof(char) * lenghtOfString) == NULL)
		return -1;
}
