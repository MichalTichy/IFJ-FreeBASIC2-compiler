#include "Token.h"
#include "ManagedMalloc.h"
#include "errors.h"

// Basic allocated lenght of string
//#define LenghtOfString 10

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

tToken* InitString(tToken *Token, long unsigned int LenghtOfString)
{
	if ((Token->String = mmalloc(sizeof(char) * LenghtOfString + 1)) == NULL)
	{
		mfreeall();
		ERR_CODE code = INTERNAL_ERR;
		exit(code);
	}

	Token->String[0] = '\0';
	return Token;
}
