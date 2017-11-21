#include "parser.h"
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

tNode* ProcessInteger() {
	if (token->Type == T_INTVALUE)
	{
		return InitIntegerNode(token->IntVal);
	}
	return NULL;
}

tNode* ProcessNumber() {
	return ProcessInteger();
}


tNode* InitIntegerNode(int value) {
	tNode* node = malloc(sizeof(struct Node));
	node->type = integer;
	node->tData.integer->value = value;
	return node;
}

tNode* InitVarDeclarationNode() {
	tNode* node = malloc(sizeof(struct Node));
	node->type = varDeclaration;
	return node;
}


tNode* ProcessVarDeclaration() {
	if (token->Type == T_DIM)
	{
		tNode* assigment = InitVarDeclarationNode();
		Next();
		if (token->Type == T_ID)
		{

		}
		else
		{
			Back();
		}
	}
}
