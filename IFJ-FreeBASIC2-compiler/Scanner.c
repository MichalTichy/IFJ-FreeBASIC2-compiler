#include <stdio.h>
#include "Token.c"


#define LenghtOfKeyWords 35

/**
* Key words of IFJ17 language
*/

const char *KeyWords[LenghtOfKeyWords] =
{
	"as", "asc", "declare", "dim", "do", "double", "else", "end", "chr",
	"function", "if", "input", "integer", "length", "loop", "print", "return",
	"scope", "string", "substr", "then", "while", "and", "boolean", "continue",
	"elseif", "exit", "false", "for", "next", "not", "or", "shared", "static", "true"
};


void GetNextToken(tToken Token)
{
	tToken* Token = InitToken(Token);

	

	return Token;
}