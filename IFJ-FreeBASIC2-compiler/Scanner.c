#include <stdio.h>
#include <stdlib.h>
#include "Token.h"

//Language IFJ17 contain 35 keywords
#define LenghtOfKeyWords 35

/**
* Key words of IFJ17 language
*/

char *KeyWords[LenghtOfKeyWords] =
{
	"as", "asc", "declare", "dim", "do", "double", "else", "end", "chr",
	"function", "if", "input", "integer", "length", "loop", "print", "return",
	"scope", "string", "substr", "then", "while", "and", "boolean", "continue",
	"elseif", "exit", "false", "for", "next", "not", "or", "shared", "static", "true"
};


/**
 * Function to get next token from source file.
 */

tToken* GetNextToken()
{
	tToken *Token;

	return Token;
}