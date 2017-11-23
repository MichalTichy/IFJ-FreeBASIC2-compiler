#include <stdio.h>
#include "Basics.h"
#include "TestScanner.h"
#include "TestStack.h"

void RunTests();
void LoadFileToSTDIN(char* fileName);
void ClearSTDIN();
void Fail(char* message);
void Pass();

extern char* currentTestName;
