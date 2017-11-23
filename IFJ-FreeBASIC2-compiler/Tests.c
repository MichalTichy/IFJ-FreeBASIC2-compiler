#include "Tests.h"

void RunTests() {
	ExampleTests();

	printf("REAL TESTS\n");
	printf("--------------\n\n");
	
	printf("******* Scanner tests *******\n");
	printf("--------------\n");
	ScannerTests();
	printf("--------------\n");
	ReturnTokenTest();
	printf("--------------\n\n");
	
	ClearSTDIN();
	printf("Press ENTER key to Continue\n");
	getchar();
}

#pragma region Lexical

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
#pragma endregion


#pragma region Examples

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
#pragma endregion

#pragma region HELPERS
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
#pragma endregion




