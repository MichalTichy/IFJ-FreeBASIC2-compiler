#ifndef ADT
#define ADT

#include "precedens.h"

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
#define SYMBOL_TABLE_ARRAY_SIZE 256


struct SymbolTable_t * SymbolTableInit(void);
BTreeNode_t * SymbolTableInsert(struct SymbolTable_t * symbolTable, struct ConstantTable_t * constantTable, struct SymbolTableData_t symbolTableData);
BTreeNode_t * SymbolTableSearch(struct SymbolTable_t * symbolTable, struct ConstantTable_t * constantTable);
void SymbolTableDestroy(struct SymbolTable_t *);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum 
{
	placeholder3,
	placeholder4,

}SymbolTableType_t;



struct SymbolTableData_t
{
	char * namePtr;
	unsigned int symTableArrayIndex;
	SymbolTableType_t type;
	struct ConstOrSymbT_dataType *value;
	unsigned int constTableIndex;
	unsigned int stackIndex;
	int loaded;
};

typedef struct SymbolTable_t SymbolTable_t;

struct SymbolTable_t
{
	BTreeNode_t * root;
	char * IdArray;
	unsigned int allocatedLenght;
	unsigned int arrayIndex;
	unsigned int assignedVarCount;
};




//--STACK

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	precedensTableToken token;
	BTreeNode_t *  bTreeNode;
	unsigned int StackIndex;

} TStackItem_t;

typedef struct TStack_t
{
	TStackItem_t * items;
	int maxSize;
	int actualSize;
} TStack_t;

TStack_t *StackInit(TStack_t * stack);
void StackDestroy(TStack_t * stack);



//--ConstantTable
#define CONSTANT_TABLE_SIZE 128

struct ConstantTable_t * ConstantTableInit();
void ConstantTableDestroy(struct ConstantTable_t *);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct
{
	struct ConstOrSymbT_dataType *value;
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



//-- symbolTableArray
int GL_SYMBOLTABLE_COUNT_MAX;
SymbolTable_t ** SymbolTable_ArrayInit();
SymbolTable_t ** SymbolTable_ArrayRealloc();
void SymbolTable_Array_destroy();



//--3AK list


typedef struct
{
	//instructionType instructionType;
	unsigned int src1;
	unsigned int src2;
	unsigned int src3;
};

#endif // !ADT



