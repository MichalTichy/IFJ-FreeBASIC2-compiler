#pragma once
#ifndef SYMTABLE
#define SYMTABLE

#include "Parser.h"


typedef struct tSTItem
{
	TokenType type;
	char* data;
	unsigned int len;
	struct tSTItem* lptr;
	struct tSTItem* rptr;
} *tSTItemPtr;

typedef struct tSTScope
{
	tSTItemPtr symtable;
	struct tSTScope* parentScope;
} *tSTScopePtr;


void STInit(tSTItemPtr* tableptr);

tSTItemPtr STSearch (tSTItemPtr* tableptr, char* key);

void STInsert (tSTItemPtr* tableptr, char* key);

void STFree (tSTItemPtr* tableptr);

void STMakeScope(tSTScopePtr* scope, tSTScopePtr parentScope); // make scope with link to parent scope

tSTItemPtr STScopeSearch(tSTScopePtr* scope, char* key); // Search in all scopes

void STScopeInsert(tSTScopePtr* scope, char* key); // insert into top scope

void STDeleteTopScope(tSTScopePtr* scope); // Delete top scope


#endif // ifndef SYMTABLE