#include "Parser.h"
void Parse() {

}
tNode* IsNumber(tToken* token) {
	return IsInteger(token);
}

tNode* IsInteger(tToken* token) {
	if (token->Type==T_INTVALUE && token->IntVal!=NULL)
	{
		return InitNode(token);
	}
	return NULL;
}

tNode* InitNode(tToken* token) {
	switch (token->Type)
	{
	case Integer:
		return InitIntegerNode(token->IntVal);
	default:
		break;
	}
}

tNode* InitIntegerNode(int value) {
	tNode* node = malloc(sizeof(struct Node));
	node->type = Integer;
	node->tData.integer = malloc(sizeof(struct NodeInteger));
	node->tData.integer = value;
	return node;
}