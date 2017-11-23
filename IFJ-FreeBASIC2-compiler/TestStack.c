#include "TestStack.h"
#include "ADT.h"
#include "Tests.h"


void StackInitTest()
{
	currentTestName = "Stack Initialization Test";
	TStack_t stack;
	StackInit(&stack);

	if (stack.items != NULL)
	{
		if (stack.maxSize == DEFAULT_STACK_SIZE)
		{
			if (stack.actualSize == 0)
			{
				Pass();
				return;
			}
			else
			{
				Fail("actualSize is not 0");
				return;
			}
		}
		else
		{
			Fail("maxsize is not correct");
			return;
		}
	}
	else
	{
		Fail("pointer to array is NULL");
		return;
	}

	Fail("Stack parameters dont match");
}

void EmptyTest()
{
	currentTestName = "Stack IsEmpty Test Empty Stack";
	TStack_t stack;
	StackInit(&stack);
	
	if (StackIsEmpty(&stack))
	{
		Pass();
		return;
	}

	Fail("stack is not empty");
}

void StackPopTopEmpty()
{
	currentTestName = "Stack Pop Empty";
	TStack_t stack;
	StackInit(&stack);
	void* ptr;

	if (((ptr = StackTopPop(&stack)) == NULL))
	{
		Pass();
		return;
	}

	Fail("empty stack did pop");
}

void StackInsertTest()
{
	currentTestName = "Stack Insert Test";
	TStack_t stack;
	StackInit(&stack);
	int a = 1;
	int b = 2;
	int c = 3;

	StackPush(&stack, (void*)(&a));
	StackPush(&stack, (void*)(&b));
	StackPush(&stack, (void*)(&c));

	int* numberptr = StackTopPop(&stack);
	if ( *(numberptr) == 3)
	{
		if ( *((int*)StackTopPop(&stack)) == 2)
		{
			if ( *((int*)StackTopPop(&stack)) == 1)
			{
				Pass();
				return;
			}
			else
			{
				Fail("expected 1");
			}
		}
		else
		{
			Fail("expected 2");
		}
	}
	else
	{
		Fail("expected 3");
	}

	Fail("unexpected error");
}

void StackPopTopEmptyAfterPopingLast()
{
	currentTestName = "Stack Pop Empty After Changes To Stack";
	TStack_t stack;
	StackInit(&stack);
	int a = 1;
	int b = 2;
	int c = 3;

	StackPush(&stack, (void*)(&a));
	StackPush(&stack, (void*)(&b));
	StackPush(&stack, (void*)(&c));

	if (*(int*)(StackTopPop(&stack)) == 3)
	{
		if ((*(int*)(StackTopPop(&stack))) == 2)
		{
			if ((*(int*)(StackTopPop(&stack))) == 1)
			{
				if (StackIsEmpty(&stack))
				{
					Pass();
					return;
				}
				else
				{
					Fail("expected true");
					return;
				}
			}
		}
	}
	Fail("unexpected error");
}

void StackExpansionTest() {
	currentTestName = "Stack Expansion Test";
	TStack_t stack;
	StackInit(&stack);
	int a = 1;

	for (int i = 0; i != DEFAULT_STACK_SIZE + 1; i++)
	{
		StackPush(&stack, &a);
	}

	if (stack.maxSize == (2 * DEFAULT_STACK_SIZE))
	{
		if (stack.actualSize ==(DEFAULT_STACK_SIZE + 1))
		{
			Pass();
			return;
		}
		else
		{
			Fail("invalid actualSize");
			return;
		}
	}
	else
	{
		Fail("invalid maxSize");
		return;
	}

	printf("stack maxsize is %d, expected %d\n", stack.maxSize, (2 * DEFAULT_STACK_SIZE));
	Fail("unexpected err");
}


void StackDestroyTest()
{
	currentTestName = "Stack Destroy Test";
		TStack_t stack;
	StackInit(&stack);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;

	StackPush(&stack, (void*)(&a));
	StackPush(&stack, (void*)(&b));
	StackPush(&stack, (void*)(&c));
	StackPush(&stack, (void*)(&d));
	StackPush(&stack, (void*)(&e));
	StackPush(&stack, (void*)(&f));

	StackDestroy(&stack);

	if (stack.items == NULL && stack.maxSize == 0 && stack.actualSize == 0)
	{
		Pass();
		return;
	}

	Fail("unexpected stack struct member values");
}

void StackAllTests()
{
	
	StackInitTest();
	EmptyTest();
	StackPopTopEmpty();
	StackInsertTest();
	StackPopTopEmptyAfterPopingLast();
	StackExpansionTest();
	StackDestroyTest();

}