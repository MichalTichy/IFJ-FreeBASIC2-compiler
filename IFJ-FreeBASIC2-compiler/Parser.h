#include "Basics.h"
#include "Scanner.h"

typedef enum  {
	integer,
	varDeclaration
}NodeType;

typedef struct NodeInteger
{
	int value;
} tNodeInteger;

typedef struct NodeExpression
{
	//todo 

} tNodeExpression;

typedef struct NodeVariableDeclaration
{
	//todo pointer to ID
	//todo TYPE DEFINITION
	tNodeExpression* Expression;

} tNodeVariableDeclaration;


typedef struct Node
{
	NodeType type;
	union Data
	{
		struct NodeVariableDeclaration variable_declaration;
		struct NodeInteger* integer;
	} tData;
}tNode;

void Parse();

void Next();

void Back();

tNode * ProcessNumber();

tNode * ProcessInteger();

tNode * InitIntegerNode(int value);

tNode * InitVarDeclarationNode();

tNode * ProcessVarDeclaration();
