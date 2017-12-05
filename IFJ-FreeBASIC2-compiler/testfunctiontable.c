#include "testfunctiontable.h"

void FTInitTest()
{
	currentTestName = "FTInit Test";
	tFTItemPtr fTable;
	FTInit(&fTable);
	if (FTSearch(&fTable, "Chr") != NULL)
	{
		Pass();
		return;
	}
	Fail("Chr not found!");
}

void FTSearchTest()
{
	currentTestName = "FTSearch Test";
	tFTItemPtr fTable;
	FTInit(&fTable);
	FTInsert(&fTable, "Hello", false);
	if (FTSearch(&fTable, "Helo") != NULL)
	{
		Pass();
		return;
	}
	Fail("Not found");
}

void FTAddParameterTest()
{
	currentTestName = "FTAddParam Test";
	tFTItemPtr fTable;
	FTInit(&fTable);
	tFTItemPtr item = FTInsert(&fTable, "Banana", true);
	AddParemeter(item, "a", TYPE_Integer);
	if (strcmp(item->parametersArr->name, "a") != 0)
	{
		if (item->parametersArr->type != TYPE_Integer)
		{
			Fail("incorrect type");
			return;
		}
		Fail("incorrect param");
		return;
	}

	Pass();
}

void FTAddRetrunValueTest()
{
	currentTestName = "FTAddRetValue Test";
	tFTItemPtr fTable;
	FTInit(&fTable);
	tFTItemPtr item = FTInsert(&fTable, "Apple", true);
	AddReturnValue(item, TYPE_String);
	if (item->parametersArr->type != TYPE_String)
	{
		Fail("Incorrect return type");
	}
	Pass();
}

void FTRemoveTest()
{

}

void CompareParametersTest()
{

}

void IsDeclaratioOnlyTest()
{

}

void FTRunAllTests()
{
	void FTInitTest();
	void FTSearchTest();
	void FTAddParameterTest();
	void FTAddRetrunValueTest();
	void FTRemoveTest();
	void CompareParametersTest();
	void IsDeclaratioOnlyTest();
}