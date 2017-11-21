#include "Basics.h"
#include "Scanner.h"

typedef enum  {
	TYPE_Integer,
	TYPE_Double,
	TYPE_String
} ScalarType;

typedef enum  {
	integer,
	varDeclaration,
	expression
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
	ScalarType varType;
	tNodeExpression* Expression;

} tNodeVariableDeclaration;


typedef struct Node
{
	NodeType type;
	union Data
	{
		struct NodeVariableDeclaration variable_declaration;
		struct NodeInteger* integer;
		struct NodeExpression* expression;
	} tData;
}tNode;

void Parse();

void Next();

void Back();

void BackMultipleTimes(int steps);

tNode * ProcessNumber();

tNode * ProcessInteger();

tNode * InitIntegerNode(int value);

tNode * InitVarDeclarationNode();

tNode * ProcessVarDeclaration();

ScalarType TokenTypeToScalarType(TokenType tokenType);
