#include "TestExpectToken.h"

int Exp_ID(char* expectedString)
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_ID || strcmp(expectedString, token->String))
	{
		return -1;
	}
	return 0;
}

int Exp_ERR()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_LexERROR)
	{
		return -1;
	}
	
	return 0;
}

int Exp_EOF()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_EOF)
	{
		return -1;
	}
	
	return 0;
}

int Exp_EOL()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_EOL)
	{
		return -1;
	}
	
	return 0;
}

int Exp_INTVALUE(int expected)
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_INTVALUE || expected != token->IntVal)
	{
		return -1;
	}
	
	return 0;
}

int Exp_DOUBLEVALUE(double expected)
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_DOUBLEVALUE || expected != token->DoubleVal)
	{
		return -1;
	}
	
	return 0;
}

int Exp_STRINGVALUE(char* expectedString)
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_STRINGVALUE || strcmp(expectedString, token->String))
	{
		return -1;
	}
	
	return 0;
}

int Exp_ADD()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_SUB)
	{
		return -1;
	}
	
	return 0;
}

int Exp_SUB()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_SUB)
	{
		return -1;
	}
	
	return 0;
}

int Exp_MULTIPLY()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_MULTIPLY)
	{
		return -1;
	}

	return 0;
}

int Exp_DIVIDE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_DIVIDE)
	{
		return -1;
	}
	
	return 0;
}

int Exp_INTDIVIDE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_INTDIVIDE)
	{
		return -1;
	}
	
	return 0;
}

int Exp_SEMICOLON()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_SEMICOLON)
	{
		return -1;
	}
	
	return 0;
}

int Exp_COLON()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_COLON)
	{
		return -1;
	}
	
	return 0;
}

int Exp_LEFTBRACKET()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_LEFTBRACKET)
	{
		return -1;
	}
	
	return 0;
}

int Exp_RIGHTBRACKET()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_RIGHTBRACKET)
	{
		return -1;
	}
	
	return 0;
}

int Exp_ASSIGN()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_ASSIGN)
	{
		return -1;
	}
	
	return 0;
}

int Exp_NOTEQUAL()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_NOTEQUAL)
	{
		return -1;
	}
	
	return 0;
}

int Exp_LESS()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_LESS)
	{
		return -1;
	}
	
	return 0;
}

int Exp_GREATER()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_GREATER)
	{
		return -1;
	}
	
	return 0;
}

int Exp_GREATEROREQUAL()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_GREATEROREQUAL)
	{
		return -1;
	}
	
	return 0;
}

int Exp_LESSEROREQUAL()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_LESSEROREQUAL)
	{
		return -1;
	}
	
	return 0;
}

int Exp_AS()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_AS)
	{
		return -1;
	}
	
	return 0;
}

int Exp_ASC()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_ASC)
	{
		return -1;
	}
	
	return 0;
}

int Exp_DECLARE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_DECLARE)
	{
		return -1;
	}
	
	return 0;
}

int Exp_DIM()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_DIM)
	{
		return -1;
	}
	
	return 0;
}

int Exp_DO()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_DO)
	{
		return -1;
	}
	
	return 0;
}

int Exp_DOUBLE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_DOUBLE)
	{
		return -1;
	}
	
	return 0;
}

int Exp_ELSE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_ELSE)
	{
		return -1;
	}
	
	return 0;
}

int Exp_END()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_END)
	{
		return -1;
	}
	
	return 0;
}

int Exp_CHR()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_CHR)
	{
		return -1;
	}
	
	return 0;
}

int Exp_FUNCTION()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_FUNCTION)
	{
		return -1;
	}
	
	return 0;
}

int Exp_IF()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_IF)
	{
		return -1;
	}
	
	return 0;
}

int Exp_INPUT()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_INPUT)
	{
		return -1;
	}
	
	return 0;
}

int Exp_INTEGER()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_INTEGER)
	{
		return -1;
	}
	
	return 0;
}

int Exp_LENGHT()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_LENGHT)
	{
		return -1;
	}
	
	return 0;
}

int Exp_LOOP()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_LOOP)
	{
		return -1;
	}
	
	return 0;
}

int Exp_PRINT()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_PRINT)
	{
		return -1;
	}
	
	return 0;
}

int Exp_RETURN()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_RETURN)
	{
		return -1;
	}
	
	return 0;
}

int Exp_SCOPE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_SCOPE)
	{
		return -1;
	}
	
	return 0;
}

int Exp_STRING()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_STRING)
	{
		return -1;
	}
	
	return 0;
}

int Exp_SUBSTRING()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_SUBSTRING)
	{
		return -1;
	}
	
	return 0;
}

int Exp_THEN()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_THEN)
	{
		return -1;
	}
	
	return 0;
}

int Exp_WHILE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_WHILE)
	{
		return -1;
	}
	
	return 0;
}

int Exp_NOT()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_NOT)
	{
		return -1;
	}
	
	return 0;
}

