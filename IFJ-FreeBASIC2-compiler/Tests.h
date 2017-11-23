#include <stdio.h>
#include "Basics.h"
#include "TestScanner.h"

void RunTests();
void LoadFileToSTDIN(char* fileName);
void ClearSTDIN();
void Fail(char* message);
void Pass();
void ExampleTests();
void FailedTestExample();

void ReturnTokenTest();

extern char* currentTestName;
