#include "TokenType.h"

void InitToken();
int InitString();

typedef struct {
	TokenType type;
	int intVal;
	double doubleVal;
	char *string;
	int lenghtOFString;
} tToken;

extern tToken Token;