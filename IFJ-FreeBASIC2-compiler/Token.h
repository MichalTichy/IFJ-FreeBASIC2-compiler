#include "TokenType.h"

void InitToken();
int InitString();
int ReallocString();
void FreeString();

typedef struct {
	TokenType Type;
	int IntVal;
	double DoubleVal;
	char *String;
	int Lenght;
} tToken;

//Global variable between all files
extern tToken Token;