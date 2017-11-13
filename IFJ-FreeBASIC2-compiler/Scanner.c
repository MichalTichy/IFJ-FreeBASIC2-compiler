#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Token.h"
#include "Scanner.h"

//Language IFJ17 contain 35 keywords
#define LenghtOfReservedWords 13

/**
* Reserved words of IFJ17 language
*/

char *ReservedWords [LenghtOfReservedWords]=
{
	"and", "boolean", "continue", "elseif", "exit", "false",
	"for", "next", "not", "or", "shared", "static", "true"
};

/**
 * Operations with strings
 */

void AddToString(int c, tToken *Token)
{
	if (Token->Lenght % 10 == 0)
	{
		ReallocString(Token);
	}

	Token->Lenght = Token->Lenght + 1;
	Token->String[Token->Lenght-1] = (char) c;
}

void RemoveString(tToken *Token)
{
	if (Token->String != NULL)
	{
		free(Token->String);
		Token->String = NULL;
	}
	Token->Lenght = 0;
}

void ConvertStringToInteger(tToken *Token)
{
	Token->IntVal = strtol(Token->String, NULL, 10);
	RemoveString(Token);
}

void ConvertStringToDouble(tToken *Token)
{
	Token->DoubleVal = strtod(Token->String, NULL);
	RemoveString(Token);
}

TokenType CompareWithKeywords(char* string)
{
	TokenType Type;

	if (!strcmp (string, "as")) Type = T_AS;
	else if (!strcmp(string, "asc")) Type = T_ASC;
	else if (!strcmp(string, "declare")) Type = T_DECLARE;
	else if (!strcmp(string, "dim")) Type = T_DIM;
	else if (!strcmp(string, "do")) Type = T_DO;
	else if (!strcmp(string, "double")) Type = T_DOUBLE;
	else if (!strcmp(string, "else")) Type = T_ELSE;
	else if (!strcmp(string, "end")) Type = T_END;
	else if (!strcmp(string, "chr")) Type = T_CHR;
	else if (!strcmp(string, "function")) Type = T_FUNCTION;
	else if (!strcmp(string, "if")) Type = T_IF;
	else if (!strcmp(string, "input")) Type = T_INPUT;
	else if (!strcmp(string, "integer")) Type = T_INTEGER;
	else if (!strcmp(string, "lenght")) Type = T_LENGHT;
	else if (!strcmp(string, "loop")) Type = T_LOOP;
	else if (!strcmp(string, "print")) Type = T_PRINT;
	else if (!strcmp(string, "return")) Type = T_RETURN;
	else if (!strcmp(string, "scope")) Type = T_SCOPE;
	else if (!strcmp(string, "string")) Type = T_STRING;
	else if (!strcmp(string, "then")) Type = T_THEN;
	else if (!strcmp(string, "while")) Type = T_WHILE;
	else
	{
		for (int i = 0; i < LenghtOfReservedWords; i++)
		{
			Type = T_ID;

			if (!strcmp(string, ReservedWords[i]))
			{
				Type = T_RESERVEDWORD;
				break;
			}
		}
	}
	
	return Type;
}

/**
 * Function to get next token from source file.
 */

tToken* GetNextToken()
{
	tToken *Token;
	tState state = S_Start;
	int c;
	
	//Malloc Token
	if ((Token = (tToken *)malloc(sizeof(tToken))) == NULL)
	{
		Token = NULL;
	}

	InitToken(Token);
	
	c = tolower(getchar());

	while (1)
	{

	switch (state)
	{
		case S_Start:
		{
			if (isblank(c))
			{
				state = S_Start;
				c = tolower(getchar());
				break;
			}
			else if (c == '\n')
			{
				state = S_Start;
				c = tolower(getchar());
				break;
			}
			else if (c == EOF)
			{
				Token->Type = T_EOF;
			}
			else if (c >= '0' && c <= '9') 
			{
				InitString(Token);
				AddToString(c, Token);
				state = S_Number;
				break;
			}
			else if ((c >= 'a' && c <= 'z') || c == '_') 
			{
				InitString(Token);
				AddToString(c, Token);
				state = S_ID;
				break;
			}
			else if (c == '<') 
			{
				state = S_Less;
				break;
			}
			else if (c == '>') 
			{
				state = S_Greater;
				break;
			}
			else if (c == ';') 
			{
				Token->Type = T_SEMICOLON;
				return Token;
			}
			else if (c == ',') 
			{
				Token->Type = T_COLON;
				return Token;
			}
			else if (c == '+') 
			{
				Token->Type = T_ADD;
				return Token;
			}
			else if (c == '-') 
			{
				Token->Type = T_SUB;
				return Token;
			}
			else if (c == '*') 
			{
				Token->Type = T_MULTIPLY;
				return Token;
			}
			else if (c == '/') 
			{
				Token->Type = T_INTDIVIDE;
				return Token;
			}
			else if (c == '!') 
			{
				InitString(Token);
				state = S_ExcString;
				break;
			}
			else if (c == '.') 
			{
				InitString(Token);
				state = S_Dot;
				break;
			}
			else if (c == '(')
			{
				Token->Type = T_RIGHTBRACKET;
				return Token;
			}
			else if (c == ')')
			{
				Token->Type = T_LEFTBRACKET;
				return Token;
			}
			else
			{
				RemoveString(Token);
				Token->Type = T_ERR;
				return Token;
			}
		}

		case S_Less:
		{
			c = tolower(getchar());

			if (c == '>')
			{
				Token->Type = T_NOTEQUAL;
				return Token;
			}
			else if (c == '=')
			{
				Token->Type = T_LESSEROREQUAL;
				return Token;
			}
			else
			{
				ungetc(c, stdin);
				Token->Type = S_Start;
				break;
			}
		}

		case S_Greater:
		{
			c = tolower(getchar());

			if (c == '=')
			{
				Token->Type = T_GREATEROREQUAL;
				return Token;
			}
			else
			{
				ungetc(c, stdin);
				Token->Type = S_Start;
				break;
			}
		}

		case S_Number:
		{
			c = tolower(getchar());

			if (isblank(c))
			{
				Token->Type = T_INT;
				return Token;
			}
			else if (c == '.')
			{
				AddToString(c, Token);
				state = S_Double; 
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				AddToString(c, Token);
				state = S_Number;
				break;
			}
			else if (c == 'e')
			{
				AddToString(c, Token);
				state = S_Exp;
				break;
			}
			else if ((c >= 'a' && c <= 'z') || c == '_')
			{
				state = S_ID;
				break;
			}
			else 
			{
				ungetc(c, stdin);
				state = S_Start;
				break;
			}
		}

		case S_ID:
		{
			c = tolower(getchar());

			if (isalpha(c) || isdigit(c) || c == '_')
			{
				state = S_ID;
				AddToString(c, Token);
			}
			else
			{
				Token->Type = CompareWithKeywords(Token->String);
				return Token;
			}
		}

		case S_ExcString:
		{
			c = tolower(getchar());

			if (c == '"')
			{
				c = tolower(getchar());
				
				while (c != '"' && c != EOF)
				{
					AddToString(c, Token);
				}

				if (c == '"')
				{
					Token->Type = T_STRING;
					return Token;
				}
				else if (c == EOF)
				{
					Token->Type = T_ERR;
					RemoveString(Token);
					return Token;
				}
			}
			else
			{
				RemoveString(Token);
				Token->Type = T_ERR;
				return Token;
			}

		}

		case S_Dot:
		{
			c = tolower(getchar());

			if (c >= '0' && c <= '9')
			{
				AddToString('0', Token);
				AddToString(c, Token);
				state = S_DotDouble;
			}
			else
			{
				RemoveString(Token);
				Token->Type = T_ERR;
				return Token;
			}
		}

		case S_Double:
		{
			c = tolower(getchar());

			if (c >= '0' && c <= '9')
			{
				AddToString(c, Token);
				break;
			}
			else if ((c >= '*' && c <= '/') || c == '\\' || isblank(c))
			{
				Token->Type = T_DOUBLEVALUE;
				ConvertStringToDouble(Token);
				RemoveString(Token);
				return Token;
			}
		}
		case S_DotDouble:
		{
			c = tolower(getchar());

			if (c >= '0' && c <= '9')
			{
				AddToString(c, Token);
				break;
			}
			else if ((c >= '*' && c <= '/') || c == '\\' || isblank(c))
			{
				Token->Type = T_DOUBLEVALUE;
				ConvertStringToDouble(Token);
				RemoveString(Token);
				return Token;
			}
		}

		case S_Exp:
		{
			c = tolower(getchar());

			if (c == '+' || c == '-')
			{
				state = S_ExpSign;
				AddToString(c, Token);
			}
			else if (c >= 0 && c <= 9)
			{
				AddToString(c, Token);
				break;
			}
			else if ((c >= '*' && c <= '/') || c == '\\')
			{
				Token->Type = T_DOUBLEVALUE;
				ConvertStringToDouble(Token);
				RemoveString(Token);
				ungetc(c, stdin);
				return Token;
			}
			else if (isblank(c))
			{
				Token->Type = T_DOUBLEVALUE;
				ConvertStringToDouble(Token);
				RemoveString(Token);
				ungetc(c, stdin);
				return Token;
			}

		}

		case S_ExpSign:
		{
			c = tolower(getchar());

			if (c >= 0 && c <= 9)
			{
				AddToString(c, Token);
				break;
			}
			else if ((c >= '*' && c <= '/') || c == '\\')
			{
				Token->Type = T_DOUBLEVALUE;
				ConvertStringToDouble(Token);
				RemoveString(Token);
				ungetc(c, stdin);
				return Token;
			}
			else if (isblank(c))
			{
				Token->Type = T_DOUBLEVALUE;
				ConvertStringToDouble(Token);
				RemoveString(Token);
				ungetc(c, stdin);
				return Token;
			}
		}



	}
	}
		
}
