#ifndef PARSER
#define PARSER

#include "Basics.h"
#include "Scanner.h"
#include "ManagedMalloc.h"
#include "SymTable.h"
#include "functiontable.h"

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
	input,
	print,
	functionCall,
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
	char* id;
	ScalarType type;
} tNodeIdentifier;

typedef struct NodeBinaryExpression{
	ScalarType resultType;
	struct Node* left;
	struct Node* right;
	TokenType OP;

}tNodeBinaryExpression;


typedef struct NodePrefixExpression
{
	ScalarType resultType;
	struct Node* expression;
	TokenType OP;

} tNodePrefixExpression;

typedef struct NodeNegationExpression
{
	ScalarType resultType;
	struct Node* expression;

} tNodeNegationExpression;

typedef struct NodeExpression
{
	ScalarType ResultType;
	struct Node* expression;

} tNodeExpression;

typedef struct NodeVariableDeclaration
{
	char* id;
	ScalarType varType;
	struct Node* Expression;

} tNodeVariableDeclaration;

typedef struct NodeVariableAssigment
{
	char* id;
	ScalarType varType;
	struct Node* Expression;

} tNodeVariableAssigment;




typedef struct NodeIfStatement
{
	struct tSTScope* passScope;
	struct tSTScope* failScope;
	struct Node* Condition;
	struct NodeStatement* Pass;
	struct NodeElseIfStatement* elseIf;
	struct NodeStatement* Fail;


} tNodeIfStatement;

typedef struct NodeElseIfStatement
{
	struct tSTScope* scope;
	struct Node* Condition;
	struct NodeStatement* Pass;
	struct NodeElseIfStatement* Next;
	tNodeIfStatement* parent;

} tNodeElseIfStatement;

typedef struct NodeScope
{
	struct tSTScope* scope;
	struct NodeStatement* Statement;

} tNodeScope;

typedef struct NodeWhileBlock
{
	struct tSTScope* scope;
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
		struct PrintStatement* printStatement;
		struct InputStatement* inputStatement;
		struct FunctionCall* functionCall;
	} tStatementNode;
	struct NodeStatement* Next;

} tNodeStatement;

typedef struct PrintStatement
{
	struct Node* Expression;
	struct PrintStatement* nextPrint;
}tPrintStatement;

typedef struct InputStatement
{
	tNodeIdentifier* identifier;
}tInputStatement;

typedef struct FunctionCall
{
	ScalarType result;
	struct tFTItem* funTableItem;
	struct NodeExpression** Arguments;
	int argumentsCount;
}tFunctionCall;

typedef struct Function
{
	struct tFTItem* funTableItem;
	struct tSTScope* scope;
	struct Node* body;
	struct NodeExpression* returnExp;
}tFunction;

typedef struct Program
{
	struct tSTScope* globalScope;
	struct tFTItem* functionTable;
	struct Node* Main;

}tProgram;

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
		struct InputStatement* input;
		struct PrintStatement* print;
		struct FunctionCall* functionCall;
	} tData;
}tNode;

tProgram* Parse();

void Next();

void Back();

void BackMultipleTimes(int steps);
tProgram* InitProgramNode();

ScalarType GetResultType(ScalarType type1, ScalarType type2, TokenType operation);
tPrintStatement* ProcessPrintExpression(struct tSTScope* parentScope);
tNode* ProcessDouble(struct tSTScope* parentScope);

tNode * ProcessInteger(struct tSTScope* parentScope);

tNode * InitIntegerNode(long int value);

tNode* InitDoubleNode(double value);

tNode* InitStringNode(char* value, int lenght);

tNode * InitVarDeclarationNode();
int SkipStatementSeparators();

tNode * ProcessVarDeclaration(struct tSTScope* parentScope);
tNode * ProcessExpression(struct tSTScope* parentScope);
tNode* ProcessRelationalExpression(struct tSTScope* parentScope);
ScalarType ExtractType(tNode* node);
ScalarType TokenTypeToScalarType(TokenType tokenType);
tNode* ProcessStatement(struct tSTScope* parentScope);
tNode* ProcessFunctionCall(struct tSTScope* parent_scope);
tProgram* ProcessProgram();

#endif