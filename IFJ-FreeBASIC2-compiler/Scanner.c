#include<stdio.h>
#include "Scanner.h"
#include "Token.h"


#define lenghtOfKeyWords 22
#define lenghtOfReservedWords 13

tToken Token;

/**
* Reserved words of IFJ17 language
*/

const char *keyWords[lenghtOfKeyWords] =
{
	"as", "asc", "declare", "dim", "do", "double", "else", "end", "chr",
	"function", "if", "input", "integer", "length", "loop", "print", "return",
	"scope", "string", "substr", "then", "while"
};

/**
 * Keywords of IFJ17 language
 */

const char *reservedWords[lenghtOfReservedWords] =
{
	"and", "boolean", "continue", "elseif", "exit", "false", "for", "next",
	"not", "or", "shared", "static", "true"
};

