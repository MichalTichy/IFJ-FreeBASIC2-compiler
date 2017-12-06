#include "TestScanner.h"
#include "Tests.h"
#

char* currentTestName;

void ScannerTests()
{
	IntegerValue();
	StringValue();
	Comment();
	BlockCommentErr();
	Identificator();
	IterativeFactorial();
	BasicProgram();
	ErrorTest_1();
	ErrorComment();
	ErrorComment2();
	KeyWordsTest();
	ReservedWordsTest();
	DobleValueError1();
	DobleValueError2();
	DobleValueError3();
	DobleValueError4();
	DoubleValue();
	DobleValue2();
	DobleValue3();
	DobleValue4();
	StringError1();
	StringError2();
	Idenfificator2();
	Idenfificator3();
}

void ClearUntilEOL()
{
	int c = getchar();

	while (CheckEOL((char) c) != 1)
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

	if (Exp_STRINGVALUE("/'Komen'//032'\\056koment"))
	{
		Fail("Expected token STRINGVALUE : 1");
		return;
	}
	if (Exp_STRINGVALUE("\\010"))
	{
		Fail("Expected token STRINGVALUE : 2");
		return;
	}
	if (Exp_STRINGVALUE("\\009"))
	{
		Fail("Expected token STRINGVALUE : 3");
		return;
	}
	if (Exp_STRINGVALUE("\\092"))
	{
		Fail("Expected token STRINGVLUE : 4");
		return;
	}
	if (Exp_STRINGVALUE("3a"))
	{
		Fail("Expected token STRINGVALUE : 5");
		return;
	}
	if (Exp_STRINGVALUE("a\\032!"))
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
	if (Exp_NOT())
	{
		Fail("Expected token NOT : 11");
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
	if (Exp_INTVALUE(5))
	{
		Fail("Expected token INTVALUE : 3");
		return;
	}
	if (Exp_ID("a"))
	{
		Fail("Expected token ID : 4");
		return;
	}
	if (Exp_ID("b"))
	{
		Fail("Expected token ID : 5");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 6");
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

	if (Exp_STRINGVALUE("Zadejte\\032cislo\\032pro\\032vypocet\\032faktorialu"))
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

	if (Exp_STRINGVALUE("\\010Faktorial\\032nelze\\032spocitat\\010"))
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

	if (Exp_STRINGVALUE("\\010Vysledek\\032je:"))
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

	if (Exp_STRINGVALUE("\\010"))
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

void ErrorTest_1()
{
	ResetScanner();
	currentTestName = "ErrorTest_1";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/ErrorTest_1.txt");

	if (Exp_EOL())
	{
		Fail("Expected token EOL : 1");
		return;
	}

	if (Exp_ERR())
	{
		Fail("Expected token ERR : 2");
		return;
	}

	Pass();
}

void BlockCommentErr()
{
	ResetScanner();
	currentTestName = "BlockCommentError";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/BlockCommentErr.txt");

	if (Exp_ERR())
	{
		Fail("Expected token ERR : 1");
		return;
	}

	Pass();
}

void ErrorComment()
{
	ResetScanner();
	currentTestName = "ErrorComment";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/ErrorComment.txt");

	if (Exp_ERR())
	{
		Fail("Expected token ERR : 1");
		return;
	}
	if (Exp_EOF())
	{
		Fail("Expected token EOF : 2");
		return;
	}

	Pass();
}

void ErrorComment2()
{
	ResetScanner();
	currentTestName = "ErrorComment2";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/ErrorComment2.txt");

	if (Exp_EOF())
	{
		Fail("Expected token EOF : 2");
		return;
	}

	Pass();
}

void KeyWordsTest()
{
	ResetScanner();
	currentTestName = "Keywords";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/Keywords.txt");
	
	if (Exp_AS())
	{
		Fail("Expected token AS : 1");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	/*if (Exp_ASC())
	{
		Fail("Expected token ASC : 2");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}*/
	if (Exp_DECLARE())
	{
		Fail("Expected token DECLARE : 3");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_DIM())
	{
		Fail("Expected token DIM : 4");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_DO())
	{
		Fail("Expected token DO : 5");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_DOUBLE())
	{
		Fail("Expected token DOUBLE : 6");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_ELSE())
	{
		Fail("Expected token ELSE : 7");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_END())
	{
		Fail("Expected token END : 8");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	/*if (Exp_CHR())
	{
		Fail("Expected token CHR : 9");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}*/
	if (Exp_FUNCTION())
	{
		Fail("Expected token FUNCTION : 10");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_IF())
	{
		Fail("Expected token IF : 11");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_INPUT())
	{
		Fail("Expected token INPUT : 12");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_INTEGER())
	{
		Fail("Expected token INTEGER : 13");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	/*if (Exp_LENGHT())
	{
		Fail("Expected token LENGHT : 14");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}*/
	if (Exp_LOOP())
	{
		Fail("Expected token LOOP : 15");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_PRINT())
	{
		Fail("Expected token PRINT : 16");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_RETURN())
	{
		Fail("Expected token RETUNR : 17");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_SCOPE())
	{
		Fail("Expected token SCOPE : 18");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_STRING())
	{
		Fail("Expected token STRING : 19");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	/*if (Exp_SUBSTRING())
	{
		Fail("Expected token SUBSTRING : 20");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}*/
	if (Exp_THEN())
	{
		Fail("Expected token THEN : 21");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_WHILE())
	{
		Fail("Expected token WHILE : 22");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_ELSEIF())
	{
		Fail("Expected token ELSEIF : 23");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_AND())
	{
		Fail("Expected token AND : 24");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_OR())
	{
		Fail("Expected token OR : 25");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_NOT())
	{
		Fail("Expected token NOT : 26");
		return;
	}
	if (Exp_EOF())
	{
		Fail("Expected token EOF : x");
		return;
	}

	Pass();
}

void ReservedWordsTest()
{
	ResetScanner();
	currentTestName = "ReservedWords";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/ReservedWords.txt");

	if (Exp_SyntaxERR())
	{
		Fail("Expected token SyERR : 1");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_SyntaxERR())
	{
		Fail("Expected token SyERR : 2");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_SyntaxERR())
	{
		Fail("Expected token SyERR : 3");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_SyntaxERR())
	{
		Fail("Expected token SyERR : 4");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_SyntaxERR())
	{
		Fail("Expected token SyERR : 5");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_SyntaxERR())
	{
		Fail("Expected token SyERR : 6");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_SyntaxERR())
	{
		Fail("Expected token SyERR : 7");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_SyntaxERR())
	{
		Fail("Expected token SyERR : 8");
		return;
	}
	if (Exp_EOL())
	{
		Fail("Expected token EOL : x");
		return;
	}
	if (Exp_SyntaxERR())
	{
		Fail("Expected token SyERR : 9");
		return;
	}
	if (Exp_EOF())
	{
		Fail("Expected token EOF : x");
		return;
	}

	Pass();
}

void DobleValueError1()
{
	ResetScanner();
	currentTestName = "DoubleValueError1";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/DoubleValueError1.txt");

	if (Exp_ERR())
	{
		Fail("Expected token ERR : 1");
		return;
	}
	if (Exp_EOF())
	{
		Fail("Expected token EOF : 2");
		return;
	}

	Pass();
}

void DobleValueError2()
{
	ResetScanner();
	currentTestName = "DoubleValueError2";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/DoubleValueError2.txt");

	if (Exp_ERR())
	{
		Fail("Expected token ERR : 1");
		return;
	}

	Pass();
}

void DobleValueError3()
{
	ResetScanner();
	currentTestName = "DoubleValueError3";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/DoubleValueError3.txt");

	if (Exp_DOUBLEVALUE(3000000))
	{
		Fail("Expected token DOUBLEVALUE : 1");
		return;
	}
	if (Exp_ERR())
	{
		Fail("Expected token ERR : 2");
		return;
	}

	Pass();
}

void DobleValueError4()
{
	ResetScanner();
	currentTestName = "DoubleValueError4";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/DoubleValueError4.txt");

	if (Exp_ERR())
	{
		Fail("Expected token ERR : 1");
		return;
	}

	Pass();
}

void DobleValue2()
{
	ResetScanner();
	currentTestName = "DoubleValue2";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/DoubleValue2.txt");

	if (Exp_DOUBLEVALUE(35000))
	{
		Fail("Expected token DOUBLEVALUE : 1");
		return;
	}
	if (Exp_EOF())
	{
		Fail("Expected token EOF : 2");
		return;
	}

	Pass();
}

void DobleValue3()
{
	ResetScanner();
	currentTestName = "DoubleValue3";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/DoubleValue3.txt");

	if (Exp_DOUBLEVALUE(36000))
	{
		Fail("Expected token DOUBLEVALUE : 1");
		return;
	}
	if (Exp_EOF())
	{
		Fail("Expected token EOF : 2");
		return;
	}

	Pass();
}

void DobleValue4()
{
	ResetScanner();
	currentTestName = "DoubleValue4";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/DoubleValue4.txt");

	if (Exp_DOUBLEVALUE(0.36))
	{
		Fail("Expected token DOUBLEVALUE : 1");
		return;
	}
	if (Exp_EOF())
	{
		Fail("Expected token EOF : 2");
		return;
	}

	Pass();
}

void StringError1()
{
	ResetScanner();
	currentTestName = "StringError1";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/StringError1.txt");

	if (Exp_ERR())
	{
		Fail("Expected token ERR : 1");
		return;
	}

	Pass();
}

void StringError2()
{
	ResetScanner();
	currentTestName = "StringError2";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/StringError2.txt");

	if (Exp_ERR())
	{
		Fail("Expected token ERR : 1");
		return;
	}

	Pass();
}

void Idenfificator2()
{
	ResetScanner();
	currentTestName = "Identificator2";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/Identificator2.txt");

	if (Exp_ID("_225_"))
	{
		Fail("Expected token ID : 1");
		return;
	}

	Pass();
}

void Idenfificator3()
{
	ResetScanner();
	currentTestName = "Identificator3";
	LoadFileToSTDIN("../../../TestSamples/ScannerTests/Identificator3.txt");

	if (Exp_ID("wdjjdwo____wdwafj45wfw_44_"))
	{
		Fail("Expected token ID : 1");
		return;
	}

	Pass();
}