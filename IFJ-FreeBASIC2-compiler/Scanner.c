#include "Scanner.h"
#include "string.h"
#include "Start.h"

#if DEBUG
#define LEXERROR 1
#endif

#if !DEBUG
#define LEXERROR 0
#endif

//Language IFJ17 contain 35 keywords
#define LenghtOfKeyWords 26
#define LenghtOfReservedWords 9

long unsigned int *LenghtOfString = 10;


/**
* Reserved words of IFJ17 language
*/

char *KeyWords[LenghtOfKeyWords] = 
{
	"as", "asc", "declare", "dim", "do", "double", "else", "end", "chr",
	"function", "if", "input", "integer", "length", "loop", "print", "return",
	"scope", "string", "substr", "then", "while", "elseif", "and", "or", "not"
};

char *ReservedWords[LenghtOfReservedWords] =
{
	"boolean", "continue", "exit", "false", "for", "next",
	"shared", "static", "true"
};


tDLList* TokenList = NULL;

void ResetScanner() {
	TokenList = NULL;
}

tToken* ReturnToken() {
	if (TokenList == NULL)
	{
		TokenList = malloc(sizeof(tDLList));
		DLInitList(TokenList);
	}
	DLPred(TokenList);
	if (TokenList->Act!=NULL)
	{
		return TokenList->Act->data;
	}
	return NULL;
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
				AddToString(c, Token, LenghtOfString);
				state = S_Number;
				break;
			}
			else if ((c >= 'a' && c <= 'z') || c == '_')
			{
				Token = InitString(Token, LenghtOfString);
				AddToString(c, Token, LenghtOfString);
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
				return ScannerError(Token);
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
				AddToString(c, Token, LenghtOfString);
				AfterDot = 1;
				state = S_Double;
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				AddToString(c, Token, LenghtOfString);
				state = S_Number;
				break;
			}
			else if (c == 'e')
			{
				AfterExp = 1;
				state = S_Exp;
				AddToString(c, Token, LenghtOfString);
				break;
			}
			else
			{
				ungetc(c, stdin);
				return ConvertStringToInteger(Token);
			}
		}

		case S_ID:
		{
			c = (char) tolower(getchar());

			if (isalpha(c) || isdigit(c) || c == '_')
			{
				state = S_ID;
				AddToString(c, Token, LenghtOfString);
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
				return ScannerError(Token);
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
						return ScannerError(Token);
					}
					else if (c == '\\')
					{
						if (CheckIfEscapeSeuquenceIsValid(c, Token) == 1)
						{
							return ScannerError(Token);
						}
					}
					else if (c == '"')
					{
						break;
					}
					else
					{
						AddToString(c, Token, LenghtOfString);
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
				return ScannerError(Token);
			}

		}

		case S_Double:
		{
			c = (char) tolower(getchar());

			if (c >= '0' && c <= '9')
			{
				AfterDot = 0;
				AddToString(c, Token, LenghtOfString);
				break;
			}
			else if (c == 'e' && AfterDot == 0)
			{
				AfterExp = 1;
				state = S_Exp;
				AddToString(c, Token, LenghtOfString);
				break;
			}
			else if ((CheckIfMathSymbol(c) == 1 || isblank(c) || c == '\n' ||
				c == '\r' || c == EOF) && AfterDot == 0)
			{
				ungetc(c, stdin);
				return ConvertStringToDouble(Token);
			}
			else
			{
				return ScannerError(Token);
			}
		}

		case S_Exp:
		{
			c = (char) tolower(getchar());

			if (c == '+' || c == '-')
			{
				state = S_ExpSign;
				AddToString(c, Token, LenghtOfString);
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				AfterExp = 0;
				AddToString(c, Token, LenghtOfString);
				break;
			}
			else if ((CheckIfMathSymbol(c) ==1 || isblank(c) || c == '\n' ||
				c == '\r' || c == EOF) && AfterExp == 0)
			{
				ungetc(c, stdin);
				return ConvertStringToDouble(Token);
			}
			else
			{
				return ScannerError(Token);
			}
		}

		case S_ExpSign:
		{
			c = (char) tolower(getchar());

			if (c >= '0' && c <= '9')
			{
				AfterExp = 0;
				AddToString(c, Token, LenghtOfString);
				break;
			}
			else if ((CheckIfMathSymbol(c) == 1 || isblank(c) || c == '\n' ||
				c == '\r' || c == EOF) && AfterExp == 0)
			{
				ungetc(c, stdin);
				return ConvertStringToDouble(Token);
			}
			else
			{
				return ScannerError(Token);
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
							return ScannerError(Token);
						}

					}
					if (c == EOF)
					{
						return ScannerError(Token);
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

tToken* ScannerError(tToken *Token)
{
	if (LEXERROR == 1)
	{
		Token->Type = T_LexERROR;
		return Token;
	}
	else
	{
		mfreeall();
		exit(1);
	}
	
}

TokenType CompareWithKeywords(char* string)
{
	TokenType Type;
	Type = T_ID;

	for (int i = 0; i < LenghtOfKeyWords; i++)
	{
		if (!strcmp(string, KeyWords[i]))
		{
			Type = i + 21;
			return Type;
		}
	}


	for (int i = 0; i < LenghtOfReservedWords; i++)
	{
		if (!strcmp(string, ReservedWords[i]))
		{
			return Type = T_LexERROR;
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
		c = (char)getchar();

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
	AddToString('\\', Token, LenghtOfString);
	c = (char)getchar();

	if (c >= '0' && c <= '1')
	{
		AddToString(c, Token, LenghtOfString);
		c = (char)getchar();

		if (c >= '0' && c <= '9')
		{
			AddToString(c, Token, LenghtOfString);
			c = (char)getchar();

			if (c >= '0' && c <= '9')
			{
				AddToString(c, Token, LenghtOfString);
				return 0;
			}

		}

		return 1;

	}
	else if (c == '2')
	{
		AddToString(c, Token, LenghtOfString);
		c = (char)getchar();

		if (c >= '0' && c <= '5')
		{
			AddToString(c, Token, LenghtOfString);
			c = (char)getchar();

			if (c >= '0' && c <= '5')
			{
				AddToString(c, Token, LenghtOfString);
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
			AddToString('\"', Token, LenghtOfString);
		}
		else if (c == 'n')
		{
			AddToString('n', Token, LenghtOfString);
		}
		else if (c == '\\')
		{
			AddToString('\\', Token, LenghtOfString);
		}
		else if (c == 't')
		{
			AddToString('t', Token, LenghtOfString);
		}

		return 0;
	}
}
