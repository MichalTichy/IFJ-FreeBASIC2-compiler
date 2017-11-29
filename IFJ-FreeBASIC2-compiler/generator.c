#include "Parser.h"
#include "generator.h"
#include "List.h"

struct Node * wrapa(NodeType type, union Data d)
{
	struct Node *tmp;
	tmp->tData = d;
	tmp->type = type;
	return tmp;
}

void Recognize(struct Node* root)
{
	struct Node* actualNode = root;
		switch (actualNode->type)
		{
			case integerVal:
			{
				fprintf(stderr, "intVal\n");
			}
			break;
			case doubleVal:
			{
				fprintf(stderr, "doubleVal\n");
			}
			break;
			case stringVal:
			{
				fprintf(stderr, "stringVal\n");
			}
			break;
			case varDeclaration:
			{
				fprintf(stderr, "var declar\n");
				fprintf(stdout, "DEFVAR LF@_%s", actualNode->tData.variable_declaration->id);
			}
			break;
			case varAssigment:
			{
				fprintf(stderr, "var assig\n");
			}
			break;
			case expression:
			{
				fprintf(stderr, "express\n");
			}
			break;
			case scope:
			{
				fprintf(stderr, "in scope\n");
				fprintf(stdout, "CREATEFRAME\n");
				/*struct Node node;
				node.type = statement;
				union Data d;
				d.statement = actualNode->tData.scope->Statement;
				node.tData = d;*/
				//Recognize( wrapa(statement,(union Data)actualNode->tData.scope->Statement));
			
			}
			break;
			case statement:
			{
				fprintf(stderr, "statement\n");

				if (actualNode->tData.statement->type == varDeclaration)
				{
					fprintf(stderr, "in statement -- vardec\n");
					//Recognize(wrapa(varDeclaration, (union Data)actualNode->tData.variable_declaration));
					
				}
				else if (actualNode->tData.statement->type == varAssigment)
				{
					fprintf(stderr, "in statement -- varassig\n");
				}
				else if (actualNode->tData.statement->type == scope)
				{
					fprintf(stderr, "in statement -- scope\n");
				}
				else if (actualNode->tData.statement->type == ifCondition)
				{
					fprintf(stderr, "in statement -- ifcond\n");
				}
				else if (actualNode->tData.statement->type == whileBlock)
				{
					fprintf(stderr, "in statement -- while\n");
				}
			}
			break;
			case ifCondition:
			{
				fprintf(stderr, "if\n");
			}
			break;
			case elseIfCondition:
			{
				fprintf(stderr, "elsif\n");
			}
			break;
			case whileBlock:
			{
				fprintf(stderr, "while\n");
			}
			break;
			case binaryExpression:
			{
				fprintf(stderr, "binexp\n");
			}
			break;
			case prefixExpression:
			{
				fprintf(stderr, "prefixexp\n");
			}
			break;
			case negationExpression:
			{
				fprintf(stderr, "neg\n");
			}
			break;
			case identifier:
			{
				fprintf(stderr, "identif\n");
			}
			break;
			case empty:
			{
				fprintf(stderr, "empt\n");
			}
			break;
			default:
				break;
	}
}
void Generate(tProgram* program)
{
	tProgram prg = *program;
	fprintf(stdout, ".IFJcode17\n");
	Recognize(prg.Main);

}

