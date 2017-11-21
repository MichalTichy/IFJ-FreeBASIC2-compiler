﻿#include "Tests.h"
char* currentTestName;
void RunTests() {
	ExampleTests();
	printf("REAL TESTS\n");
	IterativeFactorial();
	BasicProgram();
	ReturnTokenTest();

	ClearSTDIN();
	printf("Press ENTER key to Continue\n");
	getchar();
}

#pragma region Lexical

void IterativeFactorial()
{
	ResetScanner();
	currentTestName = "Iterative factorial";
	LoadFileToSTDIN("../../../TestSamples/iterativeFactorial.txt");
	tToken* token;

	if (Exp_SCOPE())
	{
		Fail("Expected token SCOPE : 1");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 2");
		return;
	}

	if (Exp_DIM())
	{
		Fail("Expected token DIM : 3");
		return;
	}

	if (Exp_ID("a"))
	{
		Fail("Expected token ID : 4");
		return;
	}

	if (Exp_AS())
	{
		Fail("Expected token AS : 5");
		return;
	}

	if (Exp_INTEGER())
	{
		Fail("Expected token INTEGER : 6");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 7");
		return;
	}

	if (Exp_DIM())
	{
		Fail("Expected token DIM : 8");
		return;
	}

	if (Exp_ID("vysl"))
	{
		Fail("Expected token ID : 9");
		return;
	}

	if (Exp_AS())
	{
		Fail("Expected token AS : 10");
		return;
	}

	if (Exp_INTEGER())
	{
		Fail("Expected token INTEGER : 11");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 12");
		return;
	}

	if (Exp_PRINT())
	{
		Fail("Expected token PRINT : 13");
		return;
	}

	if (Exp_STRINGVALUE("Zadejte cislo pro vypocet faktorialu"))
	{
		Fail("Expected token STRING : 14");
		return;
	}

	if (Exp_SEMICOLON())
	{
		Fail("Expected token SEMICOLON : 15");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 16");
		return;
	}

	if (Exp_INPUT())
	{
		Fail("Expected token INPUT : 17");
		return;
	}

	if (Exp_ID("a"))
	{
		Fail("Expected token ID : 18");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 16");
		return;
	}

	if (Exp_IF())
	{
		Fail("Expected token IF : 17");
		return;
	}

	if (Exp_ID("a"))
	{
		Fail("Expected token ID : 19");
		return;
	}

	if (Exp_LESS())
	{
		Fail("Expected token LESS : 20");
		return;
	}

	if (Exp_INTVALUE(0))
	{
		Fail("Expected token INTVALUE : 21");
		return;
	}

	if (Exp_THEN())
	{
		Fail("Expected token THEN : 22");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 23");
		return;
	}

	if (Exp_PRINT())
	{
		Fail("Expected token PRINT : 24");
		return;
	}

	if (Exp_STRINGVALUE("\nFaktorial nelze spocitat\n"))
	{
		Fail("Expected token STRINGVALUE : 25");
		return;
	}

	if (Exp_SEMICOLON())
	{
		Fail("Expected token SEMICOLON : 26");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 27");
		return;
	}

	if (Exp_ELSE())
	{
		Fail("Expected token ELSE : 28");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 29");
		return;
	}

	if (Exp_ID("vysl"))
	{
		Fail("Expected token ID : 30");
		return;
	}

	if (Exp_ASSIGN())
	{
		Fail("Expected token ASSIGN : 31");
		return;
	}

	if (Exp_INTVALUE(1))
	{
		Fail("Expected token INTVALUE : 32");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 33");
		return;
	}

	if (Exp_DO())
	{
		Fail("Expected token EOL : 34");
		return;
	}

	if (Exp_WHILE())
	{
		Fail("Expected token WHILE : 35");
		return;
	}

	if (Exp_ID("a"))
	{
		Fail("Expected token ID : 36");
		return;
	}

	if (Exp_GREATER())
	{
		Fail("Expected token GREATER : 38");
		return;
	}

	if (Exp_INTVALUE(0))
	{
		Fail("Expected token INTVALUE : 39");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 40");
		return;
	}

	if (Exp_ID("vysl"))
	{
		Fail("Expected token ID : 41");
		return;
	}
	
	if (Exp_ASSIGN())
	{
		Fail("Expected token ASSIGN : 42");
		return;
	}
	
	if (Exp_ID("vysl"))
	{
		Fail("Expected token ID : 43");
		return;
	}

	if (Exp_MULTIPLY())
	{
		Fail("Expected token MULTIPLY : 44");
		return;
	}

	if (Exp_ID("a"))
	{
		Fail("Expected token ID : 45");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 46");
		return;
	}

	if (Exp_ID("a"))
	{
		Fail("Expected token ID : 47");
		return;
	}

	if (Exp_ASSIGN())
	{
		Fail("Expected token ASSIGN : 48");
		return;
	}

	if (Exp_ID("a"))
	{
		Fail("Expected token ID : 49");
		return;
	}

	if (Exp_SUB())
	{
		Fail("Expected token SUB : 50");
		return;
	}

	if (Exp_INTVALUE(1))
	{
		Fail("Expected token INTVALUE : 51");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 52");
		return;
	}

	if (Exp_LOOP())
	{
		Fail("Expected token EOL : 53");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 54");
		return;
	}

	if (Exp_PRINT())
	{
		Fail("Expected token PRINT : 55");
		return;
	}

	if (Exp_STRINGVALUE("\nVysledek je:"))
	{
		Fail("Expected token STRINGVALUE : 55");
		return;
	}

	if (Exp_SEMICOLON())
	{
		Fail("Expected token SEMICOLON : 56");
		return;
	}

	if (Exp_ID("vysl"))
	{
		Fail("Expected token STRINGVALUE : 57");
		return;
	}

	if (Exp_SEMICOLON())
	{
		Fail("Expected token SEMICOLON : 58");
		return;
	}

	if (Exp_STRINGVALUE("\n"))
	{
		Fail("Expected token STRINGVALUE : 59");
		return;
	}

	if (Exp_SEMICOLON())
	{
		Fail("Expected token SEMICOLON : 60");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 61");
		return;
	}

	if (Exp_END())
	{
		Fail("Expected token END : 62");
		return;
	}

	if (Exp_IF())
	{
		Fail("Expected token IF : 63");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 64");
		return;
	}

	if (Exp_END())
	{
		Fail("Expected token END : 65");
		return;
	}

	if (Exp_SCOPE())
	{
		Fail("Expected token SCOPE : 66");
		return;
	}

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 67");
		return;
	}

	if (Exp_EOF())
	{
		Fail("Expected token EOF : 68");
		return;
	}

	ClearSTDIN();
	Pass();
}
void BasicProgram()
{
	ResetScanner();
	currentTestName = "Basic program";
	LoadFileToSTDIN("../../../TestSamples/basic.txt");
	tToken* token;

	token = LoadToken();
	if (token->Type!=T_SCOPE)
	{
		Fail("Expected scope as token 1");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_EOL)
	{
		Fail("Expected EOL as token 2");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_DIM)
	{
		Fail("Expected DIM as token 3");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_ID)
	{
		Fail("Expected ID as token 4");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_AS)
	{
		Fail("Expected AS as token 5");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_INTEGER)
	{
		Fail("Expected INTEGER as token 6");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_EOL)
	{
		Fail("Expected EOL as token 7");
		return;
	}
	
	token = LoadToken();
	if (token->Type!=T_ID)
	{
		Fail("Expected ID as token 8");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_ASSIGN)
	{
		Fail("Expected ASSIGN as token 9");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_INTVALUE && token->IntVal==3)
	{
		Fail("Expected INTVALUE with value 3 as token 10");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_EOL)
	{
		Fail("Expected EOL as token 11");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_END)
	{
		Fail("Expected END as token 12");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_SCOPE)
	{
		Fail("Expected SCOPE as token 13");
		return;
	}

	token = LoadToken();
	if (token->Type!=T_EOF)
	{
		Fail("Expected EOF as token 14");
		return;
	}

	Pass();
}

void ReturnTokenTest()
{
	ResetScanner();
	currentTestName = "Return token test";
	LoadFileToSTDIN("../../../TestSamples/basic.txt");
	tToken* token;

	token = LoadToken();
	if (token->Type!=T_SCOPE)
	{
		Fail("Expected scope as token 1");
		return;
	}
	ReturnToken();
	token = LoadToken();
	if (token->Type!=T_SCOPE)
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

#pragma region EXPECT

int Exp_SCOPE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_SCOPE)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_EOL()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_EOL)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_EOF()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_EOF)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_END()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_END)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_DIM()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_DIM)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_AS()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_AS)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_INTEGER()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_INTEGER)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_PRINT()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_PRINT)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_SEMICOLON()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_SEMICOLON)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_INPUT()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_INPUT)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_IF()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_IF)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_ELSE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_ELSE)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_THEN()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_THEN)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_LESS()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_LESS)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_GREATER()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_LESS)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_SUB()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_SUB)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_MULTIPLY()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_MULTIPLY)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_ASSIGN()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_ASSIGN)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_DO()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_DO)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_WHILE()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_WHILE)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_LOOP()
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_LOOP)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_ID(char* expectedString)
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_ID || strcmp(expectedString, token->String))
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}


int Exp_STRINGVALUE(char* expectedString)
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_STRINGVALUE || strcmp(expectedString, token->String))
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}

int Exp_INTVALUE(int expected)
{
	tToken *token;
	token = LoadToken();
	if (token->Type != T_INTVALUE || expected != token->IntVal)
	{
		return -1;
	}
	FreeToken(token);
	return 0;
}



#pragma endregion




