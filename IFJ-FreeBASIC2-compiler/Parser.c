#include "errors.h"
#include "ADT.h"
#include "parser.h"

ERR_CODE Parse()
{

	TStack_t *precedensStack = StackInit();
	if (precedensStack == NULL) return INTERNAL_ERR;

	Gl_constant_table = ConstantTableInit();
	if (Gl_constant_table == NULL)
	{
		StackDestroy(&precedensStack);
		return INTERNAL_ERR;
	}

	GL_SYMBOLTABLE_COUNT_MAX = 16;
	SymbolTable_t ** symbolTableArray = SymbolTable_ArrayInit();
	if (symbolTableArray == NULL)
	{
		ConstantTableDestroy(&Gl_constant_table);
		StackDestroy();
	}



}