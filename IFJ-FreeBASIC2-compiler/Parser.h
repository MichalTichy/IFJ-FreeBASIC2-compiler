#include "Basics.h"
#include "Scanner.h"

typedef enum  {
	TYPE_Integer,
	TYPE_Double,
	TYPE_String
} ScalarType;

typedef enum  {
	integerVal,
	doubleVal,
	stringVal,
	varDeclaration,
	expression
}NodeType;

typedef struct NodeInteger
{
	long int value;
} tNodeInteger;

typedef struct NodeDouble
{
	double value;
} tNodeDouble;

typedef struct NodeString
{
	char* value;
	int lenght;
} tNodeString;

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
		struct NodeInteger* intValue;
		struct NodeDouble* doubleValue;
		struct NodeString* stringValue;
		struct NodeExpression* expression;
	} tData;
}tNode;

void Parse();

void Next();

void Back();

void BackMultipleTimes(int steps);

tNode * ProcessNumber();
tNode* ProcessDouble();

tNode * ProcessInteger();

tNode * InitIntegerNode(long int value);

tNode* InitDoubleNode(double value);

tNode* IniStringNode(char* value, int lenght);

tNode * InitVarDeclarationNode();

tNode * ProcessVarDeclaration();

ScalarType TokenTypeToScalarType(TokenType tokenType);
