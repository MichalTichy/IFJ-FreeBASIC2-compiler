#include <stdio.h>
#include "Basics.h"
#include "Start.h"

#if DEBUG 
#include "Tests.h"
#endif

#if !DEBUG
#include "Scanner.h"
#endif

int main(int argc, char* argv[])
{
	
#if DEBUG 
	RunTests();
#endif

#if !DEBUG
	return 0;
#endif

}