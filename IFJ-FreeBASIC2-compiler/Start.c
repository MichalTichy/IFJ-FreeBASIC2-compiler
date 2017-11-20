#include <stdio.h>
#include "Basics.h"
#define DEBUG 1

#if DEBUG 
#include "Tests.h"
#endif

#if !DEBUG
#include "Scanner.h"
#endif

int main()
{
#if DEBUG 
	RunTests();
#endif

#if !DEBUG
	return 0;
#endif

}