/**
*	Project: IFJ17 Compiler
*
*	FILE: symtable.h
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

#pragma once
#ifndef SYMTABLE
#define SYMTABLE

#include "Parser.h"
#include "Basics.h"

typedef struct tSTItem
{
	ScalarType type;
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

void STMakeFunciontScope(tSTScopePtr* tableptr, tSTScopePtr parentScope);

tSTItemPtr STSearch(tSTItemPtr* tableptr, char* key);

void STInsert(tSTItemPtr* tableptr, char* key, ScalarType type);

void STFree(tSTItemPtr* tableptr);

void STMakeScope(tSTScopePtr* scope, tSTScopePtr parentScope); // make scope with link to parent scope

tSTItemPtr STScopeSearch(tSTScopePtr* scope, char* key); // Search in all scopes

void STScopeInsert(tSTScopePtr* scope, char* key, ScalarType type); // insert into top scope

void STDeleteTopScope(tSTScopePtr* scope); // Delete top scope

void STScopeInsertTop(tSTScopePtr* scope, char* key, ScalarType type);


#endif // ifndef SYMTABLE
