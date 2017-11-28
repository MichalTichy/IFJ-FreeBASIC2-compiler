#include "Token.h"
#include "string.h"
#include "ManagedMalloc.h"
#include "errors.h"


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
	if ((Token->String = mrealloc(Token->String, sizeof(char) * (size_t) LenghtOfString)) == NULL)
	{
		mfreeall();
		ERR_CODE code = INTERNAL_ERR;
		exit(code);
	}
}

void ConvertStringToInteger(tToken *Token)
{
	Token->IntVal = strtol(Token->String, NULL, 10);
	Token->Type = T_INTVALUE;
}

void ConvertStringToDouble(tToken *Token)
{
	Token->DoubleVal = strtod(Token->String, NULL);
	Token->Type = T_DOUBLEVALUE;
}