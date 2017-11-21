#include "Basics.h"
#include "Scanner.h"


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

typedef enum {
	Integer
} NodeType;