#include <stdlib.h>
#include <string.h>

#include "ADT.h"
#include "ManagedMalloc.h"
#include "SymTable.h"
#include "errors.h"


void STInit(tSTItemPtr* tableptr)
{
	*tableptr = NULL;
}

tSTItemPtr STSearch(tSTItemPtr* tableptr, char* token)
{
	tSTItemPtr itemPtr = *tableptr;
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

void STInsert(tSTItemPtr* tableptr, char* token)
{	
	if (tableptr == NULL)
	{
		return;
	}
	tSTItemPtr* itemPtr = tableptr;
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
	*itemPtr = mmalloc(sizeof(struct tSTItem));
	if ((*itemPtr) == NULL)
	{
		mfreeall();
		ERR_CODE code = INTERNAL_ERR;
		exit(code);
	}
	else
	{
		(*itemPtr)->len = (unsigned)strlen(token);
		(*itemPtr)->data = token;
		(*itemPtr)->lptr = NULL;
		(*itemPtr)->rptr = NULL;
	}

}

void STFree(tSTItemPtr* table)
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

	} while (*table != NULL || (!StackIsEmpty(&s)));
}

void STMakeScope(tSTScopePtr * scope, tSTScopePtr parentScope)
{
	if (scope == NULL)
		return;

	*scope = mmalloc(sizeof(struct tSTScope));
	if ((scope) == NULL)
	{
		mfreeall();
		ERR_CODE code = INTERNAL_ERR;
		exit(code);
	}
	(*scope)->symtable = NULL;
	(*scope)->parentScope = parentScope;
}

tSTItemPtr STScopeSearch(tSTScopePtr* scope, char* key)
{
	if (scope == NULL)
		return NULL;

	tSTScopePtr currScopePtr = *scope;
	tSTItemPtr item = NULL;
	while (currScopePtr != NULL)
	{
		item = STSearch(&(currScopePtr->symtable), key);

		if (item != NULL)
			break;

		currScopePtr = currScopePtr->parentScope;
	}
	return item;
}

void STScopeInsert(tSTScopePtr* scope, char* key)
{
	STInsert(&((*scope)->symtable), key);
}

void STDeleteTopScope(tSTScopePtr* scope)
{
	STFree((&(*scope)->symtable));
	mfree(*scope);
	*scope = NULL;
}

