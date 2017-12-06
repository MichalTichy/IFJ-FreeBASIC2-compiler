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
	if (FTSearch(&fTable, "Hello") != NULL)
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
	if (item->returnValue != TYPE_String)
	{
		Fail("Incorrect return type");
		return;
	}
	Pass();
}

void FTRemoveTest()
{
	currentTestName = "FTRemove Test";
	tFTItemPtr fTable;
	FTInit(&fTable);
	tFTItemPtr item = FTInsert(&fTable, "Data", true);
	FTRemove(&fTable, "Chr");
	item = FTSearch(&fTable, "Data");
	if (item == NULL)
	{
		Fail("Item not found");
		return;
	}
	Pass();
}

void CompareParametersTest()
{
	currentTestName = "CompareParameters Test";
	tFTItemPtr fTable;
	FTInit(&fTable);
	tFTItemPtr item = FTInsert(&fTable, "Banana", true);
	AddParemeter(item, "a", TYPE_Integer);
	AddParemeter(item, "ble", TYPE_Integer);
	AddParemeter(item, "c", TYPE_Integer);
	AddParemeter(item, "dude", TYPE_Double);
	AddParemeter(item, "e", TYPE_Integer);
	AddParemeter(item, "freak", TYPE_Integer);
	AddParemeter(item, "g", TYPE_String);

	CompareParameterSignature(item, 0, "a", TYPE_Integer);
	CompareParameterSignature(item, 1, "ble", TYPE_Integer);
	CompareParameterSignature(item, 2, "c", TYPE_Integer);
	CompareParameterSignature(item, 3, "dude", TYPE_Double);
	CompareParameterSignature(item, 4, "e", TYPE_Integer);
	CompareParameterSignature(item, 5, "freak", TYPE_Integer);
	CompareParameterSignature(item, 6, "g", TYPE_String);
	

	Pass();
}

void IsDeclaratioOnlyTest()
{
	currentTestName = "IsDeclarationOnly Test";
	tFTItemPtr fTable;
	FTInit(&fTable);
	FTInsert(&fTable, "Banana", true);
	if (FTIsDefinitionOnly(&fTable))
	{
		Fail("One should be declaration");
	}
	else
	{
		Pass();
	}
	FTInsert(&fTable, "Banana", false);
	currentTestName = "IsDeclarationonly Test2";
	if (!FTIsDefinitionOnly(&fTable))
	{
		Pass();
	}
	else
	{
		Fail("None should be declaration");
	}

}

void FTRunAllTests()
{
	FTInitTest();
	FTSearchTest();
	FTAddParameterTest();
	FTAddRetrunValueTest();
	FTRemoveTest();
	CompareParametersTest();
	IsDeclaratioOnlyTest();
}