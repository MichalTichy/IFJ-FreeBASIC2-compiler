/**
*	Project: IFJ17 Compiler
*
*	FILE: tests.h
*
*	File author:
*	  Michal Tichy, xtichy26
*	  Michal Martinu, xmarti78
*	  Gabriel Mastny, xmastn02
*	  Ondra Deingruber, xdeing00
*
*	Project authors:
*	  Michal Tichy, xtichy26
*	  Michal Martinu, xmarti78
*	  Gabriel Mastny, xmastn02
*	  Ondra Deingruber, xdeing00
*
**/

#include <stdio.h>
#include "Basics.h"

void RunTests();
void LoadFileToSTDIN(char* fileName);
void ClearSTDIN();
void Fail(char* message);
void Pass();
void ExampleTests();
void FailedTestExample();
void PassedTestExample();

void ReturnTokenTest();
void Expression1();
void simplifiedIterativeFactorial();
void ScopeOnly();
void MultipleVarDeclaration();
void VarDeclarationWithAllTypes();
void PrintWithoutSpace();
void Summator();
void TypeMissmatch();
void WhileCycle();
void FunctionDeclarationAndCall();
extern char* currentTestName;
