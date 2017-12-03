#include "ADT.h"
#include "ManagedMalloc.h"
#include <stdlib.h>
#include <string.h>
#include "errors.h"

void StackInit(TStack_t * stack)
{
	void ** itemPtr = mmalloc(sizeof(void*)*DEFAULT_STACK_SIZE);
	if ((itemPtr) == NULL)
	{
		mfreeall();
		ERR_CODE code = INTERNAL_ERR;
		exit(code);
	}
	stack->items = itemPtr;
	*(stack->items) = NULL;
	stack->actualSize = 0;
	stack->maxSize = DEFAULT_STACK_SIZE;
}

bool StackIsEmpty(TStack_t * stack)
{
	if (stack == NULL)
		return true;

	if (stack->actualSize == 0)
		return true;

	return false;
}

void StackPush(TStack_t * stack, void * ptr)
{
	if (stack == NULL)
		return;

	if ((stack->actualSize) < (stack->maxSize))
	{
		(stack->items)[stack->actualSize] = ptr;
		(stack->actualSize)++;
	}
	else
	{
		void ** newVoidArr = mmalloc(sizeof(void*) * ((stack->maxSize + DEFAULT_STACK_SIZE)));
		if ((newVoidArr) == NULL)
		{
			mfreeall();
			ERR_CODE code = INTERNAL_ERR;
			exit(code);
		}
		stack->maxSize += DEFAULT_STACK_SIZE;
		memcpy(newVoidArr, stack->items, sizeof(void*) * (stack->maxSize));
		mfree(stack->items);
		stack->items = newVoidArr;

		(stack->items)[stack->actualSize] = ptr;
		(stack->actualSize)++;
	}
}

void* StackTopPop(TStack_t * stack)
{
	if (stack == NULL)
		return NULL;

	if (stack->actualSize == 0)
	{
		return NULL;
	}
	else
		(stack->actualSize)--;

	return ((stack->items)[stack->actualSize]);
}

void StackDestroy(TStack_t * stack)
{
	if (stack == NULL)
		return;

	mfree(stack->items);
	stack->items = NULL;
	stack->maxSize = 0;
	stack->actualSize = 0;
}

void* StackTop(TStack_t * stack)
{
	if (stack != NULL && stack->actualSize != 0)
	{
		return stack->items[stack->actualSize-1];
	}
	return NULL;
}