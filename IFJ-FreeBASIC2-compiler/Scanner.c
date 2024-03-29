/**
*	Project: IFJ17 Compiler
*
*	FILE: scanner.c
*		
*	File author:
*	  Michal Martinu, xmarti78
*
*	Project authors:
*	  Michal Tichy, xtichy26
*	  Michal Martinu, xmarti78
*	  Gabriel Mastny, xmastn02
*	  Ondra Deingruber, xdeing00
*   
**/

#include "Scanner.h"
#include "List.h"
#include "ManagedMalloc.h"

/**
*  Used when debuggind mode is turned on for automatic testing
**/

#if DEBUG
#define LEXERROR 1
#endif

#if !DEBUG
#define LEXERROR 0
#endif

//Language IFJ17 contain 35 keywords
#define LenghtOfKeyWords 22
#define LenghtOfReservedWords 9

/**
*  Key words of IFJ17 language
*/

char *KeyWords[LenghtOfKeyWords] = 
{
	"as", "declare", "dim", "do", "double", "else", "end", 
	"function", "if", "input", "integer", "loop", "print", "return",
	"scope", "string", "then", "while", "elseif", "and", "or", "not"
};

/**
*  Reserved words of IFJ17 language
*/

char *ReservedWords[LenghtOfReservedWords] =
{
	"boolean", "continue", "exit", "false", "for", "next",
	"shared", "static", "true"
};


tDLList* TokenList = NULL;

void ResetScanner() {
	TokenList = NULL;
}

/**
*  Function that return token loaded before actual.
*/

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

/**
*  Function that saves next token from source file into list as actual.
*/

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
*  Function to load next token from source file.
*/

tToken* LoadToken()
{
	tToken *Token;
	tState state = S_Start;	//States of finite-state automaton
	char c;					//Input char from stdin
	int AfterDot = 0;		//Help variable when state is after dot
	int AfterExp = 0;		//Help variable when state is after exponent

	//Malloc Token
	if ((Token = (tToken *)mmalloc(sizeof(tToken))) == NULL)
	{  //When mmalloc fails
		exitSecurely(INTERNAL_ERR);
	}

	InitToken(Token);
	Token = InitString(Token);

	while (1)
	{
		switch (state)
		{

		case S_Start:
		{
			c = (char)tolower((char)getchar());

			if (isblank(c))									state = S_Start;
			else if (c >= '0' && c <= '9')					state = S_Number;
			else if ((c >= 'a' && c <= 'z') || c == '_')	state = S_ID;
			else if (c == '=')								state = S_Assign;
			else if (c == '<')								state = S_Less;
			else if (c == '>')								state = S_Greater;
			else if (c == ';')								state = S_Semicolon;
			else if (c == ',')								state = S_Colon;
			else if (c == '+')								state = S_Add;
			else if (c == '-')								state = S_Sub;
			else if (c == '*')								state = S_Multiply;
			else if (c == '/')								state = S_BlockcommentOrDivide;	
			else if (c == '\\')								state = S_Intdivide;
			else if (c == '!')								state = S_ExcString;
			else if (c == '(')								state = S_LeftBracket;
			else if (c == ')')								state = S_RightBracket;
			else if (c == '\'')								state = S_Comment;
			else if (CheckEOL(c))							state = S_EOL;
			else if (c == EOF)								state = S_EOF;
			else if (c == '&')								state = S_Base;
			else
			{
				return ScannerError(Token);
			}

			break;
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
				c = (char)tolower((char)getchar());
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
				ConvertStringToInteger(Token, 10);
				return Token;
			}
		}

		case S_ID:
		{
			if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
			{
				state = S_ID;
				AddToString(c, Token, Token->Lenght);
				c = (char)tolower(getchar());
				break;
			}
			else
			{
				ungetc(c, stdin);
				Token->Type = CompareWithKeywords(Token->String);
				
				if (Token->Type == T_SyntaxERROR)
				{
					return SyntaxError(Token);
				}
				
				return Token;
			}
		}

		case S_ExcString:
		{
			c = (char)tolower((char)getchar());

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
						if (CheckIfEscapeSeuquenceIsValid(c, Token))
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
						AddEscapeSequenceToString('0', '3', '2', Token, Token->Lenght);
					}
					else if (c > (char) 31)
					{
						AddToString(c, Token, Token->Lenght);
					}
					else
					{
						return ScannerError(Token);
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
				if (BlockCommentClear(Token))
				{
					state = S_Start;
					break;
				}
				else
				{
					return ScannerError(Token);
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

		case S_Base:
		{
			c = (char)tolower(getchar());

			if (c == 'b')
			{
				state = S_BINARY;
				break;
			}
			else if (c == 'o')
			{
				state = S_OCTANE;
				break;
			}
			else if (c == 'h')
			{
				state = S_HEXA;
				break;
			}
			else
			{
				return ScannerError(Token);
			}
		}

		case S_BINARY:
		{
			c = (char)getchar();

			if (c == '0' || c == '1')
			{
				AddToString(c, Token, Token->Lenght);
				break;
			}
			else
			{
				ungetc(c, stdin);
				ConvertStringToInteger(Token, 2);
				return ReturnStateType(Token, T_INTVALUE);
			}
		}

		case S_OCTANE:
		{
			c = (char)getchar();

			if (c >= '0' && c <= '7')
			{
				AddToString(c, Token, Token->Lenght);
				break;
			}
			else
			{
				ungetc(c, stdin);
				ConvertStringToInteger(Token, 8);
				return ReturnStateType(Token, T_INTVALUE);
			}
		}

		case S_HEXA:
		{
			c = (char)tolower(getchar());

			if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))
			{
				AddToString(c, Token, Token->Lenght);
				break;
			}
			else
			{
				ungetc(c, stdin);
				ConvertStringToInteger(Token, 16);
				return ReturnStateType(Token, T_INTVALUE);
			}
		}

		case S_Assign:			return ReturnStateType(Token, T_ASSIGN);
		case S_Semicolon:		return ReturnStateType(Token, T_SEMICOLON);
		case S_Colon:			return ReturnStateType(Token, T_COLON);
		case S_Add:				return ReturnStateType(Token, T_ADD);
		case S_Sub:				return ReturnStateType(Token, T_SUB);
		case S_Multiply:		return ReturnStateType(Token, T_MULTIPLY);
		case S_Intdivide:		return ReturnStateType(Token, T_INTDIVIDE);
		case S_LeftBracket:		return ReturnStateType(Token, T_LEFTBRACKET);
		case S_RightBracket:	return ReturnStateType(Token, T_RIGHTBRACKET);
		case S_EOL:				return ReturnStateType(Token, T_EOL);
		case S_EOF:				return ReturnStateType(Token, T_EOF);
		
		} //End Switch
	} //End while

}

/**
*  Function used when there is lexical error in scanner.
*/

tToken* ScannerError(tToken *Token)
{
	if (LEXERROR == 1)
	{   //When debugging mode is turned on, don�t exit
		Token->Type = T_LexERROR;
		return Token;
	}
	else
	{   //Exit securely when error in scanner is occured
		exitSecurely(LEX_ERR);
	}
	
}

/**
*  Function throw syntax error when identificator is reserved word.
*/

tToken* SyntaxError(tToken *Token)
{
	if (LEXERROR == 1)
	{   //When debugging mode is turned on, don�t exit
		Token->Type = T_SyntaxERROR;
		return Token;
	}
	else
	{   //Exit securely when error in scanner is occured
		exitSecurely(SYNTAX_ERR);
	}

}

/**
*  Function for changing type of token.
*/

tToken *ReturnStateType(tToken *Token, TokenType mType)
{
	Token->Type = mType;
	return Token;
}

/**
*  Function used when block comment needs to be cleared.
*  When some error will occur return 0, else return 1.
*/

int BlockCommentClear(tToken *Token)
{
	char c;

	while (1)
	{
		c = (char)getchar();

		if (c == '\'')
		{
			c = (char)getchar();

			if (c == '/')
			{
				return 1;
			}
			if (c == EOF)
			{
				return 0;
			}
		}
		else if (c == '/')
		{
			c = (char)getchar();

			if (c == '\'' || c == EOF)
			{
				return 0;
			}

		}
		if (c == EOF)
		{
			return 0;
		}
	}
}


/**
*  Function for commparing indetificator with key words or reserved words.
*  When input is reserved word return syntax error.
*/

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

/**
*  Function check if there is EOL, it is compatibile with windows new line.
*  When EOL is found return 1, else return 0.
*/

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


/**
*  Function to check valid escape sequence in string.
*  When escape sequence is valid return 0, else return 1.
*/

int CheckIfEscapeSeuquenceIsValid(char c, tToken *Token)
{
	char escapeSequenceValue[4];
	int tmp;
	
	AddToString('\\', Token, Token->Lenght);
	c = (char)getchar();


	if (c >= '0' && c <= '2')
	{
		AddToString(c, Token, Token->Lenght);
		escapeSequenceValue[0] = c;

		for (int i = 1; i <= 2; i++)
		{
			c = (char)getchar();

			if (c >= '0' && c <= '9')
			{
				AddToString(c, Token, Token->Lenght);
				escapeSequenceValue[i] = c;
			}
			else
			{
				return 1;
			}
		}

		tmp = strtol(escapeSequenceValue, NULL, 10);

		if (tmp >= 1 && tmp <= 255)
		{
			return 0;
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
			AddEscapeSequenceToString('0', '3', '4', Token, Token->Lenght);
		}
		else if (c == 'n')
		{
			AddEscapeSequenceToString('0', '1', '0', Token, Token->Lenght);
		}
		else if (c == '\\')
		{
			AddEscapeSequenceToString('0', '9', '2', Token, Token->Lenght);
		}
		else if (c == 't')
		{
			AddEscapeSequenceToString('0', '0', '9', Token, Token->Lenght);
		}

		return 0;
	} 
} 

/**
*  Function for adding numbers of escape sequence into string, individually.
*/

void AddEscapeSequenceToString(char val_1, char val_2, char val_3, tToken* Token, int Lenght)
{
	AddToString(val_1, Token, Lenght);
	AddToString(val_2, Token, Lenght);
	AddToString(val_3, Token, Lenght);
}
