/**
*	Project: IFJ17 Compiler
*
*	FILE: parser.h
*
*	File author:
*	  Michal Tichý, xtichy26
*
*	Project authors:
*	  Michal Tichy, xtichy26
*	  Michal Martinu, xmarti78
*	  Gabriel Mastny, xmastn02
*	  Ondra Deingruber, xdeing00
*
**/

#ifndef PARSER
#define PARSER

#include "Basics.h"
#include "Scanner.h"
#include "ManagedMalloc.h"
#include "SymTable.h"
#include "functiontable.h"

/**
 * Enum definujici typy Nodu
 */
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

/**
* Integer node
*/
typedef struct NodeInteger
{
	long int value;
} tNodeInteger;

/**
* Dobule node
*/
typedef struct NodeDouble
{
	double value;
} tNodeDouble;

/**
* String node
*/
typedef struct NodeString
{
	char* value;
	int lenght;
} tNodeString;

/**
* identifier node
*/
typedef struct NodeIdentifier
{
	char* id;
	ScalarType type;
} tNodeIdentifier;

/**
* Expression with two operands
*/
typedef struct NodeBinaryExpression {
	ScalarType resultType;
	struct Node* left;
	struct Node* right;
	TokenType OP;
}tNodeBinaryExpression;

/**
* Prefix expression
*/
typedef struct NodePrefixExpression
{
	ScalarType resultType;
	struct Node* expression;
	TokenType OP;
} tNodePrefixExpression;

/**
* Negation expression
*/
typedef struct NodeNegationExpression
{
	ScalarType resultType;
	struct Node* expression;
} tNodeNegationExpression;

/**
* Expression node
*/
typedef struct NodeExpression
{
	ScalarType ResultType;
	struct Node* expression;
} tNodeExpression;

/**
* Variavble declaration node
*/
typedef struct NodeVariableDeclaration
{
	char* id;
	ScalarType varType;
	struct Node* Expression;
} tNodeVariableDeclaration;

/**
* Variable assigment node
*/
typedef struct NodeVariableAssigment
{
	char* id;
	ScalarType varType;
	struct Node* Expression;
} tNodeVariableAssigment;

/**
* If node
*/
typedef struct NodeIfStatement
{
	struct tSTScope* passScope;
	struct tSTScope* failScope;
	struct Node* Condition;
	struct NodeStatement* Pass;
	struct NodeElseIfStatement* elseIf;
	struct NodeStatement* Fail;
} tNodeIfStatement;


/**
* Else if node
*/
typedef struct NodeElseIfStatement
{
	struct tSTScope* scope;
	struct Node* Condition;
	struct NodeStatement* Pass;
	struct NodeElseIfStatement* Next;
	tNodeIfStatement* parent;
} tNodeElseIfStatement;


/**
* Scope node
*/
typedef struct NodeScope
{
	struct tSTScope* scope;
	struct NodeStatement* Statement;
} tNodeScope;

/**
* While node
*/
typedef struct NodeWhileBlock
{
	struct tSTScope* scope;
	struct Node*  Condition;
	struct NodeStatement* Statement;
} tNodeBlock;

/**
* return node
*/
typedef struct NodeReturnStatement
{
	ScalarType result;
	struct NodeExpression* expression;
} tNodeReturnStatement;

/**
* statement node
*/
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

/**
* Print statement
*/
typedef struct PrintStatement
{
	struct Node* Expression;
	struct PrintStatement* nextPrint;
}tPrintStatement;

/**
* input statement
*/
typedef struct InputStatement
{
	tNodeIdentifier* identifier;
}tInputStatement;

/**
* Function call node
*/
typedef struct FunctionCall
{
	ScalarType result;
	struct tFTItem* funTableItem;
	struct NodeExpression** Arguments;
	int argumentsCount;
}tFunctionCall;


/**
* Function node
*/
typedef struct Function
{
	struct tFTItem* funTableItem;
	struct tSTScope* scope;
	struct Node* body;
	struct NodeExpression* returnExp;
}tFunction;


/**
* program node
*/
typedef struct Program
{
	struct tSTScope* globalScope;
	struct tFTItem* functionTable;
	struct Node* Main;
}tProgram;


/**
* Base node
*/
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

/**
* Returns tokens back to queue
* @param steps count of tokens for return* 
*/
void BackMultipleTimes(int steps);

/**
* Returns token back to queue
*/
void Back();


/**
* Extracts Scalar type from node.
* @param node Node to exptract type from.
* @return extracted type
*/
ScalarType ExtractType(tNode* node);

/**
* Gets type of opearation result
* @param type1 First operand
* @param type2 Seccond operand
* @param operation Operator
* @returnResult type
*/
ScalarType GetResultType(ScalarType type1, ScalarType type2, TokenType operation);

/**
* Creates BinaryExpression node
* @return BinaryExpression node
*/
tNode* InitBinaryExpressionNode();

/**
* Creates Double node
* @return Double node
*/
tNode* InitDoubleNode(double value);

/**
* Creates Else if node
* @return Else if node
*/
tNodeElseIfStatement* InitElseIfStatementNode(tNodeIfStatement* parent, struct tSTScope* parentScope);

/**
* Creates Expression node
* @return Expression node
*/
tNode* initExpressionNode();

/**
* Creates function node
* @return function node
*/
tFunction* InitFunctionNode(struct tSTScope* parentScope);

/**
* Creates Identifier node
* @return Identifier node
*/
tNode* initIdentifierNode();

/**
* Creates if statement node
* @return if statement node
*/
tNode* InitIfStatementNode(struct tSTScope* parentScope);

/**
* Creates Input node
* @return Input node
*/
tNode* InitInputNode();

/**
* Creates Integer node
* @return Integer node
*/
tNode* InitIntegerNode(long int value);

/**
* Creates Negation expression node
* @return Negation expression node
*/
tNode* InitNegationExpressionNode();

/**
* Creates Prefix expression node
* @return Prefix expression node
*/
tNode* InitPrefixExpressionNode();

/**
* Creates print node
* @return print node
*/
tNode* InitPrintNode();

/**
* Creates print statement node
* @return print statement node
*/
tPrintStatement* InitPrintStatement();

/**
* Creates program node
* @return program node
*/
tProgram* InitProgramNode();

/**
* Creates scope node
* @return scope node
*/
tNode* InitScopeNode(struct tSTScope* parentScope);

/**
* Creates statement node
* @return statement node
*/
tNode* InitStatementNode();

/**
* Creates string node
* @return string node
*/
tNode* InitStringNode(char* value, int lenght);

/**
* Creates variable assigment node
* @return variable assigment node
*/
tNode* InitVarAssigmentNode();

/**
* Creates variable declaration node
* @return variable declaration node
*/
tNode* InitVarDeclarationNode();

/**
* Creates while node
* @return while node
*/
tNode* InitWhileNode(struct tSTScope* parentScope);

/**
* Creates return node
* @return return node
*/
tNodeReturnStatement* initReturnNode(tNodeExpression* exp);

/**
 * Check if given token type is statement separator
 * @param tokenType input token type
 * @return whether given token type is statement separatorn
 */
bool IsStatementSeparator(TokenType tokenType);

/**
* Check if current token type represents scalar type
* @return whether current token represents scalar type
*/
bool IsTokenScalarType();

/**
 * Puts next token into token variable
 */
void Next();

/**
 *Parses program loaded from stdIn
 *@return program node
 */
tProgram* Parse();

/**
 * Processes Add expression
 * @param parentScope parent symbol scope
 * @return result node if successfull or NULL if failed
 */
tNode* ProcessAddExpression(struct tSTScope* parentScope);

/**
* Processes assigment
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessAssigment(struct tSTScope* parentScope);

/**
* Processes atom
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessAtom(struct tSTScope* parentScope);

/**
* Processes compound statement
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessCompoundStatement(struct tSTScope* parentScope);

/**
* Processes double
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessDouble(struct tSTScope* parentScope);

/**
* Processes else if statement
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNodeElseIfStatement* ProcessElseIfStatements(tNodeIfStatement* parent, struct tSTScope* parentScope);

/**
* Processes expression
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessExpression(struct tSTScope* parentScope);

/**
* Processes function call
* @param parent_scope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessFunctionCall(struct tSTScope* parent_scope);

/**
* Processes function definition
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tFunction* ProcessFunctionDefinition(struct tSTScope* parentScope);

/**
* Processes Highest precedence expression
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessHighestPrecedenceExpression(struct tSTScope* parentScope);

/**
* Processes Identifier
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessIdentifier(struct tSTScope* parentScope);

/**
* Processes if statement
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessIfStatement(struct tSTScope* parentScope);

/**
* Processes input 
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessInputNode(struct tSTScope* parentScope);

/**
* Processes int division
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessIntDivisionExpression(struct tSTScope* parentScope);

/**
* Processes integer
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessInteger(struct tSTScope* parentScope);

/**
* Processes logical and expression
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessLogicalAndExpression(struct tSTScope* parentScope);

/**
* Processes logical or expression
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessLogicalOrExpression(struct tSTScope* parentScope);

/**
* Processes multiplication expression
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessMultiplicationExpression(struct tSTScope* parentScope);

/**
* Processes neagtion expression
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessNegationExpression(struct tSTScope* parentScope);

/**
* Processes prefix expression
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessPrefixExpression(struct tSTScope* parentScope);

/**
* Processes print expression
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tPrintStatement* processPrintExpression(struct tSTScope* parentScope);

/**
* Processes print node
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessPrintNode(struct tSTScope* parentScope);

/**
* Processes program
* @return result node if successfull or NULL if failed
*/
tProgram* ProcessProgram();

/**
* Processes quirk statements
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessQuirkStatement(struct tSTScope* parentScope);

/**
* Processes relational expression
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessRelationalExpression(struct tSTScope* parentScope);

/**
* Processes scope
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessScope(struct tSTScope* parentScope);

/**
* Processes statements
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessStatement(struct tSTScope* parentScope);

/**
* Processes process string
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessString(struct tSTScope* parentScope);

/**
* Processes variable declaration
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessVarDeclaration(struct tSTScope* parentScope);

/**
* Processes while statement
* @param parentScope parent symbol scope
* @return result node if successfull or NULL if failed
*/
tNode* ProcessWhileStatement(struct tSTScope* parentScope);

/**
 * Skip all tokens which arr statement separators
 */
int SkipStatementSeparators();

/**
 * Convert token type to Scalar type
 * @param tokenType input tokoenType
 * @return result scalar type
 */
ScalarType TokenTypeToScalarType(TokenType tokenType);

#endif