#include <stdio.h>
#include "Basics.h"
#include "ManagedMalloc.h"
#include "Parser.h"
#include "generator.h"
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
#endif
	Generate(Parse());
	exitSecurely(OK_ERR);
}