#include "Parser.h"
tToken* token;

tProgram* Parse() {
	Next();
	tProgram* program = InitProgramNode();
	program->Main = ProcessProgram(program->globalScope);
	if (program==NULL || program->Main==NULL)
	{
		exitSecurely(SYNTAX_ERR);
	}
	return program;
}

void Next() {
	token = GetNextToken();
}
void Back() {
	token = ReturnToken();
}

void BackMultipleTimes(int steps) {
	for (int i = 0; i < steps; ++i)
	{
		Back();
	}
}

tNode* ProcessInteger(struct tSTScope* parentScope) {
	if (token->Type == T_INTVALUE)
	{
		return InitIntegerNode(token->IntVal);
	}
	return NULL;
}

tNode* ProcessDouble(struct tSTScope* parentScope) {
	if (token->Type == T_DOUBLEVALUE)
	{
		return InitDoubleNode(token->DoubleVal);
	}
	return NULL;
}
tNode* ProcessString(struct tSTScope* parentScope) {
	if (token->Type == T_STRINGVALUE)
	{
		return InitStringNode(token->String,token->Lenght);
	}
	return NULL;
}

tProgram* InitProgramNode()
{
	tProgram* node = mmalloc(sizeof(struct Program));
	STMakeScope(&node->globalScope, NULL);
	return node;
}

tNode* InitIntegerNode(long int value) {
	tNode* node = mmalloc(sizeof(struct Node));
	node->type = integerVal;
	node->tData.intValue = mmalloc(sizeof(struct NodeInteger));
	node->tData.intValue->value = value;
	return node;
}

tNode* InitDoubleNode(double value) {
	tNode* node = mmalloc(sizeof(struct Node));
	node->type = doubleVal;
	node->tData.doubleValue= mmalloc(sizeof(struct NodeDouble));
	node->tData.doubleValue->value = value;
	return node;
}

tNode* InitStringNode(char* value, int lenght) {
	tNode* node = mmalloc(sizeof(struct Node));
	node->type =stringVal;
	node->tData.stringValue = mmalloc(sizeof(struct NodeString));
	node->tData.stringValue->value = value;
	node->tData.stringValue->lenght = lenght;
	return node;
}

tNode* InitVarDeclarationNode() {
	tNode* node = mmalloc(sizeof(struct Node));
	node->type = varDeclaration;
	node->tData.variable_declaration = mmalloc(sizeof(struct NodeVariableDeclaration));
	return node;
}


tNode* InitVarAssigmentNode() {
	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.variable_assigment = mmalloc(sizeof(struct NodeVariableAssigment));
	node->type = varAssigment;
	return node;
}

tNode* InitScopeNode(struct tSTScope* parentScope) {
	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.scope = mmalloc(sizeof(struct NodeScope));
	STMakeScope(&node->tData.scope->scope, parentScope);
	node->type = scope;
	return node;
}
tNode* InitPrefixExpressionNode() {
	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.prefixExpression = mmalloc(sizeof(struct NodePrefixExpression));
	node->type = prefixExpression;
	return node;
}
tNode* InitNegationExpressionNode() {
	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.negationExpression = mmalloc(sizeof(struct NodeNegationExpression));
	node->type = negationExpression;
	return node;
}

tNode* InitStatementNode() {
	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.statement= mmalloc(sizeof(struct NodeStatement));
	node->type = statement;
	return node;
}

tNode* InitIfStatementNode(struct tSTScope* parentScope) {
	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.ifStatement= mmalloc(sizeof(struct NodeIfStatement));
	STMakeScope(&node->tData.ifStatement->passScope, parentScope);
	STMakeScope(&node->tData.ifStatement->failScope, parentScope);
	node->type = ifCondition;
	return node;
}


tNode* InitWhileNode(struct tSTScope* parentScope)
{
	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.whileBlock = mmalloc(sizeof(struct NodeWhileBlock));
	STMakeScope(&node->tData.whileBlock->scope, parentScope);
	node->type = whileBlock;
	return node;
}

tNode* InitBinaryExpressionNode()
{
	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.binaryExpression = mmalloc(sizeof(struct NodeBinaryExpression));
	node->type = binaryExpression;
	return node;
}

tNodeElseIfStatement* InitElseIfStatementNode(tNodeIfStatement* parent, struct tSTScope* parentScope) {
	tNodeElseIfStatement* node = mmalloc(sizeof(struct NodeElseIfStatement));
	STMakeScope(&node->scope, parentScope);
	node->parent= parent;
	return node;
}


bool IsTokenScalarType()
{
	return token->Type == T_INTEGER || token->Type == T_DOUBLE || token->Type == T_STRING;
}

tNode* initIdentifierNode()
{

	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.identifier= mmalloc(sizeof(struct NodeIdentifier));
	node->type = identifier;
	return node;
}

tNode* initExpressionNode()
{

	tNode* node = mmalloc(sizeof(struct Node));
	node->tData.expression = mmalloc(sizeof(struct NodeExpression));
	node->type = expression;
	return node;
}

tNode* ProcessIdentifier(struct tSTScope* parentScope)
{
	if (token->Type==T_ID)
	{
		tNode* node = initIdentifierNode();
		node->tData.identifier->id = token->String;

		struct tSTItem* symPableItem = STScopeSearch(&parentScope, node->tData.identifier->id);
		if (symPableItem == NULL)
		{
			exitSecurely(SEMANT_ERR_DEF);
		}
		return node;
	}
	return NULL;
}

tNode* ProcessAtom(struct tSTScope* parentScope)
{
	if (token->Type == T_INTVALUE)
	{
		tNode* node= InitIntegerNode(token->IntVal);
		return node;
	}
	if (token->Type == T_DOUBLEVALUE)
	{
		tNode* node= InitDoubleNode(token->DoubleVal);
		return node;
	}

	tNode* id = ProcessIdentifier(parentScope);
	if (id!=NULL)
	{
		return id;
	}

	return NULL;
}

tNode* ProcessHighestPrecedenceExpression(struct tSTScope* parentScope)
{
	int takenTokens = 0;
	tNode* atom = ProcessAtom(parentScope);
	if (atom!=NULL)
	{
		return atom;
	}

	if (token->Type==T_LEFTBRACKET)
	{
		Next();
		takenTokens++;
		tNode* exp = ProcessExpression(parentScope);
		if (exp!=NULL)
		{
			Next();
			takenTokens++;
			if (token->Type==T_RIGHTBRACKET)
			{
				return exp;
			}
		}		
	}

	BackMultipleTimes(takenTokens);
	return NULL;
}

tNode* ProcessNegationExpression(struct tSTScope* parentScope)
{
	int takenTokens = 0;
	if (token->Type==T_NOT)
	{
		Next();
		takenTokens++;
		tNode* relationalExpression = ProcessRelationalExpression(parentScope);
		if (relationalExpression)
		{
			tNode* exp = InitNegationExpressionNode();
			exp->tData.negationExpression->expression = relationalExpression;
			return exp;
		}
	}
	BackMultipleTimes(takenTokens);
	return NULL;
}
tNode* ProcessPrefixExpression(struct tSTScope* parentScope)
{
	int takenTokents = 0;
	if (token->Type==T_SUB||token->Type==T_ADD)
	{
		Next();
		takenTokents++;
		tNode* prefExpression = ProcessPrefixExpression(parentScope);
		if (prefExpression!=NULL)
		{
			tNode* exp = InitPrefixExpressionNode();
			exp->tData.prefixExpression->OP = token->Type;
			exp->tData.prefixExpression->expression = prefExpression;
			return exp;
		}
		else
		{
			Back();
			takenTokents--;
		}
	}


	tNode* negation = ProcessNegationExpression(parentScope);
	if (negation!=NULL)
	{
		return negation;
	}

	return ProcessHighestPrecedenceExpression(parentScope);
}

tNode* ProcessMultiplicationExpression(struct tSTScope* parentScope)
{

	tNode* exp = ProcessPrefixExpression(parentScope);
	bool matched = false;
	Next();
	while (token->Type == T_MULTIPLY || token->Type==T_DIVIDE)
	{
		matched = true;
		tNode* newExp = InitBinaryExpressionNode();
		newExp->tData.binaryExpression->OP = token->Type;
		Next();
		newExp->tData.binaryExpression->left = exp;
		newExp->tData.binaryExpression->right = ProcessPrefixExpression(parentScope);
		exp = newExp;
	}

	if (!matched)
		Back();
	return exp;
	
}

tNode* ProcessIntDivisionExpression(struct tSTScope* parentScope)
{

	tNode* exp = ProcessMultiplicationExpression(parentScope);
	bool matched = false;
	Next();
	while (token->Type == T_INTDIVIDE)
	{
		matched = true;
		tNode* newExp = InitBinaryExpressionNode();
		newExp->tData.binaryExpression->OP = token->Type;
		Next();
		newExp->tData.binaryExpression->left = exp;
		newExp->tData.binaryExpression->right = ProcessMultiplicationExpression(parentScope);
		exp = newExp;
	}

	if (!matched)
		Back();
	return exp;
}

tNode* ProcessAddExpression(struct tSTScope* parentScope)
{
	tNode* exp = ProcessIntDivisionExpression(parentScope);
	bool matched = false;
	Next();
	while (token->Type == T_ADD || token->Type == T_SUB )
	{
		matched = true;
		tNode* newExp = InitBinaryExpressionNode();
		newExp->tData.binaryExpression->left = exp;
		newExp->tData.binaryExpression->OP = token->Type;
		Next();
		newExp->tData.binaryExpression->right = ProcessIntDivisionExpression(parentScope);
		exp = newExp;
	}

	if (!matched)
		Back();
	return exp;
}

tNode* ProcessRelationalExpression(struct tSTScope* parentScope)
{
	tNode* exp = ProcessAddExpression(parentScope);
	bool matched = false;
	Next();
	while (token->Type == T_ASSIGN || token->Type == T_GREATER || token->Type == T_LESS|| token->Type == T_NOTEQUAL|| token->Type == T_GREATEROREQUAL|| token->Type == T_LESSEROREQUAL)
	{
		matched = true;
		tNode* newExp = InitBinaryExpressionNode();
		newExp->tData.binaryExpression->left = exp;
		newExp->tData.binaryExpression->OP = token->Type;
		Next();
		newExp->tData.binaryExpression->right = ProcessAddExpression(parentScope);
		exp = newExp;
	}
	if (!matched)
		Back();
	return exp;
}

tNode* ProcessLogicalAndExpression(struct tSTScope* parentScope)
{
	tNode* exp = ProcessRelationalExpression(parentScope);
	bool matched = false;
	Next();
	while (token->Type == T_AND)
	{
		matched = true;
		tNode* newExp = InitBinaryExpressionNode();
		newExp->tData.binaryExpression->left = exp;
		newExp->tData.binaryExpression->OP = T_AND;
		Next();
		newExp->tData.binaryExpression->right = ProcessRelationalExpression(parentScope);
		exp = newExp;
	}

	if (!matched)
		Back();
	return exp;
}

tNode* ProcessLogicalOrExpression(struct tSTScope* parentScope)
{
	tNode* exp = ProcessLogicalAndExpression(parentScope);
	bool matched = false;
	Next();
	while (token->Type==T_OR)
	{
		matched = true;
		tNode* newExp = InitBinaryExpressionNode();
		newExp->tData.binaryExpression->left = exp;
		newExp->tData.binaryExpression->OP = T_OR;
		Next();
		newExp->tData.binaryExpression->right= ProcessLogicalAndExpression(parentScope);
		exp = newExp;
	}
	if (!matched)
		Back();
	return exp;
}

tNode*  ProcessExpression(struct tSTScope* parentScope)
{
	tNode* exp = ProcessLogicalAndExpression(parentScope);
	tNode* wrap = initExpressionNode();
	wrap->tData.expression->tExpressionData.expression=exp;
	return wrap;
}

tNode* ProcessVarDeclaration(struct tSTScope* parentScope) {
	int takenTokens = 0;
	tNode* declaration = NULL;
	if (token->Type == T_DIM)
	{
		declaration = InitVarDeclarationNode();
		Next();
		takenTokens++;
		if (token->Type == T_ID)
		{
			declaration->tData.variable_declaration->id = token->String;
			Next();
			takenTokens++;
			if (token->Type==T_AS)
			{
				Next();
				takenTokens++;
				if (IsTokenScalarType())
				{
					declaration->tData.variable_declaration->varType = TokenTypeToScalarType(token->Type);
					Next();
					takenTokens++;

					struct tSTItem* symPableItem = STScopeSearch(&parentScope, declaration->tData.variable_declaration->id);
					if (symPableItem != NULL)
						exitSecurely(SEMANT_ERR_DEF);
					STScopeInsert(&parentScope, declaration->tData.variable_declaration->id);

					//todo check if item isnt allready defined
					if (token->Type==T_ASSIGN)
					{
						Next();
						takenTokens++;
						tNode* expression = ProcessExpression(parentScope);
						if (expression!=NULL)
						{
							declaration->tData.variable_declaration->Expression = expression;
							return declaration;
						}
					}
					else
					{
						Back();
						takenTokens--;
						return declaration;
					}
				}
			}
		}
	}

	BackMultipleTimes(takenTokens);
	mfree(declaration);
	return NULL;
}

tNode* ProcessAssigment(struct tSTScope* parentScope) {
	int takenTokens = 0;
	tNode* assigment = NULL;
	if (token->Type == T_ID)
	{
		assigment = InitVarAssigmentNode();
		assigment->tData.variable_assigment->id = token->String;
		struct tSTItem* symPableItem = STScopeSearch(&parentScope, assigment->tData.variable_assigment->id);
		if (symPableItem==NULL)
			exitSecurely(SEMANT_ERR_DEF);
		Next();
		takenTokens++;
		if (token->Type==T_ASSIGN)
		{
			Next();
			takenTokens++;
			tNode* expression = ProcessExpression(parentScope);
			if (expression!=NULL)
			{
				assigment->tData.variable_assigment->Expression = expression;
				return assigment;
			}
		}
	}

	BackMultipleTimes(takenTokens);
	mfree(assigment);
	return NULL;
}

bool IsStatementSeparator(TokenType tokenType)
{
	return tokenType == T_EOL;
}

int SkipStatementSeparators() {
	int countOfFoundSeparators = 0;
	while (IsStatementSeparator(token->Type))
	{
		Next();
		countOfFoundSeparators++;		
	}
	return countOfFoundSeparators;
}

tNode* ProcessScope(struct tSTScope* parentScope) {
	int takenTokens = 0;
	if (token->Type==T_SCOPE)
	{
		Next();
		takenTokens++;
		tNode* scope = InitScopeNode(parentScope);

		tNode* statement = ProcessStatement(scope->tData.scope->scope);
		if (statement != NULL)
		{
			scope->tData.scope->Statement = statement->tData.statement;
			Next();
			takenTokens++;

			if (token->Type == T_END)
			{
				Next();
				takenTokens++;
				if (token->Type == T_SCOPE)
				{
					return scope;
				}
			}
		}
	}

	BackMultipleTimes(takenTokens);
	return NULL;
}

tNodeElseIfStatement* ProcessElseIfStatements(tNodeIfStatement* parent, struct tSTScope* parentScope)
{
	int takenTokens = 0;
	tNodeElseIfStatement* firstElseIf = NULL;
	while (token->Type == T_ELSEIF)
	{
		tNodeElseIfStatement* elseIf = InitElseIfStatementNode(parent,parentScope);

		Next();
		takenTokens++;
		tNode* elseIfCondition = ProcessExpression(parentScope);
		if (elseIfCondition != NULL)
		{
			elseIf->Condition = elseIfCondition;

			Next();
			takenTokens++;
			tNode* elseIfStatements = ProcessStatement(elseIf->scope);

			if (elseIfStatements != NULL)
			{
				elseIf->Pass = elseIfStatements->tData.statement;
				Next();
				takenTokens++;
			}
			else
			{
				//TODO ERROR
				BackMultipleTimes(takenTokens);
				return NULL;
			}
		}
		else
		{
			//TODO ERROR
			BackMultipleTimes(takenTokens);
			return NULL;
		}

		if (firstElseIf == NULL)
		{
			firstElseIf = elseIf;
		}
		else
		{
			firstElseIf->Next = elseIf;
		}
	}

	return firstElseIf;
}

tNode* ProcessIfStatement(struct tSTScope* parentScope) {
	int takenTokens = 0;
	if (token->Type == T_IF)
	{
		tNode* ifNode = InitIfStatementNode(parentScope);
		Next();
		takenTokens++;
		tNode* expression = ProcessExpression(parentScope);
		if (expression != NULL)
		{
			ifNode->tData.ifStatement->Condition = expression;
			Next();
			takenTokens++;
			if (token->Type == T_THEN)
			{
				Next();
				takenTokens++;
				tNode* passStatements = ProcessStatement(ifNode->tData.ifStatement->passScope);
				if (passStatements != NULL)
				{
					ifNode->tData.ifStatement->Pass = passStatements->tData.statement;
					Next();
					takenTokens++;

					ifNode->tData.ifStatement->elseIf = ProcessElseIfStatements(ifNode->tData.ifStatement,parentScope);

					if (token->Type == T_ELSE)
					{
						Next();
						takenTokens++;

						tNode* failStatements = ProcessStatement(ifNode->tData.ifStatement->failScope);
						if (failStatements != NULL)
						{
							ifNode->tData.ifStatement->Fail = failStatements->tData.statement;
						}

						Next();
						takenTokens++;
					}
					if (token->Type==T_END)
					{
						Next();
						takenTokens++;
						if (token->Type==T_IF)
						{
							return ifNode;
						}
						
					}
				}
			}
		}
		BackMultipleTimes(takenTokens);
		return NULL;
	}


	BackMultipleTimes(takenTokens);
	return NULL;
}

tNode* ProcessWhileStatement(struct tSTScope* parentScope) {
	int takenTokens = 0;
	if (token->Type==T_DO)
	{
		Next();
		takenTokens++;
		if (token->Type == T_WHILE)
		{
			tNode* whileNode = InitWhileNode(parentScope);
			Next();
			takenTokens++;

			tNode* expression = ProcessExpression(parentScope);
			if (expression!=NULL)
			{
				whileNode->tData.whileBlock->Condition = expression;
				Next();
				takenTokens++;

				tNode* Statement = ProcessStatement(whileNode->tData.whileBlock->scope);
				if (Statement!=NULL)
				{
					whileNode->tData.whileBlock->Statement = Statement->tData.statement;
					
					Next();
					takenTokens++;
					if (token->Type==T_LOOP)
					{
						return whileNode;
					}
				}
			}
		}
		
	}


	BackMultipleTimes(takenTokens);
	return NULL;
}

tNode* ProcessCompoundStatement(struct tSTScope* parentScope) {

	//TODO ADD SUPPORT FOR FUNCTIONS
	int takenTokens = 0;

	tNode* scope = ProcessScope(parentScope);
	if (scope!=NULL)
		return scope;

	tNode* ifStatement = ProcessIfStatement(parentScope);
	if (ifStatement !=NULL)
		return ifStatement;

	tNode* whileStatement = ProcessWhileStatement(parentScope);
	if (whileStatement !=NULL)
		return whileStatement;



	BackMultipleTimes(takenTokens);
	return NULL;
}

tNode* ProcessPrintStatement(struct tSTScope* parentScope) {
	//TODO
}

tNode* ProcessInputStatement(struct tSTScope* parentScope) {
	//TODO
}

tNode* ProcessQuirkStatement(struct tSTScope* parentScope) {
	int takenTokens = 0;

	tNode* print = ProcessPrintStatement(parentScope);
	if (print !=NULL)
		return print;

	tNode* input = ProcessInputStatement(parentScope);
	if (input !=NULL)
		return input;

	
	BackMultipleTimes(takenTokens);
	return NULL;
}

tNode* ProcessStatement(struct tSTScope* parentScope)
{
	int takenTokens = SkipStatementSeparators();
	if (takenTokens==0)
	{
		//missing statement separator
		return NULL;
	}

	tNode* statement = InitStatementNode();
	statement->tData.statement->type = empty;

	tNode* varDec = ProcessVarDeclaration(parentScope);
	if (varDec != NULL)
	{
		statement->tData.statement->type = varDeclaration;
		statement->tData.statement->tStatementNode.variable_declaration = varDec->tData.variable_declaration;
	}
	else
	{

		tNode* compoundStatement = ProcessCompoundStatement(parentScope);
		if (compoundStatement != NULL)
		{
			switch (compoundStatement->type) {
			case scope:
				statement->tData.statement->type = scope;
				statement->tData.statement->tStatementNode.scope = compoundStatement->tData.scope;
				break;
			case ifCondition:
				statement->tData.statement->type = ifCondition;
				statement->tData.statement->tStatementNode.ifBlock = compoundStatement->tData.ifStatement;
				break;
			case whileBlock:

				statement->tData.statement->type = whileBlock;
				statement->tData.statement->tStatementNode.whileBlock = compoundStatement->tData.whileBlock;
				break;

			default:;  //todo ERROR
			}
		}
		else
		{
			tNode* quirkStatement = ProcessQuirkStatement(parentScope);
			if (quirkStatement != NULL)
			{
				//TODO quirkStatement
			}
			else
			{
				tNode* assigment = ProcessAssigment(parentScope);
				if (assigment != NULL)
				{
					statement->tData.statement->type = varAssigment;
					statement->tData.statement->tStatementNode.variable_assigment = assigment->tData.variable_assigment;
				}
				else
				{
					//NOT AN STATEMENT
					BackMultipleTimes(takenTokens);
					return statement;
				}
			}

		}
	}

	Next();
	tNode* nextStatement = ProcessStatement(parentScope);
	if (nextStatement!=NULL && nextStatement->tData.statement->type !=empty)
	{
		statement->tData.statement->Next = nextStatement->tData.statement;
	}
	
	return statement;

}

tNode* ProcessProgram(struct tSTScope* parentScope) {

	//TODO ADD SUPPORT FOR FUNCTIONS
	int takenTokens = 0;
	tNode* scope = ProcessScope(parentScope);
	if (scope!=NULL)
	{
		return scope;
	}

	BackMultipleTimes(takenTokens);
	return NULL;
}



ScalarType TokenTypeToScalarType(TokenType tokenType)
{
	switch (tokenType)
	{
		case T_INTEGER:return TYPE_Integer;
		case T_DOUBLE:return TYPE_Double;
		case T_STRING:return TYPE_String;
		default: return NULL; //TODO ERROR
	} 
}
