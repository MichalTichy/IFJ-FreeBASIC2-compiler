#pragma once
#ifndef SYMTABLE
#define SYMTABLE

#include "Token.h"


typedef struct tSTItem
{
	tToken* data;
	struct tSTItem* lptr;
	struct tSTItem* rptr;
} tSTItem;

typedef struct // potreba zrusit
{
	tSTItem* first;
} tSTable;

void STInit(tSTable* table);
tSTItem* STSearch(tSTable* table, tToken* token);
void STInsert(tSTable* table, tToken* token);
void STFree(tSTItem* table);

#endif // ifndef SYMTABLE