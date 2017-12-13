/**
*	Project: IFJ17 Compiler
*
*	FILE: tokentype.h
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

#ifndef TOKENTYPE
#define TOKENTYPE
typedef enum {

	T_ID,
	T_EOF,
	T_EOL,
	T_INTVALUE,
	T_DOUBLEVALUE,
	T_STRINGVALUE,
	T_ADD,				// ** +
	T_SUB,				// ** -
	T_MULTIPLY,			// ** *
	T_DIVIDE,			// ** /
	T_INTDIVIDE,		// ** \ result as integer
	T_SEMICOLON,		// ** ;
	T_COLON,			// ** ,
	T_LEFTBRACKET,		// ** (
	T_RIGHTBRACKET,		// ** )
	T_ASSIGN,			// ** =
	T_NOTEQUAL,			// ** <>
	T_LESS,				// ** <
	T_GREATER,			// ** >
	T_GREATEROREQUAL,	// ** >=
	T_LESSEROREQUAL,	// ** <=

	T_AS,				// ** KeyWords
	T_DECLARE,
	T_DIM,
	T_DO,
	T_DOUBLE,
	T_ELSE,
	T_END,
	T_FUNCTION,
	T_IF,
	T_INPUT,
	T_INTEGER,
	T_LOOP,
	T_PRINT,
	T_RETURN,
	T_SCOPE,
	T_STRING,
	T_THEN,
	T_WHILE,
	T_ELSEIF,			
	T_AND,
	T_OR,
	T_NOT,

	T_LexERROR,			//return 1 USED WHEN DEBUG
	T_SyntaxERROR,		//return 2 USED WHEN DEBUG

} TokenType;

#endif
