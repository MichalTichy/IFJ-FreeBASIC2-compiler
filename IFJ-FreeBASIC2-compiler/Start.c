#include <stdio.h>
#include "Basics.h"
#include "ManagedMalloc.h"
#include "Parser.h"
#include "generator.h"
#include "Scanner.h"

#if DEBUG 
#include "Tests.h"
#endif

int main(int argc, char* argv[])
{
	
	#if DEBUG 
		RunTests();
	#endif
	
	#if !DEBUG
		Generate(Parse());
		exitSecurely(OK_ERR);
	#endif
}
	
