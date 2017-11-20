#include "Tests.h"
char* currentTestName;
void RunTests() {
	ExampleTests();
	printf("REAL TESTS");
	

	ClearSTDIN();
	printf("Press ENTER key to Continue\n");
	getchar();
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
	if (a!=b)
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
	if (a!=b)
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
	printf("FAILED  %s : %s █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █ ! █\n",currentTestName,message);
}
void Pass() {
	printf("PASSED %s\n",currentTestName);
}