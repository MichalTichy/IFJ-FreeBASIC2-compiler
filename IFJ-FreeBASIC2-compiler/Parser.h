#ifndef PARSER
#define PARSER

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
	whileBlock,
	binaryExpression,
	prefixExpression,
	negationExpression,
	identifier,
	empty
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

typedef struct NodeIdentifier
{
	//todo pointer to symtable
} tNodeIdentifier;

typedef struct NodeBinaryExpression{
	struct Node* left;
	struct Node* right;
	TokenType OP;

}tNodeBinaryExpression;


typedef struct NodePrefixExpression
{
	struct Node* expression;
	TokenType OP;

} tNodePrefixExpression;

typedef struct NodeNegationExpression
{
	struct Node* expression;

} tNodeNegationExpression;

typedef struct NodeExpression
{
	ScalarType ResultType;
	union ExpressionData
	{
		struct NodeString* string;
		struct Node* expression;

	}tExpressionData;

} tNodeExpression;

typedef struct NodeVariableDeclaration
{
	//todo pointer to ID
	ScalarType varType;
	struct Node* Expression;

} tNodeVariableDeclaration;

typedef struct NodeVariableAssigment
{
	//todo pointer to ID
	ScalarType varType;
	struct Node* Expression;

} tNodeVariableAssigment;




typedef struct NodeIfStatement
{
	struct Node* Condition;

	struct NodeStatement* Pass;
	struct NodeElseIfStatement* elseIf;
	struct NodeStatement* Fail;


} tNodeIfStatement;

typedef struct NodeElseIfStatement
{
	struct Node* Condition;
	struct NodeStatement* Pass;
	struct NodeElseIfStatement* Next;
	tNodeIfStatement* parent;

} tNodeElseIfStatement;

typedef struct NodeScope
{
	struct NodeStatement* Statement;

} tNodeScope;

typedef struct NodeWhileBlock
{

	struct Node*  Condition;
	struct NodeStatement* Statement;

} tNodeBlock;

typedef struct NodeStatement
{
	NodeType type;
	union StatementNode
	{
		struct NodeVariableDeclaration* variable_declaration;
		struct NodeVariableAssigment* variable_assigment;
		struct NodeScope* scope;
		struct NodeIfStatement* ifBlock;
		struct NodeWhileBlock* whileBlock;
		//todo procedure call
	} tStatementNode;
	struct NodeStatement* Next;

} tNodeStatement;

typedef struct Node
{
	NodeType type;
	union Data
	{
		struct NodeVariableDeclaration* variable_declaration;
		struct NodeVariableAssigment* variable_assigment;
		struct NodeInteger* intValue;
		struct NodeDouble* doubleValue;
		struct NodeString* stringValue;
		struct NodeExpression* expression;
		struct NodeStatement* statement;
		struct NodeIfStatement* ifStatement;
		struct NodeElseIfStatement* elseIfStatement;
		struct NodeScope* scope;
		struct NodeWhileBlock* whileBlock;
		struct NodeBinaryExpression* binaryExpression;
		struct NodePrefixExpression* prefixExpression;
		struct NodeNegationExpression* negationExpression;
		struct NodeIdentifier* identifier;
	} tData;
}tNode;

tNode* Parse();

void Next();

void Back();

void BackMultipleTimes(int steps);

tNode * ProcessNumber();
tNode* ProcessDouble();

tNode * ProcessInteger();

tNode * InitIntegerNode(long int value);

tNode* InitDoubleNode(double value);

tNode* InitStringNode(char* value, int lenght);

tNode * InitVarDeclarationNode();

tNode * ProcessVarDeclaration();
tNode * ProcessExpression();
tNode* ProcessRelationalExpression();

ScalarType TokenTypeToScalarType(TokenType tokenType);
tNode* ProcessStatement();
tNode* ProcessProgram();

#endif