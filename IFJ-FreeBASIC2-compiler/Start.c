#include <stdio.h>
#include "Basics.h"
#include "Scanner.h"
#include "Tests.h"

#define DEBUG 1
int main()
{
#if DEBUG 
	RunTests();
#endif

#if !DEBUG
	LoadFileToSTDIN("TestSamples\\iterativeFactorial.txt");
	tToken* token = GetNextToken();
	return 0;
#endif

}