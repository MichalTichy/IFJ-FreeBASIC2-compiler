#include "TokenType.h"

typedef struct {
	TokenType Type;
	int IntVal;
	double DoubleVal;
	char *String;
	int Lenght;
} tToken;

tToken* InitToken(tToken Token);
int InitString(tToken *Token);
int ReallocString(tToken *Token);
void FreeToken(tToken *Token);
