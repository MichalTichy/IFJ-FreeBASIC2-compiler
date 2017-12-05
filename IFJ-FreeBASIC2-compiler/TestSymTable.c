#include "SymTable.h"
#include "Tests.h"
#include "Parser.h"

void TestSTInit()
{
	currentTestName = "Testing Initialization";

	tSTItemPtr symtable;
	STInit(&symtable);

	if (symtable == NULL)
	{
		Pass();
		return;
	}

	Fail("Pointer not Initialised");
	return;

}

void TestSTSearchEmpty()
{
	currentTestName = "Test Search Empty";

	tSTItemPtr symtable;
	STInit(&symtable);

	tSTItemPtr itemptr = STSearch(&symtable, "key");
	
	if (itemptr == NULL)
	{
		Pass();
		return;
	}

	Fail("Item pointer not NULL");
	return;
}

void TestSTInsert()
{
	currentTestName = "Test Insert";

	tSTItemPtr symtable;
	STInit(&symtable);

	STInsert(&symtable, "key", TYPE_String);

	if (symtable != NULL)
	{
		if (strcmp(symtable->data, "key") == 0)
		{
			if (symtable->len == 3)
			{
				if (symtable->rptr == NULL)
				{
					if (symtable->lptr == NULL)
					{
						Pass();
						return;
					}
					else
					{
						Fail("Lptr Expected NULL");
						return;
					}
				}
				else
				{
					Fail("Rptr Expected NULL");
					return;
				}
			}
			else
			{
				Fail("Len Expected 3");
				return;
			}
		}
		else
		{
			Fail("Key expected: Key");
			return;
		}
	}
	else
	{
		Fail("Is Empty");
		return;
	}
	

	Fail("unexpected error");
	return;

}

void TestSTInsertMultiple()
{
	currentTestName = "Test Multiple Insert";

	tSTItemPtr symtable;
	STInit(&symtable);

	STInsert(&symtable, "Eva",TYPE_String);
	STInsert(&symtable, "Eda", TYPE_String);
	STInsert(&symtable, "Jana", TYPE_String);
	STInsert(&symtable, "Eduard", TYPE_String);
	STInsert(&symtable, "Honza", TYPE_String);
	STInsert(&symtable, "Zuzka", TYPE_String);

	if (strcmp(symtable->lptr->rptr->data, "Eduard") == 0)
	{
		if (symtable->lptr->rptr->len == 6)
		{
			if (symtable->lptr->rptr->lptr == NULL)
			{
				if (symtable->lptr->rptr->rptr == NULL)
				{
					Pass();
					return;
				}
				else
				{
					Fail("Lptr Expected NULL");
					return;
				}
			}
			else
			{
				Fail("Rptr Expected NULL");
				return;
			}
		}
		else
		{
			Fail("Len Expected 6");
			return;
		}
	}
	else
	{
		Fail("Key expected: Eduard");
		return;
	}

	if (strcmp(symtable->rptr->rptr->data, "Honza") == 0)
	{
		if (symtable->rptr->rptr->len == 5)
		{
			if (symtable->rptr->rptr->lptr == NULL)
			{
				if (symtable->rptr->rptr->rptr != NULL)
				{
					Pass();
				}
				else
				{
					Fail("Lptr Expected NULL");
					return;
				}
			}
			else
			{
				Fail("Rptr Expected different from NULL");
				return;
			}
		}
		else
		{
			Fail("Len Expected 5");
			return;
		}
	}
	else
	{
		Fail("Key expected: Honza");
		return;
	}
}

void TestSTSearch()
{
	currentTestName = "Test Search";

	tSTItemPtr symtable;
	STInit(&symtable);

	STInsert(&symtable, "Eva", TYPE_String);
	STInsert(&symtable, "Eda", TYPE_String);
	STInsert(&symtable, "Jana", TYPE_String);
	STInsert(&symtable, "Eduard", TYPE_String);
	STInsert(&symtable, "Honza", TYPE_String);
	STInsert(&symtable, "Zuzka", TYPE_String);

	tSTItemPtr itemptr = STSearch(&symtable, "Honza");

	if (itemptr != NULL)
	{
		if (strcmp(itemptr->data, "Honza") == 0)
		{
			Pass();
			return;
		}
		else
		{
			Fail("Incorrect key");
			return;
		}
	}
	else
	{
		Fail("Not Found");
		return;
	}

	Fail("unexpected error");
	return;
}

void TestMakeScope()
{
	currentTestName = "Test Make Scope";

	tSTScopePtr scope;

	STMakeScope(&scope, NULL);

	if (scope != NULL)
	{
		if (scope->parentScope == NULL)
		{
			if (scope->symtable == NULL)
			{
				Pass();
				return;
			}
			else
			{
				Fail("symtable is not NULL");
				return;
			}
		}
		else
		{
			Fail("Parent scope is not NULL");
			return;
		}
	}
	else
	{
		Fail("scope is NULL");
		return;
	}
	Fail("Unexpected error");
}

void TestScopeSearch()
{
	currentTestName = "Test Scope Search";

	tSTScopePtr scope;

	STMakeScope(&scope, NULL);

	STScopeInsert(&scope, "rain", TYPE_String);
	STScopeInsert(&scope, "pain", TYPE_String);

	tSTScopePtr scope2;
	tSTScopePtr scope3;

	STMakeScope(&scope2, scope);
	STMakeScope(&scope3, scope2);
	STScopeInsert(&scope3, "believer", TYPE_String);

	tSTItemPtr item = STScopeSearch(&scope3, "pain");

	if (item != NULL)
	{
		if (strcmp(item->data, "pain") == 0)
		{
			Pass();
			return;
		}
		else
		{
			Fail("Incorrect Key");
			return;
		}
	}
	else
	{
		Fail("not found item is NULL");
	}

	Fail("unexpected error");

}

void TestSTDeleteTopScope()
{
	currentTestName = "Test Delete Scope";

	tSTScopePtr scope;

	STMakeScope(&scope, NULL);

	STScopeInsert(&scope, "hell", TYPE_String);
	STScopeInsert(&scope, "pain", TYPE_String);

	tSTScopePtr scope2;
	tSTScopePtr scope3;

	STMakeScope(&scope2, scope);
	STMakeScope(&scope3, scope2);
	STScopeInsert(&scope3, "no sleep", TYPE_String);

	STDeleteTopScope(&scope3);

	if (scope3 == NULL)
	{
		tSTItemPtr item = STScopeSearch(&scope2, "hell");
		if (strcmp(item->data, "hell") == 0)
		{
			Pass();
			return;
		}
		else
		{
			Fail("item in other scopes not found");
			return;
		}
	}
	else
	{
		Fail("scope is not NULL");
		return;
	}

	Fail("unknown error");
	return;

}
void NestedScope()
{
	ResetScanner();
	lastError = NULL;
	currentTestName = "Nested scope";
	LoadFileToSTDIN("../../../TestSamples/ParserTests/NestedScope.txt");
	tProgram* result = Parse();
	if (lastError != 0)
	{
		Fail("Error detected");
	}

	Pass();

}
void AllSymTableTests()
{
	TestSTInit();

	TestSTSearchEmpty();

	TestSTInsert();

	TestSTInsertMultiple();

	TestSTSearch();

	TestMakeScope();

	TestScopeSearch();

	TestSTDeleteTopScope();

	NestedScope();

	return;
}


