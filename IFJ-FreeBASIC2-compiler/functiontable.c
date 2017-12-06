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
#include "errors.h"
#include <string.h>
#include "ManagedMalloc.h"
#include "ADT.h"

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

