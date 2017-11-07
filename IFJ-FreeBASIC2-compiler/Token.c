#include <stdio.h>
#include "Token.h"

static void initToken()
{
	Token.state = Start;
	Token.intVal = 0;
	Token.doubleVal = 0;
	Token.string = NULL;
}
