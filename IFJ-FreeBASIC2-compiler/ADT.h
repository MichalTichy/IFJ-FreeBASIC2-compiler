#ifndef ADT
#define ADT

#include "precedens.h"
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


#endif // !ADT



