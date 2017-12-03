#include "functiontable.h"
#include <stdlib.h>
#include "errors.h"
#include <string.h>
#include "ManagedMalloc.h"

void ReplaceByRightmost(tFTItemPtr PtrReplaced, tFTItemPtr* RootPtr) 
{
	if ((*RootPtr)->rptr == NULL)		// Is the Rightmost
	{
		PtrReplaced->data = (*RootPtr)->data;
		PtrReplaced->len = (*RootPtr)->len;
		PtrReplaced->parametersMax = (*RootPtr)->parametersMax;
		PtrReplaced->parametersCount = (*RootPtr)->parametersCount;
		PtrReplaced->returnValue = (*RootPtr)->returnValue;
		PtrReplaced->parameters = (*RootPtr)->parameters;
		if ((*RootPtr)->lptr != NULL)	// Have left child
		{
			tFTItemPtr child = (*RootPtr)->lptr;
			mfree(*RootPtr);
			*RootPtr = child;
		}
		else							// Dont have child
		{
			mfree(*RootPtr);
			*RootPtr = NULL;
		}
	}
	else								// Go to right node
	{
		ReplaceByRightmost(PtrReplaced, &((*RootPtr)->rptr));
	}
}

void FTInit(tFTItemPtr* tableptr)
{
	*tableptr = NULL;
}

tFTItemPtr FTSearch(tFTItemPtr* tableptr, char* token)
{
	tFTItemPtr itemPtr = *tableptr;
	while (itemPtr != NULL)
	{
		if (strcmp(itemPtr->data, token) == 0)
		{
			break;
		}
		else if (strcmp(itemPtr->data, token) < 0)		// Token is bigger
		{
			itemPtr = itemPtr->rptr;
		}
		else		// Token is smaller
		{
			itemPtr = itemPtr->lptr;
		}
	}
	return itemPtr;
}

void FTInsert(tFTItemPtr* tableptr, char* token)
{
	if (tableptr == NULL)
	{
		return;
	}
	tFTItemPtr* itemPtr = tableptr;
	while ((*itemPtr) != NULL)
	{
		if (strcmp((*itemPtr)->data, token) == 0)			// Token is here
		{
			break;
		}
		else if (strcmp((*itemPtr)->data, token) < 0)		// Token is bigger
		{
			itemPtr = &((*itemPtr)->rptr);
		}
		else		// Token is smaller
		{
			itemPtr = &((*itemPtr)->lptr);
		}
	}
	*itemPtr = mmalloc(sizeof(struct tFTItem));
	if ((*itemPtr) == NULL)
	{
		exitSecurely(INTERNAL_ERR);
	}
	else
	{
		(*itemPtr)->len = (unsigned)strlen(token);
		(*itemPtr)->data = token;
		(*itemPtr)->returnValue = TYPE_Void;
		(*itemPtr)->parameters = mmalloc(sizeof(char*) * 5);
		if ((*itemPtr)->parameters == NULL)
		{
			exitSecurely(INTERNAL_ERR);
		}
		(*itemPtr)->parametersMax = 5;
		(*itemPtr)->parametersCount = 0;
		(*itemPtr)->lptr = NULL;
		(*itemPtr)->rptr = NULL;
	}
}

void AddParemeter(tFTItemPtr* funItem, char* name, ScalarType type)
{
	tFTItemPtr item = FTSearch(funItem, name);

	if (item->parametersMax <= item->parametersCount)
	{
		(*funItem)->parameters = mrealloc((*funItem)->parameters, sizeof(char*) * ((*funItem)->parametersMax + 5));
		item->parametersMax = item->parametersMax + 5;
	}

	item->parameters[item->parametersCount] = name;
	item->parametersCount = item->parametersCount + 1;
}

void FTFree(tFTItemPtr* tableptr)
{
	TStack_t s;
	StackInit(&s);						// init stack of pointers
	do
	{
		if ((*tableptr) == NULL)			// take node from stack
		{
			if (!StackIsEmpty(&s))
			{
				*tableptr = StackTopPop(&s);
			}
		}
		else							// move right to stack
		{
			if ((*tableptr)->rptr != NULL)
			{
				StackPush(&s, (*tableptr)->rptr);
			}
			tFTItemPtr auxPtr = *tableptr;
			*tableptr = (*tableptr)->lptr;		// go left
			mfree(auxPtr);				// delete current node
		}

	} while (*tableptr != NULL || (!StackIsEmpty(&s)));
}

void FTRemove (tFTItemPtr* tableptr, char* token)
{
	if ((*tableptr) == NULL)						// Empty tree
	{
		return;
	}
	else if (((*tableptr)->data) == token)				// Node is one To delete
	{

		if ((((*tableptr)->lptr) == NULL) && (((*tableptr)->rptr) == NULL)) 		// Have no children
		{
			mfree(*tableptr);
			*tableptr = NULL;
			return;
		}

		else if (((*tableptr)->lptr) == NULL)	// Have right child
		{
			tFTItemPtr child = (*tableptr)->rptr;
			mfree(*tableptr);
			*tableptr = child;
		}
		else if (((*tableptr)->rptr) == NULL)	// Have left child
		{
			tFTItemPtr child = (*tableptr)->lptr;
			mfree(*tableptr);
			*tableptr = child;
		}
		else									// have both children
		{
			ReplaceByRightmost((*tableptr), &((*tableptr)->lptr));
		}
	}
	else if ((*tableptr)->data >= token)				// Key is smaller
	{
		FTRemove(&((*tableptr)->lptr), token);
	}
	else										// Key is Bigger
	{
		FTRemove(&((*tableptr)->rptr), token);
	}
	return;
}