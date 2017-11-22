#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "Symtable.h"


void STInit(tSTable* table)
{
	table->first = NULL;
}

tSTItem* STSearch(tSTable* table, tToken* token)
{
	tSTItem* itemPtr = table->first;
	while (itemPtr != NULL)
	{
		if (strcmp(itemPtr->data->String, token->String) == 0)
		{
			break;
		}
		else if (strcmp(itemPtr->data->String, token->String) < 0)		// Token is bigger
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

void STInsert(tSTable* table, tToken* token)
{	
	tSTItem** itemPtr = &(table->first);
	while (itemPtr != NULL)
	{
		if (strcmp((*itemPtr)->data->String, token->String) == 0)
		{
			break;
		}
		else if (strcmp((*itemPtr)->data->String, token->String) < 0)		// Token is bigger
		{
			itemPtr = &((*itemPtr)->rptr);
		}
		else		// Token is smaller
		{
			itemPtr = &((*itemPtr)->lptr);
		}
	}
	*itemPtr = malloc(sizeof(tSTItem));
	if ((*itemPtr) == NULL)
	{
		// dodelat error
	}
	else
	{
		(*itemPtr)->data = token;
		(*itemPtr)->lptr = NULL;
		(*itemPtr)->rptr = NULL;
	}
}

void STFree(tSTItem* table) // potreba zrusit datovy typ tSTable
{
	if (table == NULL)
		return;
	STFree(table->lptr);
	STFree(table->rptr);
	free(table);
}