#include <stdio.h>
#include "Token.h"


#define LenghtOfKeyWords 22
#define LenghtOfReservedWords 13

tToken Token;

/**
* Reserved words of IFJ17 language
*/

const char *KeyWords[LenghtOfKeyWords] =
{
	"as", "asc", "declare", "dim", "do", "double", "else", "end", "chr",
	"function", "if", "input", "integer", "length", "loop", "print", "return",
	"scope", "string", "substr", "then", "while"
};

/**
 * Keywords of IFJ17 language
 */

const char *ReservedWords[LenghtOfReservedWords] =
{
	"and", "boolean", "continue", "elseif", "exit", "false", "for", "next",
	"not", "or", "shared", "static", "true"
};



tToken GetNextToken(tToken *Token)
{
	InitToken();

	//return Token;
}