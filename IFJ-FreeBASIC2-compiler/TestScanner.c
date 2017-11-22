#include "TestScanner.h"

char* currentTestName;

void IntegerValue()
{
	ResetScanner();
	currentTestName = "Integer value";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/INTVAL.txt");
	
	if (Exp_INTVALUE(454561313))
	{
		Fail("Expected token INTVAL : 1");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : 3");
		return;
	}
	if (Exp_SUB())
	{
		Fail("Expected token SUB : 4");
		return;
	}
	if (Exp_INTVALUE(35689744))
	{
		Fail("Expected token INTVAL : 5");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 6");
		return;
	}

	Pass();
}

//This Test FAIL
void DoubleValue()
{
	ResetScanner();
	currentTestName = "Double value";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/DoubleValue.txt");

	if (Exp_DOUBLEVALUE(3.5648))
	{
		Fail("Expected token DOUBLEVALUE : 1");
		return;
	}
	if (Exp_DOUBLEVALUE(3000))
	{
		Fail("Expected token DOUBLEVALUE : 2");
		return;
	}
	if (Exp_DOUBLEVALUE(0.0053))
	{
		Fail("Expected token DOUBLEVALUE : 3");
		return;
	}
	if (Exp_DOUBLEVALUE(89700))
	{
		Fail("Expected token DOUBLEVALUE : 4");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 5");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 6");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 7");
		return;
	}
	if (Exp_EOF())
	{
		Fail("Expected token EOF : 8");
		return;
	}

	Pass();
}

void StringValue()
{
	ResetScanner();
	currentTestName = "String value";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/StringValue.txt");

	if (Exp_STRINGVALUE("AhOj"))
	{
		Fail("Expected token STRINGVALUE : 1");
		return;
	}
		if (Exp_STRINGVALUE("\n"))
	{
		Fail("Expected token STRINGVALUE : 2");
		return;
	}
	if (Exp_STRINGVALUE("\t"))
	{
		Fail("Expected token STRINGVALUE : 3");
		return;
	}
	if (Exp_STRINGVALUE("\\"))
	{
		Fail("Expected token STRINGVLUE : 4");
		return;
	}
	if (Exp_STRINGVALUE("3a"))
	{
		Fail("Expected token STRINGVALUE : 5");
		return;
	}
	if (Exp_STRINGVALUE("a !"))
	{
		Fail("Expected token STRINGVALUE : 6");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 7");
		return;
	}

	Pass();
}