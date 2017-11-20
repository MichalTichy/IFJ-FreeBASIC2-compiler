#include "Token.h"

// Basic allocated lenght of string
#define LenghtOfString 10

/**
 * Function allocate and initialise token
 * when malloc fail token is NULL.
 */

void InitToken(tToken *Token)
{
	Token->IntVal = 0;
	Token->DoubleVal = 0.0;
	Token->String = NULL;
	Token->Lenght = 0;
}

/**
* Function allocate string in token
* when malloc fail type of token is set to T_ERR. 
*/

tToken* InitString(tToken *Token)
{
	if ((Token->String = (char *) malloc(sizeof(char) * LenghtOfString + 1)) == NULL)
	{
		Token->String = NULL;
		Token->Type = T_ERR;
	}
	return Token;
}

/**
* Function reallocate string in token when malloc fail type of token
* is set to T_ERR and free string from memory.
*/

void ReallocString(tToken *Token)
{
	if ((Token->String = (char *) realloc(Token->String, sizeof(char) * LenghtOfString)) == NULL)
	{
		if (Token->String != NULL)
		{
			free(Token->String);
		}
		Token->Type = T_ERR;
	}
}

/**
* Function free token from memory.
*/
void FreeToken(tToken *Token)
{
	if (Token->String != NULL)
	{
		free(Token->String);
	}
	free(Token);
}