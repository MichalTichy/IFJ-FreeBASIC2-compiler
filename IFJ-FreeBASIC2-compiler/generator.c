#include "Parser.h"
#include "generator.h"
#include "List.h"

void Generate(struct Node* root)
{
	struct Node* actualNode = root;
	tDLList* list;
	DLInitList(&list);
	while (actualNode != NULL)
	{
		switch (actualNode->type)
		{
		case integerVal:
		{

		}
		break;
		case doubleVal:
		{

		}
		break;
		case stringVal:
		{

		}
		break;
		case varDeclaration:
		{

		}
		break;
		case varAssigment :
		{

		}
		break;
		case expression :
		{

		}
		break;
		case scope :
		{

		}
		break; 
		case statement :
		{

		}
		break;
		case ifCondition :
		{

		}
		break;
		case elseIfCondition :
		{

		}
		break;
		case whileBlock :
		{

		}
		break;
		case binaryExpression :
		{

		}
		break;
		case prefixExpression :
		{

		}
		break;
		case negationExpression :
		{

		}
		break;
		case identifier :
		{

		}
		break;
		case empty :
		{

		}
		break;
		default:
			break;
		}
	}

}