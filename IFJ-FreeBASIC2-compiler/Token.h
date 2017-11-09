#include "TokenType.h"

tToken* InitToken();
int InitString(tToken *Token);
int ReallocString(tToken *Token);
void FreeToken(tToken *Token);

typedef struct {
	TokenType Type;
	int IntVal;
	double DoubleVal;
	char *String;
	int Lenght;
} tToken;

