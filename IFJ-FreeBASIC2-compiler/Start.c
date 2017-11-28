#include <stdio.h>
#include "Basics.h"

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
	printf("HAHA");
	getchar();
	return 0;
#endif

}