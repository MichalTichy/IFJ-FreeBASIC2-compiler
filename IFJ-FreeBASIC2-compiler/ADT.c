/**
*	Project: IFJ17 Compiler
*
*	FILE: adt.c
*
*	File author:
*	  Ondrej Deingruber, xdeing00
*
*	Project authors:
*	  Michal Tichy, xtichy26
*	  Michal Martinu, xmarti78
*	  Gabriel Mastny, xmastn02
*	  Ondrej Deingruber, xdeing00
*
**/

#include "ADT.h"
#include "ManagedMalloc.h"
#include <stdlib.h>
#include <string.h>
#include "errors.h"

void StackInit(TStack_t * stack)
/**
* Function initializises stack
* should be used only once!
* @param tableptr is pointer to stack
**/
{
	void ** itemPtr = mmalloc(sizeof(void*)*DEFAULT_STACK_SIZE); // maloc stack
	if ((itemPtr) == NULL)
	{
		mfreeall();
		ERR_CODE code = INTERNAL_ERR;
		exit(code);
	}
	stack->items = itemPtr;			// Init values
	*(stack->items) = NULL;
	stack->actualSize = 0;
	stack->maxSize = DEFAULT_STACK_SIZE;
}

bool StackIsEmpty(TStack_t * stack)
/**
* Function chacks whenever stack is empty
* @param stack is pointer to stack
* @return bool determinating if stack is empty
**/
{
	if (stack == NULL)	// invalid ptr
		return true;

	if (stack->actualSize == 0)
		return true;

	return false;
}

void StackPush(TStack_t * stack, void * ptr)
/**
* Function pushes item to stack
* @param stack is pointer to stack
* @param ptr is pointer to save on stack
**/
{
	if (stack == NULL)
		return;

	if ((stack->actualSize) < (stack->maxSize))		// can insert	
	{
		(stack->items)[stack->actualSize] = ptr;
		(stack->actualSize)++;
	}
	else											// need to alloc more space
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
/**
* Function tops stack and pop stack
* @param stack is pointer to stack
* @return top item on stack
**/
{
	if (stack == NULL)	// invalid ptr
		return NULL;

	if (stack->actualSize == 0) // empty stack
	{
		return NULL;
	}
	else
		(stack->actualSize)--;

	return ((stack->items)[stack->actualSize]);
}

void StackDestroy(TStack_t * stack)
/**
* Function destroys stack
* @param stack is pointer to stack
**/
{
	if (stack == NULL)	// invalid ptr
		return;

	mfree(stack->items);
	stack->items = NULL;
	stack->maxSize = 0;
	stack->actualSize = 0;
}

void* StackTop(TStack_t * stack)
/**
* Function returns top item on stack
* @param stack is pointer to stack
* @return top item on stack or NULL if empty
**/
{
	if (stack != NULL && stack->actualSize != 0)
	{
		return stack->items[stack->actualSize - 1];
	}
	return NULL;
}