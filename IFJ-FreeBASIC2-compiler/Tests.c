#include "Tests.h"
char* currentTestName;
void RunTests() {
	ExampleTests();
	printf("REAL TESTS\n");
	IterativeFactorial();
	BasicProgram();

	ClearSTDIN();
	printf("Press ENTER key to Continue\n");
	getchar();
}

#pragma region Lexical
//this test will fail
void IterativeFactorial()
{
	currentTestName = "Iterative factorial";
	LoadFileToSTDIN("../../../TestSamples/iterativeFactorial.txt");
	tToken* token = GetNextToken();
	if (token->Type!=T_SCOPE)
	{
		Fail("Expected token SCOPE");
		return;
	}

	Pass();
}
void BasicProgram()
{
	currentTestName = "Basic program";
	LoadFileToSTDIN("../../../TestSamples/basic.txt");
	tToken* token;

	token = GetNextToken();
	if (token->Type!=T_SCOPE)
	{
		Fail("Expected scope as token 1");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_EOL)
	{
		Fail("Expected EOL as token 2");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_DIM)
	{
		Fail("Expected DIM as token 3");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_ID)
	{
		Fail("Expected ID as token 4");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_AS)
	{
		Fail("Expected AS as token 5");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_INTEGER)
	{
		Fail("Expected INTEGER as token 6");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_EOL)
	{
		Fail("Expected EOL as token 7");
		return;
	}
	
	token = GetNextToken();
	if (token->Type!=T_ID)
	{
		Fail("Expected ID as token 8");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_ASSIGN)
	{
		Fail("Expected ASSIGN as token 9");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_INTVALUE && token->IntVal==3)
	{
		Fail("Expected INTVALUE with value 3 as token 10");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_EOL)
	{
		Fail("Expected EOL as token 11");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_END)
	{
		Fail("Expected END as token 12");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_SCOPE)
	{
		Fail("Expected SCOPE as token 13");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_EOL)
	{
		Fail("Expected EOL as token 14");
		return;
	}

	token = GetNextToken();
	if (token->Type!=T_EOF)
	{
		Fail("Expected EOL as token 15");
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



