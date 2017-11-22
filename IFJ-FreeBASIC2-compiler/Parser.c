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
	bool failed = false;
	tNode* assigment = NULL;
	if (token->Type == T_DIM)
	{
		assigment = InitVarDeclarationNode();
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
					assigment->tData.variable_declaration.varType = TokenTypeToScalarType(token->Type);
					Next();
					takenTokens++;
					if (token->Type==T_ASSIGN)
					{
						Next();
						takenTokens++;
						tNode* expression = ProcessExpression();
						if (expression!=NULL)
						{
							assigment->tData.variable_declaration.Expression = expression->tData.expression;
							return assigment;
						}
					}
					else
					{
						Back();
						takenTokens--;
						return assigment;
					}
				}
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
