#include "ADT.h"
#include "ManagedMalloc.h"
#include <stdlib.h>
#include <string.h>

void StackInit(TStack_t * stack)
{
	mmalloc(sizeof(void*)*DEFAULT_STACK_SIZE);
	stack->items = NULL;
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
		stack->items = (stack->items) + 1;
	}
	else			// replace with mrealloc when avalible
	{
		void ** newVoidArr = mmalloc(sizeof(void*) * ((stack->maxSize) + 128));
		memcpy(newVoidArr, stack->items, sizeof(void*) * (stack->maxSize));
		mfree(stack->items);
		stack->items = newVoidArr;

		(stack->items)[stack->actualSize] = ptr;
		stack->items = (stack->items) + 1;
	}
}

void* StackTopPop(TStack_t * stack)
{
	if (stack == NULL)
		return NULL;

	if (stack->actualSize != 0)
		(stack->actualSize)--;

	return (stack->items)[stack->actualSize];
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
