#include "Scanner.h"

typedef struct {
	tStates state;
	int intVal;
	double doubleVal;
	char *string;
} tToken;

extern tToken Token;