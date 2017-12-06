/**
*	Project: IFJ17 Compiler
*
*	FILE: ADT.h
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


#ifndef ADT
#define ADT

#include "precedens.h"
#include "Parser.h"
#include <stdbool.h>

typedef struct BTreeNode_t BTreeNode_t;
typedef struct SymbolTableData_t SymbolTableData_t;

//--BinaryTree



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



struct BTreeNode_t
{
	BTreeNode_t *parentPtr;
	BTreeNode_t *leftPtr;
	BTreeNode_t *rightPtr;
	struct SymbolTableData_t *data;
};

//-- symbolTable

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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

// todo move symtable def. here

//--STACK

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DEFAULT_STACK_SIZE 128

typedef struct TStack_t
{
	void ** items;
	unsigned int maxSize;
	unsigned int actualSize;
} TStack_t;

void StackInit(TStack_t * stack);
bool StackIsEmpty(TStack_t * stack);
void* StackTopPop(TStack_t * stack);
void StackPush(TStack_t * stack, void * ptr);
void StackDestroy(TStack_t * stack);
void* StackTop(TStack_t * stack);

//--FUNCTION TABLE

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct tParamStruct
{
	char* name;
	ScalarType type;
} tParam;

typedef struct tFTItem
{
	tParam* parametersArr;
	char* data;
	bool declarationOnly;
	struct Function* body;
	unsigned int parametersCount;
	unsigned int parametersMax;
	unsigned int len;
	ScalarType returnValue;
	struct tFTItem* lptr;
	struct tFTItem* rptr;
} *tFTItemPtr;

void FTInit(tFTItemPtr* tableptr);

tFTItemPtr FTSearch(tFTItemPtr* tableptr, char* token);

void AddParemeter(tFTItemPtr itemptr, char* paramName, ScalarType type);

void AddReturnValue(tFTItemPtr itemptr, ScalarType type);

tFTItemPtr FTInsert(tFTItemPtr* tableptr, char* token, bool isDeclaration);

void FTRemove(tFTItemPtr* funItem, char* token);

void FTFree(tFTItemPtr* tableptr);

bool FTIsDefinitionOnly(tFTItemPtr* tablePtr);
#endif // !ADT




