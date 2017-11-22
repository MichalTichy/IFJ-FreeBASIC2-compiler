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
	varAssigment,
	expression,
	scope,
	statement,
	ifCondition,
	elseIfCondition,
	whileBlock
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

typedef struct NodeVariableAssigment
{
	//todo pointer to ID
	ScalarType varType;
	tNodeExpression* Expression;

} tNodeVariableAssigment;




typedef struct NodeStatement
{
	NodeType type;
	union StatementNode
	{
		struct NodeVariableDeclaration variable_declaration;
		struct NodeVariableAssigment variable_assigment;
		//todo procedure call
		//todo compound statements
	} tStatementNode;
	struct NodeStatement* Next;

} tNodeStatement;


typedef struct NodeIfStatement
{
	tNodeExpression* Condition;

	tNodeStatement* Pass;
	struct NodeElseIfStatement* elseIf;
	tNodeStatement* Fail;


} tNodeIfStatement;

typedef struct NodeElseIfStatement
{
	tNodeExpression* Condition;
	tNodeStatement* Pass;
	struct NodeElseIfStatement* Next;
	tNodeIfStatement* parent;

} tNodeElseIfStatement;

typedef struct NodeScope
{
	tNodeStatement* Statement;

} tNodeScope;

typedef struct NodeBlock
{

	tNodeExpression* Condition;
	tNodeStatement* Statement;

} tNodeBlock;

typedef struct Node
{
	NodeType type;
	union Data
	{
		struct NodeVariableDeclaration variable_declaration;
		struct NodeVariableAssigment variable_assigment;
		struct NodeInteger* intValue;
		struct NodeDouble* doubleValue;
		struct NodeString* stringValue;
		struct NodeExpression* expression;
		struct NodeStatement* statement;
		struct NodeIfStatement* ifStatement;
		struct NodeElseIfStatement* elseIfStatement;
		struct NodeScope* scope;
		struct NodeBlock* whileBlock;
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
tNode* ProcessStatement();
