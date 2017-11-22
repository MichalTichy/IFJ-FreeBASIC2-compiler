#include "Parser.h"
tToken* token;

void Parse() {
	Next();
}

void Next() {
	token = GetNextToken();
}
void Back() {
	ReturnToken();
}

void BackMultipleTimes(int steps) {
	for (int i = 0; i < steps; ++i)
	{
		Back();
	}
}

tNode* ProcessInteger() {
	if (token->Type == T_INTVALUE)
	{
		return InitIntegerNode(token->IntVal);
	}
	return NULL;
}

tNode* ProcessDouble() {
	if (token->Type == T_DOUBLEVALUE)
	{
		return InitDoubleNode(token->DoubleVal);
	}
	return NULL;
}
tNode* ProcessString() {
	if (token->Type == T_STRINGVALUE)
	{
		return IniStringNode(token->String,token->Lenght);
	}
	return NULL;
}



tNode* ProcessScalar() {
	return ProcessNumber() || ProcessString();
}

tNode* ProcessNumber() {
	return ProcessInteger() || ProcessDouble();
}


tNode* InitIntegerNode(long int value) {
	tNode* node = malloc(sizeof(struct Node));
	node->type = integerVal;
	node->tData.intValue->value = value;
	return node;
}

tNode* InitDoubleNode(double value) {
	tNode* node = malloc(sizeof(struct Node));
	node->type = doubleVal;
	node->tData.doubleValue->value = value;
	return node;
}

tNode* IniStringNode(char* value, int lenght) {
	tNode* node = malloc(sizeof(struct Node));
	node->type =stringVal;
	node->tData.stringValue->value = value;
	node->tData.stringValue->lenght = lenght;
	return node;
}

tNode* InitVarDeclarationNode() {
	tNode* node = malloc(sizeof(struct Node));
	node->type = varDeclaration;
	return node;
}


tNode* InitVarAssigmentNode() {
	tNode* node = malloc(sizeof(struct Node));
	node->type = varAssigment;
	return node;
}

tNode* InitScopeNode() {
	tNode* node = malloc(sizeof(struct Node));
	node->type = scope;
	return node;
}

tNode* InitStatementNode() {
	tNode* node = malloc(sizeof(struct Node));
	node->type = statement;
	return node;
}

tNode* InitIfStatementNode() {
	tNode* node = malloc(sizeof(struct Node));
	node->type = ifCondition;
	return node;
}


tNode* InitWhileNode()
{
	tNode* node = malloc(sizeof(struct Node));
	node->type = whileBlock;
	return node;
}

tNodeElseIfStatement* InitElseIfStatementNode(tNodeIfStatement* parent) {
	tNodeElseIfStatement* node = malloc(sizeof(struct NodeElseIfStatement));
	node->parent= parent;
	return node;
}


bool IsTokenScalarType()
{
	return token->Type == T_INTEGER || token->Type == T_DOUBLE || token->Type == T_STRING;
}

tNode* ProcessExpression()
{
	//TODO
}

tNode* ProcessVarDeclaration() {
	int takenTokens = 0;
	tNode* declaration = NULL;
	if (token->Type == T_DIM)
	{
		declaration = InitVarDeclarationNode();
		Next();
		takenTokens++;
		if (token->Type == T_ID)
		{
			//todo add to symtable
			Next();
			takenTokens++;
			if (token->Type==T_AS)
			{
				Next();
				takenTokens++;
				if (IsTokenScalarType())
				{
					declaration->tData.variable_declaration.varType = TokenTypeToScalarType(token->Type);
					Next();
					takenTokens++;
					if (token->Type==T_ASSIGN)
					{
						Next();
						takenTokens++;
						tNode* expression = ProcessExpression();
						if (expression!=NULL)
						{
							declaration->tData.variable_declaration.Expression = expression->tData.expression;
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
	free(declaration);
	return NULL;
}

tNode* ProcessAssigment() {
	int takenTokens = 0;
	tNode* assigment = NULL;
	if (token->Type == T_ID)
	{
		//tood pointer var
		assigment = InitVarAssigmentNode();
		Next();
		takenTokens++;
		if (token->Type==T_ASSIGN)
		{
			Next();
			takenTokens++;
			tNodeExpression* expression = ProcessExpression()->tData.expression;
			if (expression!=NULL)
			{
				assigment->tData.variable_assigment.Expression = expression;
				return assigment;
			}
		}
	}

	BackMultipleTimes(takenTokens);
	free(assigment);
	return NULL;
}

int SkipStatementSeparators() {
	int countOfFoundSeparators = 0;
	while (token->Type==T_EOL)
	{
		Next();
		countOfFoundSeparators++;		
	}
	return countOfFoundSeparators;
}

tNode* ProcessScope() {
	int takenTokens = 0;
	if (token->Type==T_SCOPE)
	{
		Next();
		takenTokens++;
		tNode* scope = InitScopeNode();

		tNode* statement = ProcessStatement();
		if (statement != NULL)
		{
			scope->tData.scope->Statement = statement->tData.statement;
			Next();
			takenTokens++;
		}
		else if (token->Type == T_END)
		{
			Next();
			takenTokens++;
			if (token->Type == T_SCOPE)
			{
				return scope;
			}
		}
	}

	BackMultipleTimes(takenTokens);
	return NULL;
}

tNodeElseIfStatement* ProcessElseIfStatements(tNodeIfStatement* parent)
{
	int takenTokens = 0;
	tNodeElseIfStatement* firstElseIf = NULL;
	while (token->Type == T_ELSEIF)
	{
		tNodeElseIfStatement* elseIf = InitElseIfStatementNode(parent);

		Next();
		takenTokens++;
		tNode* elseIfCondition = ProcessExpression();
		if (elseIfCondition != NULL)
		{
			elseIf->Condition = elseIfCondition->tData.expression;

			Next();
			takenTokens++;
			tNode* elseIfStatements = ProcessExpression();

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

tNode* ProcessIfStatement() {
	int takenTokens = 0;
	if (token->Type == T_IF)
	{
		tNode* ifNode = InitIfStatementNode();
		Next();
		takenTokens++;
		tNode* expression = ProcessExpression();
		if (expression != NULL)
		{
			ifNode->tData.ifStatement->Condition = expression->tData.expression;
			Next();
			takenTokens++;
			if (token->Type == T_THEN)
			{
				Next();
				takenTokens++;
				tNode* passStatements = ProcessStatement();
				if (passStatements != NULL)
				{
					ifNode->tData.ifStatement->Pass = passStatements->tData.statement;
					Next();
					takenTokens++;

					ifNode->tData.ifStatement->elseIf = ProcessElseIfStatements(ifNode->tData.ifStatement);

					if (token->Type == T_ELSE)
					{
						Next();
						takenTokens++;

						tNode* failStatements = ProcessStatement();
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

tNode* ProcessWhileStatement() {
	int takenTokens = 0;
	if (token->Type==T_DO)
	{
		Next();
		takenTokens++;
		if (token->Type == T_WHILE)
		{
			tNode* whileNode = InitWhileNode();
			Next();
			takenTokens++;

			tNode* expression = ProcessExpression();
			if (expression!=NULL)
			{
				whileNode->tData.whileBlock->Condition = expression->tData.expression;
				Next();
				takenTokens++;

				tNode* Statement = ProcessStatement();
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

tNode* ProcessCompoundStatement() {

	//TODO ADD SUPPORT FOR FUNCTIONS
	int takenTokens = 0;

	tNode* scope = ProcessScope();
	if (scope!=NULL)
		return scope;
	else
		free(scope);

	tNode* ifStatement = ProcessIfStatement();
	if (ifStatement !=NULL)
		return ifStatement;
	else
		free(ifStatement);

	tNode* whileStatement = ProcessWhileStatement();
	if (whileStatement !=NULL)
		return whileStatement;
	else
		free(whileStatement);



	BackMultipleTimes(takenTokens);
	return NULL;
}

tNode* ProcessPrintStatement() {
	//TODO
}

tNode* ProcessInputStatement() {
	//TODO
}

tNode* ProcessQuirkStatement() {
	int takenTokens = 0;

	tNode* print = ProcessPrintStatement();
	if (print !=NULL)
		return print;
	else
		free(print);

	tNode* input = ProcessInputStatement();
	if (input !=NULL)
		return input;
	else
		free(input);

	
	BackMultipleTimes(takenTokens);
	return NULL;
}

tNode* ProcessStatement()
{
	int takenTokens = SkipStatementSeparators();
	if (takenTokens==0)
	{
		//missing statement separator
		return NULL;
	}

	tNode* statement = InitStatementNode();

	tNode* varDec = ProcessVarDeclaration();
	if (varDec != NULL)
	{
		statement->tData.statement->type = varDeclaration;
		statement->tData.statement->tStatementNode.variable_declaration = varDec->tData.variable_declaration;
	}
	else
	{

		tNode* compoundStatement = ProcessCompoundStatement();
		if (compoundStatement != NULL)
		{
			//TODO compound statements
		}
		else
		{
			tNode* quirkStatement = ProcessQuirkStatement();
			if (quirkStatement != NULL)
			{
				//TODO quirkStatement
			}
			else
			{
				tNode* assigment = ProcessAssigment();
				if (assigment != NULL)
				{
					statement->tData.statement->type = varAssigment;
					statement->tData.statement->tStatementNode.variable_assigment = varDec->tData.variable_assigment;
				}
				else
				{
					//NOT AN STATEMENT
					BackMultipleTimes(takenTokens);
					return NULL;
				}
			}

		}
	}

	Next();
	tNode* nextStatement = ProcessStatement();
	if (nextStatement!=NULL)
	{
		statement->tData.statement->Next = nextStatement->tData.statement;
	}
	else
	{
		Back();
	}
	
	return statement;

}

tNode* ProcessProgram() {

	//TODO ADD SUPPORT FOR FUNCTIONS
	int takenTokens = 0;
	tNode* scope = ProcessScope();
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

