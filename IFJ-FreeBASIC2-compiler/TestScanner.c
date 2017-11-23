#include "TestScanner.h"
#include "Tests.h"

char* currentTestName;

void ScannerTests()
{
	IntegerValue();
	DoubleValue();
	StringValue();
	Comment();
	Identificator();
	IterativeFactorial();
	BasicProgram();
}


void ClearUntilEOL()
{
	int c = getchar();

	while (CheckEOL(c) != 1)
	{
		c = getchar();
	}
}

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
	if (Exp_INTVALUE(32))
	{
		Fail("Expected token INTVAL : 2");
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
	if (Exp_DOUBLEVALUE(35000))
	{
		Fail("Expected token DOUBLEVALUE : 7");
		return;
	}

	Pass();
}

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
	if (Exp_DOUBLEVALUE(3300))
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

	ClearUntilEOL();

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
	if (Exp_STRINGVALUE("\\n"))
	{
		Fail("Expected token STRINGVALUE : 2");
		return;
	}
	if (Exp_STRINGVALUE("\\t"))
	{
		Fail("Expected token STRINGVALUE : 3");
		return;
	}
	if (Exp_STRINGVALUE("\\\\"))
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

	ClearUntilEOL();

	if (Exp_STRINGVALUE("\\002"))
	{
		Fail("Expected token STRINGVALUE : 8");
		return;
	}
	if (Exp_STRINGVALUE("\\069"))
	{
		Fail("Expected token STRINGVALUE : 9");
		return;
	}
	if (Exp_STRINGVALUE("\\255"))
	{
		Fail("Expected token STRINGVALUE : 10");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 11");
		return;
	}

	ClearUntilEOL();

	if (Exp_ERR())
	{
		Fail("Expected token ERR : 12");
		return;
	}

	Pass();
}

void Comment()
{
	ResetScanner();
	currentTestName = "Comments";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/comment.txt");

	if (Exp_ID("nicedwdwdwagwgwahawhwhawh"))
	{
		Fail("Expected token ID : 1");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : 2");
		return;
	}
	if (Exp_IF())
	{
		Fail("Expected token IF : 3");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : 4");
		return;
	}
	if (Exp_ID("ok"))
	{
		Fail("Expected token ID : 5");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 6");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : 9");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : 10");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 11");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 12");
		return;
	}

	Pass();
}

void Identificator()
{
	ResetScanner();
	currentTestName = "Identificator";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/id.txt");

	if (Exp_ID("pneumonoultramicroscopicsilicovolcanoconiosisahahahatestlenghtdwdslpodwagwfajglwbwfafw6464646"))
	{
		Fail("Expected token ID : 1");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : 2");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 3");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 4");
		return;
	}



	Pass();
}
void IterativeFactorial()
{
	ResetScanner();
	currentTestName = "Iterative factorial";
	LoadFileToSTDIN("../../../TestSamples/iterativeFactorial.txt");

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

	if (Exp_STRINGVALUE("\\nFaktorial nelze spocitat\\n"))
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

	if (Exp_STRINGVALUE("\\nVysledek je:"))
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

	if (Exp_STRINGVALUE("\\n"))
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

	if (Exp_SCOPE())
	{
		Fail("Expected scope as token 1");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected EOL as token 2");
		return;
	}
	if (Exp_DIM())
	{
		Fail("Expected DIM as token 3");
		return;
	}
	if (Exp_ID("a"))
	{
		Fail("Expected ID as token 4");
		return;
	}
	if (Exp_AS())
	{
		Fail("Expected AS as token 5");
		return;
	}
	if (Exp_INTEGER())
	{
		Fail("Expected INTEGER as token 6");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected EOL as token 7");
		return;
	}
	if (Exp_ID("a"))
	{
		Fail("Expected ID as token 8");
		return;
	}
	if (Exp_ASSIGN())
	{
		Fail("Expected ASSIGN as token 9");
		return;
	}
	if (Exp_INTVALUE(3))
	{
		Fail("Expected INTVALUE with value 3 as token 10");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected EOL as token 11");
		return;
	}
	if (Exp_END())
	{
		Fail("Expected END as token 12");
		return;
	}
	if (Exp_SCOPE())
	{
		Fail("Expected SCOPE as token 13");
		return;
	}
	if (Exp_EOF())
	{
		Fail("Expected EOF as token 14");
		return;
	}

	Pass();
}
