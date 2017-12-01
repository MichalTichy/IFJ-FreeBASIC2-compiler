#include "Scanner.h"
#include "List.h"
#include "ManagedMalloc.h"

#if DEBUG
#define LEXERROR 1
#endif

#if !DEBUG
#define LEXERROR 0
#endif

//Language IFJ17 contain 35 keywords
#define LenghtOfKeyWords 26
#define LenghtOfReservedWords 9

/**
* Reserved words of IFJ17 language
*/

char *KeyWords[LenghtOfKeyWords] = 
{
	"as", "asc", "declare", "dim", "do", "double", "else", "end", "chr",
	"function", "if", "input", "integer", "lenght", "loop", "print", "return",
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
		TokenList = mmalloc(sizeof(tDLList));
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
		TokenList = mmalloc(sizeof(tDLList));
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
	tState state = S_Start;	//States of finite-state automaton
	char c;					//Input char from stdion
	int AfterDot = 0;		//Help variable when state is after dot
	int AfterExp = 0;		//Help variable when state is after exponent

	//Malloc Token
	if ((Token = (tToken *)mmalloc(sizeof(tToken))) == NULL)
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
			if (isblank(c))
			{
				state = S_Start;
				c = (char) tolower((char) getchar());
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				Token = InitString(Token);
				AddToString(c, Token, Token->Lenght);
				state = S_Number;
				break;
			}
			else if ((c >= 'a' && c <= 'z') || c == '_')
			{
				Token = InitString(Token);
				AddToString(c, Token, Token->Lenght);
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
				AddToString(c, Token, Token->Lenght);
				AfterDot = 1;
				state = S_Double;
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				AddToString(c, Token, Token->Lenght);
				state = S_Number;
				break;
			}
			else if (c == 'e')
			{
				AfterExp = 1;
				state = S_Exp;
				AddToString(c, Token, Token->Lenght);
				break;
			}
			else
			{
				ungetc(c, stdin);
				ConvertStringToInteger(Token);
				return Token;
			}
		}

		case S_ID:
		{
			c = (char) tolower(getchar());

			if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9' || c == '_')
			{
				state = S_ID;
				AddToString(c, Token, Token->Lenght);
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
					else if (c == ' ')
					{
						AddToString('\\', Token, Token->Lenght);
						AddToString('0', Token, Token->Lenght);
						AddToString('3', Token, Token->Lenght);
						AddToString('2', Token, Token->Lenght);
					}
					else
					{
						AddToString(c, Token, Token->Lenght);
					}
					
				}

				if (c == '"')
				{
					Token->Type = T_STRINGVALUE;
					return Token;
				}
				else
				{
					return ScannerError(Token);
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
				AddToString(c, Token, Token->Lenght);
				break;
			}
			else if (c == 'e' && AfterDot == 0)
			{
				AfterExp = 1;
				state = S_Exp;
				AddToString(c, Token, Token->Lenght);
				break;
			}
			else if (AfterDot == 0)
			{
				ungetc(c, stdin);
				ConvertStringToDouble(Token);
				return Token;
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
				AddToString(c, Token, Token->Lenght);
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				AfterExp = 0;
				AddToString(c, Token, Token->Lenght);
				break;
			}
			else if (AfterExp == 0)
			{
				ungetc(c, stdin);
				ConvertStringToDouble(Token);
				return Token;
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
				AddToString(c, Token, Token->Lenght);
				break;
			}
			else if (AfterExp == 0)
			{
				ungetc(c, stdin);
				ConvertStringToDouble(Token);
				return Token;
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

						if (c == '/')
						{
							state = S_Start;
							c = (char) tolower((char) getchar());
							break;
						}
						if (c == EOF)
						{
							return ScannerError(Token);
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
		exitSecurely(LEX_ERR);
	}
	
}

tToken* SyntaxError(tToken *Token)
{
	if (LEXERROR == 1)
	{
		Token->Type = T_SyntaxERROR;
		return Token;
	}
	else
	{
		exitSecurely(SYNTAX_ERR);
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
			return Type = T_SyntaxERROR;
		}
	}

	return Type;
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

int CheckIfEscapeSeuquenceIsValid(char c, tToken *Token)
{
	AddToString('\\', Token, Token->Lenght);
	c = (char)getchar();

	if (c == '0') // 0
	{
		AddToString(c, Token, Token->Lenght);
		c = (char)getchar();

		if (c == '0') // 0 0
		{
			AddToString(c, Token, Token->Lenght);
			c = (char)getchar();

			if (c >= '1' && c <= '9') // 0 0 (1-9)
			{
				AddToString(c, Token, Token->Lenght);
				return 0;
			}
		}
		else if ((c >= '1' && c <= '9')) // 0 (1-9) 
		{
			AddToString(c, Token, Token->Lenght);
			c = (char)getchar();

			if (c >= '0' && c <= '9') // 0 (1-9) (0-9)
			{
				AddToString(c, Token, Token->Lenght);
				return 0;
			}
		}

		return 1;
	}
	if (c == '1') // 1
	{
		AddToString(c, Token, Token->Lenght);
		c = (char)getchar();

		if (c >= '0' && c <= '9') // 1 (0-9)
		{
			AddToString(c, Token, Token->Lenght);
			c = (char)getchar();

			if (c >= '0' && c <= '9') // 1 (0-9) (0-9)
			{
				AddToString(c, Token, Token->Lenght);
				return 0;
			}

		}

		return 1;
	}
	else if (c == '2') // 2
	{
		AddToString(c, Token, Token->Lenght);
		c = (char)getchar();

		if (c >= '0' && c <= '4') // 2 (0-4)
		{
			AddToString(c, Token, Token->Lenght);
			c = (char)getchar();

			if (c >= '0' && c <= '9') // 2 (0-4) (0-9) 
			{
				AddToString(c, Token, Token->Lenght);
				return 0;
			}
		}
		else if (c == '5') // 2 5
		{
			AddToString(c, Token, Token->Lenght);
			c = (char)getchar();

			if (c >= '0' && c <= '5') // 2 5 (0-5)
			{
				AddToString(c, Token, Token->Lenght);
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
			AddToString('0', Token, Token->Lenght);
			AddToString('3', Token, Token->Lenght);
			AddToString('4', Token, Token->Lenght);
		}
		else if (c == 'n')
		{
			AddToString('0', Token, Token->Lenght);
			AddToString('1', Token, Token->Lenght);
			AddToString('0', Token, Token->Lenght);
		}
		else if (c == '\\')
		{
			AddToString('0', Token, Token->Lenght);
			AddToString('9', Token, Token->Lenght);
			AddToString('2', Token, Token->Lenght);
		}
		else if (c == 't')
		{
			AddToString('0', Token, Token->Lenght);
			AddToString('0', Token, Token->Lenght);
			AddToString('9', Token, Token->Lenght);
		}

		return 0;
	}
}
