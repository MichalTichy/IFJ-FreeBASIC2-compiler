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

#include <stdlib.h>
#include <string.h>

#include "ADT.h"
#include "ManagedMalloc.h"
#include "SymTable.h"
#include "errors.h"




void STMakeScope(tSTScopePtr * scope, tSTScopePtr parentScope)
/**
 * Makes new scope, alocates new symbol table
 * @param scope is pointer to scope
 * @param parentScope is parent scope
 **/
{
	if (scope == NULL)	// null ptr
		return;

	*scope = mmalloc(sizeof(struct tSTScope));	// malloc new scope
	if ((scope) == NULL)
	{
		mfreeall();
		ERR_CODE code = INTERNAL_ERR;
		exit(code);
	}
	(*scope)->symtable = NULL;					// set symtable
	(*scope)->parentScope = parentScope;		// set parent scope
}

tSTItemPtr STScopeSearch(tSTScopePtr* scope, char* key)
/**
 * Search symbol in scope if not found search higer scopes,
 * returns item or exits with SEMANT_ERR_DEF
 * @param scope is pointer to scope
 * @param key is string with keyword
 * @return pointer to item
 **/
{
	if (scope == NULL)				// invalid ptr
		return NULL;

	tSTScopePtr currScopePtr = *scope;
	tSTItemPtr item = NULL;
	while (currScopePtr != NULL)	// go throw all scopes
	{
		item = STSearch(&(currScopePtr->symtable), key);	// search

		if (item != NULL)			// if you found
			return item;

		currScopePtr = currScopePtr->parentScope;
	}

	exitSecurely(SEMANT_ERR_DEF);	// error, not found
	return NULL;
}

void STScopeInsert(tSTScopePtr* scope, char* key, ScalarType type)
/**
 * Inserts symbol into scope
 * @param scope is pointer to pointer to scope
 * @param key is string with keyword
 * @param type is data type of the symbol
 **/
{
	STInsert(&((*scope)->symtable), key, type);
}

void STScopeInsertTop(tSTScopePtr* scope, char* key, ScalarType type)
/**
* Inserts symbol into top scope
* @param scope is pointer to pointer to scope
* @param key is string with keyword
* @param type is data type of the symbol
**/
{
	if (scope == NULL)			// invalid ptr
	{
		exitSecurely(INTERNAL_ERR);
	}
	tSTScopePtr scopeptr = *scope;
	if (scopeptr == NULL)		// no scope
	{
		exitSecurely(INTERNAL_ERR);
	}
	tSTScopePtr previousScope;
	while (scopeptr != NULL)	// go to top scope
	{
		previousScope = scopeptr;
		scopeptr = scopeptr->parentScope;
	}

	STInsert(&(previousScope->symtable), key, type);	// Insert
}

void STDeleteTopScope(tSTScopePtr* scope)
/**
 * Function deletes scope you are pointing to.
 * It must be scope no scpoe is pointing to!
 * @param scope is pointer to pointer to scope you want to delete
 **/
{
	STFree((&(*scope)->symtable));
	mfree(*scope);
	*scope = NULL;
}

void STMakeFunciontScope(tSTScopePtr* tablescope, tSTScopePtr parentScope)
/**
* Makes scope for variables for function, allocates new symtable
* @param scope is pointer to scope
* @param parentScope is parent scope
**/
{
	if (parentScope == NULL)		// Invalid scope
	{
		exitSecurely(INTERNAL_ERR);
	}
	tSTScopePtr previousScope;
	while (parentScope != NULL)		// Go to top scope
	{
		previousScope = parentScope;
		parentScope = parentScope->parentScope;
	}
	STMakeScope(tablescope, previousScope);	// Make scope
}

