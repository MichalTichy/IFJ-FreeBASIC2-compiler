#include "Basics.h"
#include "Scanner.h"

typedef enum NodeType {
	Integer
} NodeType;

typedef struct NodeInteger
{
	int value;
} tNodeInteger;


typedef struct Node
{
	NodeType type;
	union Data
	{
		tNodeInteger* integer;
	} tData;
}tNode;

tNode* IsNumber(tToken* token);
tNode* IsInteger(tToken* token);
tNode* InitNode(tToken* token);
tNode* InitIntegerNode(int value);