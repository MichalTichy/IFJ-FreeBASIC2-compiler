#include <TokenType.h>

struct Token {
	TokenType type;
	int intVal;
	double doubleVal;
	char *string;
};