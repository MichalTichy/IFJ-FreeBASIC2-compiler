#ifndef PARSER
#define PARSER

#include "Basics.h"
#include "Scanner.h"
#include "ManagedMalloc.h"
#include "SymTable.h"
#include "functiontable.h"

typedef enum {
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
	returnStatement,
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

typedef struct NodeBinaryExpression {
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

typedef struct NodeReturnStatement
{
	ScalarType result;
	struct NodeExpression* expression;
} tNodeReturnStatement;

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
		struct NodeReturnStatement* returnStatement;
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
		struct NodeReturnStatement* returnStatement;
	} tData;
}tNode;

void BackMultipleTimes(int steps);
void Back();
ScalarType ExtractType(tNode* node);
ScalarType GetResultType(ScalarType type1, ScalarType type2, TokenType operation);
tNode* InitBinaryExpressionNode();
tNode* InitDoubleNode(double value);
tNodeElseIfStatement* InitElseIfStatementNode(tNodeIfStatement* parent, struct tSTScope* parentScope);
tNode* initExpressionNode();
tFunction* InitFunctionNode(struct tSTScope* parentScope);
tNode* initIdentifierNode();
tNode* InitIfStatementNode(struct tSTScope* parentScope);
tNode* InitInputNode();
tNode* InitIntegerNode(long int value);
tNode* InitNegationExpressionNode();
tNode* InitPrefixExpressionNode();
tNode* InitPrintNode();
tPrintStatement* InitPrintStatement();
tProgram* InitProgramNode();
tNode* InitScopeNode(struct tSTScope* parentScope);
tNode* InitStatementNode();
tNode* InitStringNode(char* value, int lenght);
tNode* InitVarAssigmentNode();
tNode* InitVarDeclarationNode();
tNode* InitWhileNode(struct tSTScope* parentScope);
tNodeReturnStatement* initReturnNode(tNodeExpression* exp);
bool IsStatementSeparator(TokenType tokenType);
bool IsTokenScalarType();
void Next();
tProgram* Parse();
tNode* ProcessAddExpression(struct tSTScope* parentScope);
tNode* ProcessAssigment(struct tSTScope* parentScope);
tNode* ProcessAtom(struct tSTScope* parentScope);
tNode* ProcessCompoundStatement(struct tSTScope* parentScope);
tNode* ProcessDouble(struct tSTScope* parentScope);
tNodeElseIfStatement* ProcessElseIfStatements(tNodeIfStatement* parent, struct tSTScope* parentScope);
tNode* ProcessExpression(struct tSTScope* parentScope);
tNode* ProcessFunctionCall(struct tSTScope* parent_scope);
tFunction* ProcessFunctionDefinition(struct tSTScope* parentScope);
tNode* ProcessHighestPrecedenceExpression(struct tSTScope* parentScope);
tNode* ProcessIdentifier(struct tSTScope* parentScope);
tNode* ProcessIfStatement(struct tSTScope* parentScope);
tNode* ProcessInputNode(struct tSTScope* parentScope);
tNode* ProcessIntDivisionExpression(struct tSTScope* parentScope);
tNode* ProcessInteger(struct tSTScope* parentScope);
tNode* ProcessLogicalAndExpression(struct tSTScope* parentScope);
tNode* ProcessLogicalOrExpression(struct tSTScope* parentScope);
tNode* ProcessMultiplicationExpression(struct tSTScope* parentScope);
tNode* ProcessNegationExpression(struct tSTScope* parentScope);
tNode* ProcessPrefixExpression(struct tSTScope* parentScope);
tPrintStatement* processPrintExpression(struct tSTScope* parentScope);
tNode* ProcessPrintNode(struct tSTScope* parentScope);
tProgram* ProcessProgram();
tNode* ProcessQuirkStatement(struct tSTScope* parentScope);
tNode* ProcessRelationalExpression(struct tSTScope* parentScope);
tNode* ProcessScope(struct tSTScope* parentScope);
tNode* ProcessStatement(struct tSTScope* parentScope);
tNode* ProcessString(struct tSTScope* parentScope);
tNode* ProcessVarDeclaration(struct tSTScope* parentScope);
tNode* ProcessWhileStatement(struct tSTScope* parentScope);
int SkipStatementSeparators();
ScalarType TokenTypeToScalarType(TokenType tokenType);

#endif