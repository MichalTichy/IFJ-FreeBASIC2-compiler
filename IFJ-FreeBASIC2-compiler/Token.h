#include "TokenState.h"

typedef struct {
	TokenState state;
	int intVal;
	double doubleVal;
	char *string;
} tToken;

extern tToken Token;