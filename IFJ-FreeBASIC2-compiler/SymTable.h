/**
*	Project: IFJ17 Compiler
*
*	FILE: symtable.c
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

#include "Scanner.h"
#include "Basics.h"
#include "ADT.h"


void STMakeScope(tSTScopePtr* scope, tSTScopePtr parentScope); // make scope with link to parent scope

tSTItemPtr STScopeSearch(tSTScopePtr* scope, char* key); // Search in all scopes

void STScopeInsert(tSTScopePtr* scope, char* key, ScalarType type); // insert into top scope

void STDeleteTopScope(tSTScopePtr* scope); // Delete top scope

void STScopeInsertTop(tSTScopePtr* scope, char* key, ScalarType type);


#endif // ifndef SYMTABLE
