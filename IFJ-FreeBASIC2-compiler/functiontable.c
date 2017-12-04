#include "functiontable.h"
#include <stdlib.h>
#include "errors.h"
#include <string.h>
#include "ManagedMalloc.h"
#include "ADT.h"

void ReplaceByRightmost(tFTItemPtr PtrReplaced, tFTItemPtr* RootPtr) 
{
	if ((*RootPtr)->rptr == NULL)		// Is the Rightmost
	{
		PtrReplaced->data = (*RootPtr)->data;
		PtrReplaced->len = (*RootPtr)->len;
		PtrReplaced->parametersMax = (*RootPtr)->parametersMax;
		PtrReplaced->parametersCount = (*RootPtr)->parametersCount;
		PtrReplaced->returnValue = (*RootPtr)->returnValue;
		PtrReplaced->parametersArr = (*RootPtr)->parametersArr;
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

tFTItemPtr FTInsert(tFTItemPtr* tableptr, char* token, bool isDeclaration)
{
	if (tableptr == NULL)
	{
		exitSecurely(INTERNAL_ERR);
		return NULL;
	}
	tFTItemPtr* itemPtr = tableptr;
	while ((*itemPtr) != NULL)
	{
		if (strcmp((*itemPtr)->data, token) == 0)			// Token is here
		{
			if ((*itemPtr)->declarationOnly && !isDeclaration)
			{
				(*itemPtr)->declarationOnly = false;
				return *itemPtr;
			}
			else
			{
				exitSecurely(SEMANT_ERR_DEF);
				return NULL;
			}
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
		(*itemPtr)->declarationOnly = isDeclaration;
		(*itemPtr)->parametersArr = mmalloc(sizeof(tParam) * 5);
		if ((*itemPtr)->parametersArr == NULL)
		{
			exitSecurely(INTERNAL_ERR);
		}
		(*itemPtr)->parametersMax = 5;
		(*itemPtr)->parametersCount = 0;
		(*itemPtr)->lptr = NULL;
		(*itemPtr)->rptr = NULL;
	}
	return *itemPtr;
}

void AddParemeter(tFTItemPtr* funItem, char* name, ScalarType type)
{
	tFTItemPtr item = FTSearch(funItem, name);
	if (item == NULL)
		exitSecurely(SEMANT_ERR_DEF);

	if (item->parametersMax <= item->parametersCount)
	{
		(*funItem)->parametersArr = mrealloc((*funItem)->parametersArr, sizeof(tParam) * ((*funItem)->parametersMax + 5));
		if ((*funItem)->parametersArr == NULL)
		{
			exitSecurely(INTERNAL_ERR);
		}
		item->parametersMax = item->parametersMax + 5;
	}

	(item->parametersArr[item->parametersCount]).name = name;
	item->parametersCount = item->parametersCount + 1;
	(item->parametersArr[item->parametersCount]).type = type;
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

void AddReturnValue(tFTItemPtr* funItem, char* name, ScalarType type)
{
	tFTItemPtr item = FTSearch(funItem, name);
	if (item == NULL)
		exitSecurely(INTERNAL_ERR);
	item->returnValue = type;
}

void CompareParameterSignature(tFTItemPtr item, unsigned int position, char* name, ScalarType type)
{
	if (strcmp((item->parametersArr[position]).name, name) == 0)
	{
		if ((item->parametersArr[position]).type == type)
		{
			return;
		}
	}
	exitSecurely(SEMANT_ERR_DEF);
	return;
}