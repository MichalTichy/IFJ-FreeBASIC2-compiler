
#include "Tests.h"
#include "TestScanner.h"
#include "TestStack.h"
#include "TestSymTable.h"
#include "Parser.h"

void RunTests() {
	ExampleTests();

	printf("REAL TESTS\n");
	printf("--------------\n\n");
	
	printf("******* Scanner tests *******\n");
	printf("--------------\n");
	ScannerTests();
	printf("--------------\n");
	ReturnTokenTest();
	printf("******* Parser tests *******\n");
	printf("--------------\n");
	Expression1();
	printf("--------------\n");
	ReturnTokenTest();
	printf("******* Stack tests *******\n\n");
	StackAllTests();
	printf("--------------\n");
	printf("******* Symbol Table tests *******\n");
	AllSymTableTests();
	printf("--------------\n");

	ClearSTDIN();
	printf("Press ENTER key to Continue\n");
	getchar();
}

void ReturnTokenTest()
{
	ResetScanner();
	currentTestName = "Return token test";
	LoadFileToSTDIN("../../../TestSamples/basic.txt");
	tToken* token;

	token = GetNextToken();
	if (token->Type != T_SCOPE)
	{
		Fail("Expected scope as token 1");
		return;
	}
	ReturnToken();
	token = GetNextToken();
	if (token->Type != T_SCOPE)
	{
		Fail("Expected scope as token 1");
		return;
	}

	Pass();
}

void Expression1()
{
	ResetScanner();
	currentTestName = "5*2+3";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/Expression1.txt");
	Next();
	tNode* result = ProcessRelationalExpression();

	if (result->type!=binaryExpression)
	{
		Fail("Root node should be binary expression");
		return;
	}

	if (result->tData.binaryExpression->OP!=T_ADD)
	{
		Fail("Root node operator should be ADD");
		return;
	}

	if (result->tData.binaryExpression->left->type!=binaryExpression)
	{
		Fail("Roots left node should be binary expression");
		return;
	}

	if (result->tData.binaryExpression->left->tData.binaryExpression->OP!=T_MULTIPLY)
	{
		Fail("left nodes OP should be multiplication");
		return;
	}
	if (result->tData.binaryExpression->left->tData.binaryExpression->left->type!=integerVal && result->tData.binaryExpression->left->tData.binaryExpression->left->tData.intValue->value==5)
	{
		Fail("left nodes left node should be INT value with value 5");
		return;
	}
	if (result->tData.binaryExpression->left->tData.binaryExpression->right->type!=integerVal && result->tData.binaryExpression->left->tData.binaryExpression->right->tData.intValue->value == 2)
	{
		Fail("left nodes right node should be INT value with value 2");
		return;
	}
	if (result->tData.binaryExpression->right->type != integerVal && result->tData.binaryExpression->right->tData.intValue->value==3)
	{
		Fail("Roots right node should be int value with value 3");
		return;
	}
	Pass();
}



void ExampleTests()
{
	printf("EXAMPLE TESTS");
	printf("\n");
	PassedTestExample();
	FailedTestExample();

	printf("\n");
	printf("\n");
	printf("\n");
}

//this test will fail
void FailedTestExample() {
	currentTestName = "Failed Test example";

	int a = 5;
	int b = 6;
	if (a != b)
	{
		Fail("a should equal b");
	}
	else
	{
		Pass();
	}
}

//this test will pass
void PassedTestExample() {
	currentTestName = "Passed Test example";

	int a = 6;
	int b = 6;
	if (a != b)
	{
		Fail("a should equal b");
	}
	else
	{
		Pass();
	}

}

void LoadFileToSTDIN(char* fileName)
{
	freopen(fileName, "r", stdin);
}

void ClearSTDIN() {
	fseek(stdin, 0, SEEK_END);
}

void Fail(char* message) {
	printf("FAILED  %s : %s █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █\n", currentTestName, message);
}
void Pass() {
	printf("PASSED %s\n", currentTestName);
}





