#include "functiontable.h"
#include <stdlib.h>
#include "errors.h"
#include <string.h>
#include "ManagedMalloc.h"
#include "ADT.h"

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

void FTInsert(tFTItemPtr* tableptr, char* token, char** parameters)
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
		(*itemPtr)->parameters = parameters;
		(*itemPtr)->lptr = NULL;
		(*itemPtr)->rptr = NULL;
	}
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