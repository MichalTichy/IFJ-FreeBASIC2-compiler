#include <stdio.h>
#include "Scanner.h"
#include "Token.c"

//Language IFJ17 contains 35 keywords
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

tToken GetNextToken(FILE *fp)
{
	tToken Token;
	char c;			//Char obtained from getchar()

	while(1)
	{
		fgetc(fp);
	}
	return Token;

}