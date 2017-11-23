#include "Scanner.h"

//Language IFJ17 contain 35 keywords
#define LenghtOfReservedWords 12

/**
* Reserved words of IFJ17 language
*/

char *ReservedWords[LenghtOfReservedWords] =
{
	"and", "boolean", "continue", "exit", "false",
	"for", "next", "not", "or", "shared", "static", "true"
};


// Used for realloc
long unsigned int LenghtOfString = 10;
tDLList* TokenList = NULL;

void ResetScanner() {
	TokenList = NULL;
}
void ReturnToken() {
	if (TokenList == NULL)
	{
		TokenList = malloc(sizeof(tDLList));
		DLInitList(TokenList);
	}
	DLPred(TokenList);
}
tToken* GetNextToken() {
	if (TokenList == NULL)
	{
		TokenList = malloc(sizeof(tDLList));
		DLInitList(TokenList);
	}

	if (DLIsEmpty(TokenList))
	{
		DLInsertFirst(TokenList, LoadToken());
		DLFirst(TokenList);
	}
	else if (!DLActive(TokenList)) {
		DLFirst(TokenList);
	}
	else if (DLIsActiveItemLast(TokenList))
	{
		DLInsertLast(TokenList, LoadToken());
		DLLast(TokenList);
	}
	else
	{
		DLNext(TokenList);
	}

	return TokenList->Act->data;
}

/**
* Operations with strings
*/

void AddToString(char c, tToken *Token)
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

	if (!strcmp(string, "as")) Type = T_AS;
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
	else if (!strcmp(string, "elseif")) Type = T_ELSEIF;
	else
	{
		for (int i = 0; i < LenghtOfReservedWords; i++)
		{
			Type = T_ID;

			if (!strcmp(string, ReservedWords[i]))
			{
				Type = T_ERR;
				break;
			}
		}
	}

	return Type;
}

int CheckEOL(char c)
{
	if (c == '\n')
	{
		return 1;
	}
	else if (c == '\r')
	{
		c = (char) getchar();

		if (c != '\n')
		{
			ungetc(c, stdin);
		}
			return 1;
	}
	else
	{
		return 0;
	}
}

int CheckIfMathSymbol(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' ||
		c == '\\' || c == '=')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int CheckIfEscapeSeuquenceIsValid(char c, tToken *Token)
{
	AddToString('\\', Token);
	c = (char) getchar();

	if (c >= '0' && c <= '1')
	{
		AddToString(c, Token);
		c = (char) getchar();

		if (c >= '0' && c <= '9')
		{
			AddToString(c, Token);
			c = (char) getchar();

			if (c >= '0' && c <= '9')
			{
				AddToString(c, Token);
				return 0;
			}

		}

		return 1;

	}
	else if (c == '2')
	{
		AddToString(c, Token);
		c = (char) getchar();

		if (c >= '0' && c <= '5')
		{
			AddToString(c, Token);
			c = (char) getchar();

			if (c >= '0' && c <= '5')
			{
				AddToString(c, Token);
				return 0;
			}
		}

		return 1;

	}
	else if (c != '\"' && c != 'n' && c != 't' && c != '\\')
	{
		return 1;
	}
	else
	{
		if (c == '\"')
		{
			AddToString('\"', Token);
		}
		else if (c == 'n')
		{
			AddToString('n', Token);
		}
		else if (c == '\\')
		{
			AddToString('\\', Token);
		}
		else if (c == 't')
		{
			AddToString('t', Token);
		}
		
		return 0;
	}
}


/**
* Function to get next token from source file.
*/
tToken* LoadToken()
{
	tToken *Token;
	tState state = S_Start;
	char c;
	int AfterDot = 0;
	int AfterExp = 0;

	//Malloc Token
	if ((Token = (tToken *)malloc(sizeof(tToken))) == NULL)
	{
		Token = NULL;
	}

	InitToken(Token);

	c = (char) tolower((char) getchar());

	while (1)
	{

		switch (state)
		{
		case S_Start:
		{
			if (c == ' ')
			{
				state = S_Start;
				c = (char) tolower((char) getchar());
				break;
			}
			else if (CheckEOL(c) == 1)
			{
				Token->Type = T_EOL;
				return Token;
			}
			else if (c == EOF)
			{
				Token->Type = T_EOF;
				return Token;
			}
			else if (c >= '0' && c <= '9')
			{
				Token = InitString(Token, LenghtOfString);
				AddToString(c, Token);
				state = S_Number;
				break;
			}
			else if ((c >= 'a' && c <= 'z') || c == '_')
			{
				Token = InitString(Token, LenghtOfString);
				AddToString(c, Token);
				state = S_ID;
				break;
			}
			else if (c == '=')
			{
				Token->Type = T_ASSIGN;
				return Token;
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
				state = S_BlockcommentOrDivide;
				break;
			}
			else if (c == '\\')
			{
				Token->Type = T_INTDIVIDE;
				return Token;
			}
			else if (c == '!')
			{
				Token = InitString(Token, LenghtOfString);
				c = (char) tolower((char) getchar());
				state = S_ExcString;
				break;
			}
			else if (c == '(')
			{
				Token->Type = T_LEFTBRACKET;
				return Token;
			}
			else if (c == ')')
			{
				Token->Type = T_RIGHTBRACKET;
				return Token;
			}
			else if (c == '\'')
			{
				state = S_Comment;
				break;
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
			c = (char) tolower((char) getchar());

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
				Token->Type = T_LESS;
				return Token;
			}
		}

		case S_Greater:
		{
			c = (char) tolower((char) getchar());

			if (c == '=')
			{
				Token->Type = T_GREATEROREQUAL;
				return Token;
			}
			else
			{
				ungetc(c, stdin);
				Token->Type = T_GREATER;
				return Token;
			}
		}

		case S_Number:
		{
			c = (char) tolower((char) getchar());

			if (c == '.')
			{
				AddToString(c, Token);
				AfterDot = 1;
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
				AfterExp = 1;
				state = S_Exp;
				AddToString(c, Token);
				break;
			}
			else if (CheckIfMathSymbol(c) == 1 || isblank(c) ||
				CheckEOL(c) == 1 || c == EOF)
			{
				ungetc(c, stdin);
				Token->Type = T_INTVALUE;
				ConvertStringToInteger(Token);
				return Token;
			}
			else
			{
				Token->Type = T_ERR;
				RemoveString(Token);
				return Token;
			}
		}

		case S_ID:
		{
			c = (char) tolower(getchar());

			if (isalpha(c) || isdigit(c) || c == '_')
			{
				state = S_ID;
				AddToString(c, Token);
				break;
			}
			else if (CheckIfMathSymbol(c) == 1 || isblank(c) || c == '\n' ||
				c == '\r' || c == EOF)
			{
				ungetc(c, stdin);
				Token->Type = CompareWithKeywords(Token->String);
				return Token;
			}
			else
			{
				Token->Type = T_ERR;
				RemoveString(Token);
				return Token;
			}
		}

		case S_ExcString:
		{
			if (c == '"')
			{
				
				while (c != EOF)
				{
					c = (char) getchar();

					if (CheckEOL(c) == 1)
					{
						RemoveString(Token);
						Token->Type = T_ERR;
						return Token;
					}
					else if (c == '\\')
					{
						if (CheckIfEscapeSeuquenceIsValid(c, Token) == 1)
						{
							RemoveString(Token);
							Token->Type = T_ERR;
							return Token;
						}
					}
					else if (c == '"')
					{
						break;
					}
					else
					{
						AddToString(c, Token);
					}
					
				}

				if (c == '"')
				{
					Token->Type = T_STRINGVALUE;
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

		case S_Double:
		{
			c = (char) tolower(getchar());

			if (c >= '0' && c <= '9')
			{
				AfterDot = 0;
				AddToString(c, Token);
				break;
			}
			else if (c == 'e' && AfterDot == 0)
			{
				AfterExp = 1;
				state = S_Exp;
				AddToString(c, Token);
				break;
			}
			else if ((CheckIfMathSymbol(c) == 1 || isblank(c) || c == '\n' ||
				c == '\r' || c == EOF) && AfterDot == 0)
			{
				Token->Type = T_DOUBLEVALUE;
				ConvertStringToDouble(Token);
				RemoveString(Token);
				ungetc(c, stdin);
				return Token;
			}
			else
			{
				Token->Type = T_ERR;
				RemoveString(Token);
				return Token;
			}
		}

		case S_Exp:
		{
			c = (char) tolower(getchar());

			if (c == '+' || c == '-')
			{
				state = S_ExpSign;
				AddToString(c, Token);
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				AfterExp = 0;
				AddToString(c, Token);
				break;
			}
			else if ((CheckIfMathSymbol(c) ==1 || isblank(c) || c == '\n' ||
				c == '\r' || c == EOF) && AfterExp == 0)
			{
				Token->Type = T_DOUBLEVALUE;
				ConvertStringToDouble(Token);
				RemoveString(Token);
				ungetc(c, stdin);
				return Token;
			}
			else
			{
				Token->Type = T_ERR;
				RemoveString(Token);
				return Token;
			}
		}

		case S_ExpSign:
		{
			c = (char) tolower(getchar());

			if (c >= '0' && c <= '9')
			{
				AfterExp = 0;
				AddToString(c, Token);
				break;
			}
			else if (((c >= '*' && c <= '/') || c == '\\' || c == '=' || isblank(c) || c == '\n' ||
				c == '\r' || c == EOF) && AfterExp == 0)
			{
				Token->Type = T_DOUBLEVALUE;
				ConvertStringToDouble(Token);
				RemoveString(Token);
				ungetc(c, stdin);
				return Token;
			}
			else
			{
				Token->Type = T_ERR;
				RemoveString(Token);
				return Token;
			}
		}

		case S_Comment:
		{
			c = (char) tolower(getchar());

			while (c != '\n' && c != EOF)
			{
				c = (char) getchar();
			}

			if (c == '\n')
			{
				Token->Type = T_EOL;
				return Token;
			}
			else
			{
				Token->Type = T_EOF;
				return Token;
			}
		}

		case S_BlockcommentOrDivide:
		{
			c = (char) tolower(getchar());

			if (c == '\'')
			{
				while (1)
				{
					c = (char) getchar();

					if (c == '\'')
					{
						c = (char) getchar();

						if (c == '/' && c != EOF)
						{
							state = S_Start;
							c = (char) tolower((char) getchar());
							break;
						}
					}
					else if (c == '/')
					{
						c = (char) getchar();

						if (c == '\'' || c == EOF)
						{
							Token->Type = T_ERR;
							RemoveString(Token);
							return Token;
						}

					}

					if (c == EOF)
					{
						Token->Type = T_ERR;
						RemoveString(Token);
						return Token;
					}
				}
			}
			else
			{
				ungetc(c, stdin);
				Token->Type = T_DIVIDE;
				return Token;
			}

			break;
		}
		}
	}

}