/**
*	Project: IFJ17 Compiler
*
*	FILE: functiontable.h
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

//--STACK

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StackInit(TStack_t * stack)
/**
 * Function initializises stack
 * should be used only once!
 * @param tableptr is pointer to stack
**/
{
	if (stack == NULL)						// Invalid pointer
	{
		exitSecurely(INTERNAL_ERR);
	}
	void ** itemPtr = mmalloc(sizeof(void*)*DEFAULT_STACK_SIZE);	// maloc stack
	if ((itemPtr) == NULL)
	{
		mfreeall();
		ERR_CODE code = INTERNAL_ERR;
		exit(code);
	}
	stack->items = itemPtr;					// Init values
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

	if (stack->actualSize == 0)	// empty stack
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
	if (stack == NULL) // invalid ptr
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
		return stack->items[stack->actualSize-1];
	}
	return NULL;
}

//-- symbolTable

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void STInit(tSTItemPtr* tableptr)		// should be called only once
/**
* Function initializes pointer to first element of table to null
* should be used only once for table
* @param tableptr is pointer to pointer to root of table
**/
{
	*tableptr = NULL;					// set pointer to null
}

tSTItemPtr STSearch(tSTItemPtr* tableptr, char* token)
/**
* Function search in symtable, if found returns pointer to item
* if not return NULL
* @param tableptr is pointer to pointer root of table
* @param token is string with keyword
* @return item in table
* tableptr
**/
{
	tSTItemPtr itemPtr = *tableptr;
	while (itemPtr != NULL)
	{
		if (strcmp(itemPtr->data, token) == 0)			// if its token you are looking for
		{
			break;
		}
		else if (strcmp(itemPtr->data, token) < 0)		// Token is bigger
		{
			itemPtr = itemPtr->rptr;
		}
		else											// Token is smaller
		{
			itemPtr = itemPtr->lptr;
		}
	}
	return itemPtr;
}

void STInsert(tSTItemPtr* tableptr, char* token, ScalarType type)
/**
* Function inserts element into symtable, if exist exit with SEMANT_ERR_DEF
* @param tableptr is pointer to pointer to root of table
* @param token is string with keyword
* @param type is data type of the symbol
**/
{
	if (tableptr == NULL)									// empty table
	{
		return;
	}
	tSTItemPtr* itemPtr = tableptr;
	while ((*itemPtr) != NULL)
	{
		if (strcmp((*itemPtr)->data, token) == 0)			// Token is here
		{
			exitSecurely(SEMANT_ERR_DEF);					// error inserting existing symbol
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
	*itemPtr = mmalloc(sizeof(struct tSTItem));				// alloc new item
	if ((*itemPtr) == NULL)
	{
		exitSecurely(INTERNAL_ERR);
	}
	else
	{
		(*itemPtr)->len = (unsigned)strlen(token);			// initialize item
		(*itemPtr)->data = token;
		(*itemPtr)->type = type;
		(*itemPtr)->lptr = NULL;
		(*itemPtr)->rptr = NULL;
	}

}

void STFree(tSTItemPtr* table)
/**
* Function STFree destroys whole tree and free its items
* @param tableptr is pointer to pointer to root of table
**/
{
	TStack_t s;
	StackInit(&s);						// init stack of pointers
	do
	{
		if ((*table) == NULL)			// take node from stack
		{
			if (!StackIsEmpty(&s))
			{
				*table = StackTopPop(&s);
			}
		}
		else							// move right to stack
		{
			if ((*table)->rptr != NULL)
			{
				StackPush(&s, (*table)->rptr);
			}
			tSTItemPtr auxPtr = *table;
			*table = (*table)->lptr;		// go left
			mfree(auxPtr);				// delete current node
		}

	} while (*table != NULL || (!StackIsEmpty(&s))); // till stack is empty and you have null
}

//--FUNCTION TABLE

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
		if (strcmp((*itemPtr)->data, token) == 0)		// Token is here
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

	} while (*tableptr != NULL || (!StackIsEmpty(&s)));	// till stack is not empty and pointer is not NULL
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