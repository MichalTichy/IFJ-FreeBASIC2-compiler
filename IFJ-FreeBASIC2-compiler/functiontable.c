#include "functiontable.h"
#include <stdlib.h>
#include <stdio.h>
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

	tFTItemPtr item = FTInsert(tableptr, "length",false);
	AddParemeter(item, "s", TYPE_String);
	AddReturnValue(item, TYPE_Integer);

	item = FTInsert(tableptr, "substr", false);
	AddParemeter(item, "s", TYPE_String);
	AddParemeter(item, "i", TYPE_Integer);
	AddParemeter(item, "n", TYPE_Integer);
	AddReturnValue(item, TYPE_String);

	item = FTInsert(tableptr, "chr", false);
	AddParemeter(item, "i", TYPE_Integer);
	AddReturnValue(item, TYPE_String);

	item = FTInsert(tableptr, "asc", false);
	AddParemeter(item, "s", TYPE_String);
	AddParemeter(item, "i", TYPE_Integer);
	AddReturnValue(item, TYPE_Integer);
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
		(*itemPtr)->parametersArr = mmalloc(sizeof(tParam) * 30);
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

void AddParemeter(tFTItemPtr itemptr, char* paramName, ScalarType type)
{
	if (itemptr == NULL)
		exitSecurely(SEMANT_ERR_DEF);

	if (itemptr->parametersMax <= itemptr->parametersCount)
	{
		unsigned int size = itemptr->parametersMax;
		tParam* Array = itemptr->parametersArr;
		tParam* newArr = (tParam*)realloc(Array, sizeof(struct tParamStruct) * (size + 5));
		if (newArr == NULL)
		{
			exitSecurely(INTERNAL_ERR);
		}
		itemptr->parametersArr = newArr;
		itemptr->parametersMax = itemptr->parametersMax + 5;
	}

	(itemptr->parametersArr[itemptr->parametersCount]).name = paramName;
	itemptr->parametersCount = itemptr->parametersCount + 1;
	(itemptr->parametersArr[itemptr->parametersCount]).type = type;
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

void AddReturnValue(tFTItemPtr itemptr, ScalarType type)
{
	if (itemptr == NULL)
	{
		exitSecurely(INTERNAL_ERR);
	}
	itemptr->returnValue = type;
}

void CompareParameterSignature(tFTItemPtr item, unsigned int position, char* name, ScalarType type)
{
	if (position>=item->parametersCount)
	{
		exitSecurely(SEMANT_ERR_TYPE);
		return;
	}

	if (strcmp((item->parametersArr[position]).name, name) == 0)
	{
		if ((item->parametersArr[position]).type == type)
		{
			return;
		}
	}
	exitSecurely(SEMANT_ERR_TYPE);
	return;
}

bool FTIsDefinitionOnly(tFTItemPtr* tablePtr)
{
	TStack_t s;
	StackInit(&s);

	do
	{
		if ((*tablePtr) == NULL)			// take node from stack
		{
			if (!StackIsEmpty(&s))
			{
				*tablePtr = StackTopPop(&s);
			}
		}
		else							// move right to stack
		{
			if ((*tablePtr)->rptr != NULL)
			{
				StackPush(&s, (*tablePtr)->rptr);
			}
			if ((*tablePtr)->declarationOnly)
			{
				return false;
			}
			*tablePtr = (*tablePtr)->lptr;		// go left
		}

	} while (*tablePtr != NULL || (!StackIsEmpty(&s)));

	return true;
}