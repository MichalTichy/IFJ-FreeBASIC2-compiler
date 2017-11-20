#ifndef ADT
#define ADT

#include "precedens.h"

//--STACK
TStack_t *StackInit(TStack_t * stack);
void StackDestroy(TStack_t * stack);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	precedensTableToken token;
	BTreeNode_t *  bTreeNode;
	unsigned int StackIndex;

} TStackItem_t;

typedef struct stack
{
	TStackItem_t * items;
	int maxSize;
	int actualSize;
} TStack_t;



//--BinaryTree



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct 
{
	BTreeNode_t *parentPtr;
	BTreeNode_t *leftPtr;
	BTreeNode_t *rightPtr;
	SymbolTableData_t data;
}BTreeNode_t;






//--ConstantTable
#define CONSTANT_TABLE_SIZE 128

ConstantTable_t * ConstantTableInit();
void ConstantTableDestroy(ConstantTable_t *);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct
{
	ConstOrSymbT_dataType value;
	SymbolTableType_t type;
}ConstTableItem_t;

typedef struct
{
	ConstTableItem_t* items;
	unsigned int iterator;
	unsigned int maxSize;
}ConstantTable_t;


//--CONSTANT or SYMBOL table data type
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef union 
{
	void * placeholder;
	int * placeholder2;
}ConstOrSymbT_dataType;


//-- symbolTable
#define SYMBOL_TABLE_ARRAY_SIZE 256


SymbolTable_t * SymbolTableInit(void);
BTreeNode_t * SymbolTableInsert(SymbolTable_t * symbolTable, ConstantTable_t * constantTable, SymbolTableData_t symbolTableData);
BTreeNode_t * SymbolTableSearch(SymbolTable_t * symbolTable, ConstantTable_t * constantTable);
void SymbolTableDestroy(SymbolTable_t *);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum 
{
	void * placeholder,
	void * placeholder2,

}SymbolTableType_t;

typedef struct
{
	char * namePtr;
	unsigned int symTableArrayIndex;
	SymbolTableType_t type;
	ConstOrSymbT_dataType value;
	unsigned int constTableIndex;
	unsigned int stackIndex;
	int loaded;
}SymbolTableData_t;

typedef struct
{
	BTreeNode_t * root;
	char * IdArray;
	unsigned int allocatedLenght;
	unsigned int arrayIndex;
	unsigned int assignedVarCount;
}SymbolTable_t;

//-- symbolTableArray
int GL_SYMBOLTABLE_COUNT_MAX;
SymbolTable_t ** SymbolTable_ArrayInit()
SymbolTable_t ** SymbolTable_ArrayRealloc();
void SymbolTable_Array_destroy;



//--3AK list


typedef struct
{
	instructionType instructionType;
	unsigned int src1;
	unsigned int src2;
	unsigned int src3;
};

#endif // !ADT



