#include "Scanner.h"

//Language IFJ17 contain 35 keywords
#define LenghtOfReservedWords 13

/**
* Reserved words of IFJ17 language
*/

char *ReservedWords[LenghtOfReservedWords] =
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
	Token->String[Token->Lenght - 1] = (char)c;
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
	int AfterDot = 0;

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
			if (c == ' ')
			{
				state = S_Start;
				c = tolower(getchar());
				break;
			}
			else if (c == '\n')
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
				Token = InitString(Token);
				AddToString(c, Token);
				state = S_Number;
				break;
			}
			else if ((c >= 'a' && c <= 'z') || c == '_')
			{
				Token = InitString(Token);
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
				Token = InitString(Token);
				c = tolower(getchar());
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
				Token->Type = T_LESS;
				return Token;
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
				Token->Type = T_LESS;
				return Token;
			}
		}

		case S_Number:
		{
			c = tolower(getchar());

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
			else if ((c >= 'a' && c <= 'z') || c == '_')
			{
				Token->Type = T_ERR;
				RemoveString(Token);
				return Token;
			}
			else
			{
				ungetc(c, stdin);
				Token->Type = T_INTVALUE;
				ConvertStringToInteger(Token);
				return Token;
			}
		}

		case S_ID:
		{
			c = tolower(getchar());

			if (isalpha(c) || isdigit(c) || c == '_')
			{
				state = S_ID;
				AddToString(c, Token);
				break;
			}
			else
			{
				ungetc(c, stdin);
				Token->Type = CompareWithKeywords(Token->String);
				return Token;
			}
		}

		case S_ExcString:
		{
			if (c == '"')
			{
				c = tolower(getchar());
				while (c != '"' && c != EOF)
				{
					AddToString(c, Token);
					c = tolower(getchar());
				}

				if (c == '"')
				{
					Token->Type = T_STRING;
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
			c = tolower(getchar());

			if (c >= '0' && c <= '9')
			{
				AddToString(c, Token);
				AfterDot = 0;
				break;
			}
			else if (c == 'e')
			{
				state = S_Exp;
				AfterDot = 0;
				AddToString(c, Token);
				break;
			}
			else if (((c >= '*' && c <= '/') || c == '\\' || isblank(c) ||
				c == '\n' || c == EOF) && AfterDot == 0)
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
			c = tolower(getchar());

			if ((c == '+' || c == '-') && AfterDot == 0)
			{
				state = S_ExpSign;
				AddToString(c, Token);
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				AddToString(c, Token);
				break;
			}
			else if (((c >= '*' && c <= '/') || c == '\\' || isblank(c) ||
				c == '\n' || c == EOF) && AfterDot == 0)
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
			c = tolower(getchar());

			if (c >= '0' && c <= '9')
			{
				AddToString(c, Token);
				break;
			}
			else if (((c >= '*' && c <= '/') || c == '\\' || isblank(c) ||
				c == '\n' || c == EOF) && AfterDot == 0)
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
			c = tolower(getchar());

			while (c != '\n' && c != EOF)
			{
				c = getchar();
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
			c = tolower(getchar());

			if (c == '\'')
			{
				while (1)
				{
					c = getchar();

					if (c == '\'')
					{
						c = getchar();

						if (c == '/' && c != EOF)
						{
							state = S_Start;
							c = tolower(getchar());
							break;
						}
					}
					else if (c == '/')
					{
						c = getchar();

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
