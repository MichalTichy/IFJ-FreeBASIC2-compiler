/**
*	Project: IFJ17 Compiler
*
*	FILE: functiontable.c
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

#include "functiontable.h"
#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include <string.h>
#include "ManagedMalloc.h"
#include "ADT.h"

void ReplaceByRightmost(tFTItemPtr PtrReplaced, tFTItemPtr* RootPtr)
/**
* Replaces item PtrReplaced with rightmost item, destroys rightmost item
* @param PtrRreplaced is pointer to item we want to replace
* @param RootPtr is pointer to root item
**/
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
		ReplaceByRightmost(PtrReplaced, &((*RootPtr)->rptr)); // continue recursivly
	}
}

void FTInit(tFTItemPtr* tableptr)
/**
* Function initializes pointer to first element of table to null
* should be used only once for table, inserts
* @param tableptr is pointer to pointer to root of table
**/
{
	*tableptr = NULL;

	tFTItemPtr item = FTInsert(tableptr, "length", false);
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
/**
* Function search in function table, if found returns pointer to item
* if not returns NULL
* @param tableptr is pointer to pointer to root of table
* @param token is string with keyword
* @return item in table
**/
{
	tFTItemPtr itemPtr = *tableptr;
	while (itemPtr != NULL)
	{
		if (strcmp(itemPtr->data, token) == 0)		// Token is here
		{
			break;
		}
		else if (strcmp(itemPtr->data, token) < 0)	// Token is bigger
		{
			itemPtr = itemPtr->rptr;
		}
		else										// Token is smaller
		{
			itemPtr = itemPtr->lptr;
		}
	}
	return itemPtr;
}

tFTItemPtr FTInsert(tFTItemPtr* tableptr, char* token, bool isDeclaration)
/**
* Function inserts element into function table, if exist exit with SEMANT_ERR_DEF
* @param tableptr is pointer to pointer to root of table
* @param token is string with keyword
* @param isDeclaration determines if its declaration or definition
* @return pointer to inserted item
**/
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
			if ((*itemPtr)->declarationOnly && !isDeclaration)	// is item defined or declared again?
			{
				return *itemPtr;
			}
			else
			{
				exitSecurely(SEMANT_ERR_DEF);
				return NULL;
			}
		}
		else if (strcmp((*itemPtr)->data, token) < 0)	// Token is bigger
		{
			itemPtr = &((*itemPtr)->rptr);
		}
		else											// Token is smaller
		{
			itemPtr = &((*itemPtr)->lptr);
		}
	}
	*itemPtr = mmalloc(sizeof(struct tFTItem));			// malloc token
	if ((*itemPtr) == NULL)
	{
		exitSecurely(INTERNAL_ERR);
	}
	else												// initializate item
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
/**
* Function adds parameter to function if function
* doesnt exist exits with SEMANT_ERR_DEF
* @param itemptr is pointer to item
* @param paramName is string with name of parameter
* @param type is data type of the parameter
**/
{
	if (itemptr == NULL)	// invalid pointer
		exitSecurely(SEMANT_ERR_DEF);

	if (itemptr->parametersMax <= itemptr->parametersCount)					// not enough space
	{
		unsigned int size = itemptr->parametersMax;
		tParam* Array = itemptr->parametersArr;
		tParam* newArr = (tParam*)realloc(Array, sizeof(struct tParamStruct) * (size + 5)); // realoc
		if (newArr == NULL)
		{
			exitSecurely(INTERNAL_ERR);
		}
		itemptr->parametersArr = newArr;
		itemptr->parametersMax = itemptr->parametersMax + 5;
	}

	(itemptr->parametersArr[itemptr->parametersCount]).name = paramName;	// add parameter
	(itemptr->parametersArr[itemptr->parametersCount]).type = type;

	itemptr->parametersCount = itemptr->parametersCount + 1;
}

void FTFree(tFTItemPtr* tableptr)
/**
* Function FTFree destroys whole tree and free its items
* @param tableptr is pointer to pointer to root of table
**/
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

void FTRemove(tFTItemPtr* tableptr, char* token)
/**
* Function FTRemove removes item from table, if it have both childs
* its replaced with rightmost item
* @param tableptr is pointer to pointer to root of table
* @param token is name of function to be replaced
**/
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
/**
* Function adds return value to function
* @param itemptr is pointer to item
* @param type is return type
**/
{
	if (itemptr == NULL)
	{
		exitSecurely(INTERNAL_ERR);
	}
	itemptr->returnValue = type;
}

void CompareParameterSignature(tFTItemPtr item, unsigned int position, char* name, ScalarType type)
/**
* Function compares parameter in function on given position
* if position is bigger than number of parameters or parameter
* is not as expected exits with SEMANT_ERR_DEF
* @param item is pointer to function item
* @param position is position of parameter
* @param name is ame of parameter
* @param type is data type of parameter
**/
{
	if (position >= item->parametersCount)	// invalid position
	{
		exitSecurely(SEMANT_ERR_DEF);
		return;
	}

	if (strcmp((item->parametersArr[position]).name, name) == 0)  // compare name
	{
		if ((item->parametersArr[position]).type == type)	// compare type
		{
			return;
		}
	}
	exitSecurely(SEMANT_ERR_DEF);
	return;
}

bool FTIsDefinitionOnly(tFTItemPtr* tablePtr)
/**
* Function chack if in the tree is function with definition only
* if there is exits with SEMANT_ERR_DEF
* @param tableptr is pointer to pointer to root of table
**/
{
	TStack_t s;
	StackInit(&s);

	do
	{
		if ((*tablePtr) == NULL)		// take node from stack
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
				return false;			// there is function without definition
			}
			*tablePtr = (*tablePtr)->lptr;		// go left
		}

	} while (*tablePtr != NULL || (!StackIsEmpty(&s))); // till stack is empty or tableptr is null

	return true;						// all functions defined
}