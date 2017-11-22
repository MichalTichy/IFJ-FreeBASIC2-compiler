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
