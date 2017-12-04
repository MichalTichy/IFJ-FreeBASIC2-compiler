
#include "Tests.h"
#include "TestScanner.h"
#include "TestStack.h"
#include "TestSymTable.h"
#include "Parser.h"
#include "ManagedMalloc.h"
#include "generator.h"

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
	Expression1();
	ReturnTokenTest();
	printf("--------------\n");
	simplifiedIterativeFactorial();
	printf("--------------\n");
	ScopeOnly();
	MultipleVarDeclaration();
	VarDeclarationWithAllTypes();
	PrintWithoutSpace();
	Summator();
	TypeMissmatch();
	FunctionDeclaration();
	printf("******* Stack tests *******\n\n");
	StackAllTests();
	printf("--------------\n");
	printf("******* Symbol Table tests *******\n");
	AllSymTableTests();
	printf("--------------\n");

	mfreeall();

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

void simplifiedIterativeFactorial()
{
	ResetScanner();
	currentTestName = "simplifiedIterativeFactorial";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/simplifiedIterativeFactorial.txt");
	tProgram* result = Parse();
	Generate(result);

	Pass();
}

void Summator()
{
	ResetScanner();
	currentTestName = "Summator";
	lastError = OK_ERR;
	LoadFileToSTDIN("../../../TestSamples/ParserTests/Summator.txt");
	tProgram* result = Parse();
	if (lastError != 0)
	{
		Fail("Error detected");
	}
	if (result->Main == NULL)
	{
		Fail("Main failed to parse.");
	}
	if (result->Main->type != scope || result->Main->tData.scope == NULL)
	{
		Fail("Scope failed to parse");
	}
	if (result->Main->tData.scope->Statement->Next->Next->Next->Next->Next->Next->Next->type==varAssigment)
	{
		Fail("Last statement is not assigment");
	}
	Pass();
}
void Expression1()
{
	ResetScanner();
	currentTestName = "5*2+3";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/Expression1.txt");
	Next();
	struct tSTScope* scope;
	STMakeScope(&scope, NULL);
	tNode* result = ProcessRelationalExpression(scope);

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

void ScopeOnly()
{
	ResetScanner();
	lastError = NULL;
	currentTestName = "ScopeOnly";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/ScopeOnly.txt");
	tProgram* result = Parse();
	if (lastError!=0)
	{
		Fail("Error detected");
	}
	if (result->Main->type!=scope || result->Main->tData.scope==NULL)
	{
		Fail("Scope failed to parse");
	}
	if (result->Main->tData.scope->Statement->type!=empty)
	{
		Fail("Scope statement should be empty");
	}
	Pass();
}

void MultipleVarDeclaration()
{
	ResetScanner();
	lastError = NULL;
	currentTestName = "MultipleVarDeclaration";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/MultipleVarDeclaration.txt");
	tProgram* result = Parse();
	if (lastError!=0)
	{
		Fail("Error detected");
	}
	if (result->Main==NULL)
	{
		Fail("Main failed to parse.");
	}
	if (result->Main->type!=scope || result->Main->tData.scope==NULL)
	{
		Fail("Scope failed to parse");
	}
	if (result->Main->tData.scope->Statement->type!=varDeclaration)
	{
		Fail("First var declaration is missing");
	}
	if (result->Main->tData.scope->Statement->Next->type!=varDeclaration)
	{
		Fail("Second var declaration is missing");

	}
	if (result->Main->tData.scope->Statement->Next->Next->type!=varDeclaration)
	{
		Fail("Third var declaration is missing");
	}
	Pass();
}
void TypeMissmatch()
{
	ResetScanner();
	lastError = NULL;
	currentTestName = "type missMatch";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/TypeMissmatch.txt");
	tProgram* result = Parse();
	if (lastError!=4)
	{
		Fail("Wrong error detected");
	}
	Pass();
}

void PrintWithoutSpace()
{
	ResetScanner();
	lastError = NULL;
	currentTestName = "Print without trailing space";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/printWithoutSpace.txt");
	tProgram* result = Parse();
	if (lastError!=0)
	{
		Fail("Error detected");
	}
	if (result->Main->type!=scope || result->Main->tData.scope==NULL)
	{
		Fail("Scope failed to parse");
	}
	if (result->Main->tData.scope->Statement == NULL || result->Main->tData.scope->Statement->type!=print)
	{
		Fail("Print node is missing");
	}
	
	Pass();
}

void VarDeclarationWithAllTypes()
{
	ResetScanner();
	lastError = NULL;
	currentTestName = "VarDeclarationWithAllTypes";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/VarDeclarationWithAllTypes.txt");
	tProgram* result = Parse();
	if (lastError!=0)
	{
		Fail("Error detected");
	}
	if (result->Main->type!=scope || result->Main->tData.scope==NULL)
	{
		Fail("Scope failed to parse");
	}
	if (result->Main->tData.scope->Statement->type!=varDeclaration)
	{
		Fail("First var declaration is missing");
	}
	if (result->Main->tData.scope->Statement->Next->type!=varDeclaration)
	{
		Fail("Second var declaration is missing");

	}
	if (result->Main->tData.scope->Statement->Next->Next->type!=varDeclaration)
	{
		Fail("Third var declaration is missing");
	}
	if (result->Main->tData.scope->Statement->Next->Next->Next->Next->type!=varDeclaration)
	{
		Fail("Third var declaration is missing");
	}
	if (result->Main->tData.scope->Statement->Next->Next->Next->Next->Next->type!=varDeclaration)
	{
		Fail("Third var declaration is missing");
	}
	if (result->Main->tData.scope->Statement->Next->Next->Next->Next->Next->Next->type!=varDeclaration)
	{
		Fail("Third var declaration is missing");
	}
	Pass();
}

void FunctionDeclaration()
{
	ResetScanner();
	lastError = NULL;
	currentTestName = "Function declaration";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/BasicFunctions.txt");
	tProgram* result = Parse();
	if (lastError!=0)
	{
		Fail("Error detected");
	}
	tFTItemPtr function = FTSearch(&result->functionTable, "foo");
	if (lastError != 0)
	{
		Fail("Error detected");
	}
	if (result->Main->type!=scope || result->Main->tData.scope==NULL)
	{
		Fail("Scope failed to parse");
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





