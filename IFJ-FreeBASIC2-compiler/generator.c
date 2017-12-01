#include "Parser.h"
#include "generator.h"
#include "List.h"
#include "ADT.h"

struct Node * wrapa(NodeType type, union Data d)
{
	struct Node *tmp = (struct Node*)mmalloc(sizeof(struct Node));
	tmp->type = type;
	tmp->tData = d;
	
	return tmp;
}

typedef struct meta
{
	int ifStatementsInUse;
	int whileStatementsInUse;
	int intVarInUse;
	int doubleVarInUse;
	int boolVarInUse;

	int ifStatementsDeclared;
	int whileStatementsDeclared;
	int intVarDeclared;
	int doubleVarDeclared;
	int boolVarDeclared;
} tMetaData;

enum metaMember
{
	ifStatement,
	whileStatement,
	intVar,
	doubleVar,
	boolVar

};


void metaDec(enum metaMember memb, tMetaData* meta)
{
	switch (memb)
	{
	case ifStatement: meta->ifStatementsInUse--;
		break;
	case whileStatement: meta->whileStatementsInUse--;
		break;
	case intVar: meta->doubleVarInUse--;
		break;
	case doubleVar: meta->doubleVarInUse--;
		break;
	case boolVar: meta->boolVarInUse--;
		break;
	}
}

void metaInc(enum metaMember memb, tMetaData* meta)
{
	switch (memb)
	{
	case ifStatement: 
	{
		if(meta->ifStatementsInUse == meta->ifStatementsDeclared)
		{
			//fprintf(stdout, "DEFVAR LF@_IfStatementConditionResult%d\n", meta->ifStatementsInUse);
			meta->ifStatementsDeclared++;
		}
		meta->ifStatementsInUse++;
	}
	break;
	case whileStatement:
	{
		if (meta->whileStatementsInUse == meta->whileStatementsDeclared+1)
		{
			meta->whileStatementsDeclared++;
		}
		meta->whileStatementsInUse++;
	}
	break;
	case intVar:
	{
		if (meta->intVarInUse == meta->intVarDeclared)
		{
			meta->intVarDeclared++;
			fprintf(stdout, "DEFVAR LF@_intVar%d\n", meta->intVarInUse+1);
			
		}
		meta->intVarInUse++;
	}
	break;
	case doubleVar:
	{
		if (meta->doubleVarInUse == meta->doubleVarDeclared)
		{
			meta->doubleVarDeclared++;
			fprintf(stdout, "DEFVAR LF@_floatVar%d\n", meta->doubleVarInUse+1);
			
		}
		meta->doubleVarInUse++;
	}
	break;
	case boolVar:
	{
		if (meta->boolVarInUse == meta->boolVarDeclared)
		{
			meta->boolVarDeclared++;
			fprintf(stdout, "DEFVAR LF@_boolVar%d\n", meta->boolVarInUse+1);
			
		}
		meta->boolVarInUse++;
	}
	default:
		break;
	}
}



void Recognize(struct Node* root, struct meta* metadata)
{
	struct Node* actualNode = root;
	struct meta* met = metadata;
		switch (actualNode->type)
		{
			case integerVal:
			{
				fprintf(stdout, "int@%d", actualNode->tData.intValue->value);

			}
			break;
			case doubleVal:
			{
				fprintf(stdout, "float@%f", actualNode->tData.doubleValue->value);
			}
			break;
			case stringVal:
			{
				fprintf(stdout, "string@%s",actualNode->tData.stringValue->value);
			}
			break;
			case varDeclaration:
			{
				fprintf(stdout, "DEFVAR LF@_%s\n", actualNode->tData.variable_declaration->id);
				if (actualNode->tData.variable_declaration->Expression != NULL)
				{
					switch (actualNode->tData.variable_declaration->varType)
					{
					case TYPE_Integer: fprintf(stdout, "MOVE LF@_%s ", actualNode->tData.variable_declaration->id);
						break;
					case TYPE_Double: fprintf(stdout, "MOVE LF@_%s ", actualNode->tData.variable_declaration->id);
						break;
					case TYPE_String: fprintf(stdout, "MOVE LF@_%s ", actualNode->tData.variable_declaration->id);
					}

					Recognize(wrapa(expression, (union Data)actualNode->tData.variable_declaration->Expression->tData), met);
					fprintf(stdout, "\n");
				}
				
				
				
				
			}
			break;
			case varAssigment:
			{
				/*switch (actualNode->tData.variable_assigment->varType)
				{
				case TYPE_Integer: fprintf(stdout, "MOVE LF@_%s int@", actualNode->tData.variable_assigment->id);
					break;
				case TYPE_Double: fprintf(stdout, "MOVE LF@_%s double@", actualNode->tData.variable_assigment->id);
					break;
				case TYPE_String: fprintf(stdout, "MOVE LF@_%s string@", actualNode->tData.variable_assigment->id);
				default:
					break;
				}*/
				

				switch (actualNode->tData.variable_assigment->varType)
				{
					case TYPE_String:
					{
						Recognize(wrapa(stringVal, (union Data)actualNode->tData.variable_assigment->Expression->tData), met);
					}
					break;
					case TYPE_Integer:
					{
						if (actualNode->tData.variable_assigment->Expression->tData.expression->tExpressionData.expression->type == integerVal)
						{
							fprintf(stdout, "MOVE LF@_%s ", actualNode->tData.variable_assigment->id);
							Recognize(wrapa(expression, (union Data)actualNode->tData.variable_assigment->Expression->tData),met);
							fprintf(stdout, "\n");
						}
						else 
						{
							Recognize(wrapa(expression, (union Data)actualNode->tData.variable_assigment->Expression->tData), met);
							fprintf(stdout, "MOVE LF@_%s LF@_intVar%d\n", actualNode->tData.variable_assigment->id, met->intVarInUse);
						}
						
					}
					break;
					case TYPE_Double:
					{
						if (actualNode->tData.variable_assigment->Expression->tData.expression->tExpressionData.expression->type == doubleVal)
						{
							fprintf(stdout, "MOVE LF@_%s ", actualNode->tData.variable_assigment->id);
							Recognize(wrapa(expression, (union Data)actualNode->tData.variable_assigment->Expression->tData), met);
							fprintf(stdout, "\n");
						}
						else
						{
							Recognize(wrapa(expression, (union Data)actualNode->tData.variable_assigment->Expression->tData), met);
							fprintf(stdout, "MOVE LF@_%s LF@_doubleVar%d\n", actualNode->tData.variable_assigment->id, met->doubleVarInUse);
						}
						
					}
					break;
				}
				
				
			}
			break;
			case expression:
			{

				if (actualNode->tData.expression->ResultType == TYPE_Integer || actualNode->tData.expression->ResultType == TYPE_Double)
				{
					if (actualNode->tData.expression->tExpressionData.expression->type == binaryExpression)
					{
						Recognize(wrapa(binaryExpression, (union Data)actualNode->tData.expression->tExpressionData.expression->tData.binaryExpression), met);
					}
					else if (actualNode->tData.expression->tExpressionData.expression->type == negationExpression)
					{
						Recognize(wrapa(negationExpression, (union Data)actualNode->tData.expression->tExpressionData.expression->tData.binaryExpression), met);
					}
					else if (actualNode->tData.expression->tExpressionData.expression->type == integerVal)
					{
						Recognize(wrapa(integerVal, (union Data)actualNode->tData.expression->tExpressionData.expression->tData.binaryExpression), met);
					}
					else if (actualNode->tData.expression->tExpressionData.expression->type == doubleVal)
					{
						Recognize(wrapa(doubleVal, (union Data)actualNode->tData.expression->tExpressionData.expression->tData.binaryExpression), met);
					}
					else if (actualNode->tData.expression->tExpressionData.expression->type == stringVal)
					{
						Recognize(wrapa(stringVal, (union Data)actualNode->tData.expression->tExpressionData.expression->tData.binaryExpression), met);
					}
					else
					{
						printf("######## case expression - something else -  to do define #######");
					}
					
				}
				else if (actualNode->tData.expression->ResultType == TYPE_String)
				{
					Recognize(wrapa(stringVal, (union Data)actualNode->tData.expression->tExpressionData.expression->tData), met);
				}
			}
			break;
			case scope:
			{
				fprintf(stdout, "CREATEFRAME\n");
				fprintf(stdout, "PUSHFRAME\n");
				Recognize( wrapa( statement,(union Data)actualNode->tData.scope->Statement), met);
				fprintf(stdout, "POPFRAME\n");
			
			}
			break;
			case statement:
			{

				if (actualNode->tData.statement->type == varDeclaration)
				{
					Recognize(wrapa(varDeclaration, (union Data)actualNode->tData.statement->tStatementNode.variable_declaration), met);
					
					

				}
				else if (actualNode->tData.statement->type == varAssigment)
				{
				}
				else if (actualNode->tData.statement->type == scope)
				{
				}
				else if (actualNode->tData.statement->type == ifCondition)
				{
					Recognize(wrapa(ifCondition, (union Data)actualNode->tData.statement->tStatementNode.ifBlock), met);
				}
				else if (actualNode->tData.statement->type == whileBlock)
				{
				}
				if (actualNode->tData.statement->Next != NULL) Recognize(wrapa(statement, (union Data)actualNode->tData.statement->Next), met);
			}
				break;
			case ifCondition:
			{
				metaInc(ifStatement, met);
				Recognize(wrapa(expression, (union Data)actualNode->tData.ifStatement->Condition->tData.expression), met); // IFSTATEMENT CONDITION
				fprintf(stdout, "JUMPIFNEQ _ifStatementElse%d LF@_boolVar%d bool@true\n", met->ifStatementsInUse, met->boolVarInUse);
				metaDec(boolVar, met);
				if (actualNode->tData.ifStatement->Pass->type != empty)					// PASS BLOCK
				{
					if (actualNode->tData.ifStatement->Pass->type == varAssigment)
					{
						Recognize(wrapa(varAssigment, (union Data)actualNode->tData.ifStatement->Pass->tStatementNode.variable_assigment), met);
						Recognize(actualNode->tData.ifStatement->Pass->Next, met);
					}
					else
					{
						fprintf(stderr, "##### ifCondition PASS type something else #####");
					}
				}
				

				fprintf(stdout, "JUMP _IfStatementConditionEnd%d\n", met->ifStatementsInUse);					// JUMP to the end of if statment in case of pass
				

				if (actualNode->tData.ifStatement->Fail->type != empty)									// FAIL BLOCK
				{
					fprintf(stdout, "LABEL _ifStatementElse%d\n", met->ifStatementsInUse);
					if (actualNode->tData.ifStatement->Fail->type == varAssigment)
					{
						Recognize(wrapa(varAssigment, (union Data)actualNode->tData.ifStatement->Fail->tStatementNode.variable_assigment), met);
						fprintf(stdout, "\n");
						Recognize(actualNode->tData.ifStatement->Fail->Next, met);
					}
					else
					{
						fprintf(stderr, "##### ifCondition FAIL type something else #####");
					}
				}
				
				

				if (actualNode->tData.ifStatement->elseIf == NULL)  //if there is no else if, than this is end of if statement
				{
					fprintf(stdout, "LABEL _IfStatementConditionEnd%d\n", met->ifStatementsInUse);
					metaDec(ifStatement, met);
				}
				else
				{
					Recognize(wrapa(elseIfCondition, (union Data)actualNode->tData.ifStatement->elseIf), met);
				}
			}
			break;
			case elseIfCondition:
			{
				fprintf(stderr, "elsif\n");
			}
			break;
			case whileBlock:
			{
				metaInc(whileStatement, met);
				fprintf(stdout, "JUMP _WhileStatementCondition%d\n", met->whileStatementsInUse);

				switch (actualNode->tData.whileBlock->Statement->type)
				{
				case varDeclaration: Recognize(wrapa(varDeclaration, (union Data)actualNode->tData.whileBlock->Statement->tStatementNode.variable_declaration), met);
					break;
				case varAssigment: Recognize(wrapa(varAssigment, (union Data)actualNode->tData.whileBlock->Statement->tStatementNode.variable_assigment), met);
					break;
				case scope: Recognize(wrapa(scope, (union Data)actualNode->tData.whileBlock->Statement->tStatementNode.scope), met);
					break;
				case ifCondition: Recognize(wrapa(ifCondition, (union Data)actualNode->tData.whileBlock->Statement->tStatementNode.ifBlock), met);
					break;
				case whileBlock:Recognize(wrapa(whileBlock, (union Data)actualNode->tData.whileBlock->Statement->tStatementNode.whileBlock), met);
					break;
				}


				Recognize(actualNode->tData.whileBlock->Statement->Next, met);

				

				

			}
			break;
			case binaryExpression:
			{

				
				switch (actualNode->tData.binaryExpression->OP)
				{
				case T_LESS:
				{
					metaInc(boolVar, met);
					fprintf(stdout, "LT LF@_boolVar%d ", met->boolVarInUse);
					//fprintf(stdout, "PUSHS LF@_boolVar%d\n", met->boolVarInUse);
				}
					break;
				case T_MULTIPLY: 
				{
					switch (actualNode->tData.binaryExpression->resultType)
					{
						case TYPE_Integer:
						{
							metaInc(intVar, met);
							fprintf(stdout, "MUL LF@_intVar%d", met->intVarInUse);
						}
							break;
						case TYPE_Double:
						{
							metaInc(doubleVar, met);
							fprintf(stdout, "MUL LF@_floatVar%d", met->doubleVarInUse);
						}
							break;
					}
				}
					break;
				default: fprintf(stderr, "#### case binary expression op #####");
					break;
				}
				
				
				if (actualNode->tData.binaryExpression->left->type == identifier)
				{
					Recognize(wrapa(identifier, (union Data)actualNode->tData.binaryExpression->left->tData), met);

				}
				else if (actualNode->tData.binaryExpression->left->type == integerVal)
				{
					Recognize(wrapa(integerVal, (union Data)actualNode->tData.binaryExpression->left->tData), met);
				}
				else
				{
					fprintf(stderr, "###### case binaryexp LEFT type something elese ###### ");
				}

				fprintf(stdout, " ");

				if (actualNode->tData.binaryExpression->right->type == identifier)
				{
					Recognize(wrapa(identifier, (union Data)actualNode->tData.binaryExpression->right->tData), met);

				}
				else if (actualNode->tData.binaryExpression->right->type == integerVal)
				{
					Recognize(wrapa(integerVal, (union Data)actualNode->tData.binaryExpression->right->tData), met);
				}
				else
				{
					fprintf(stderr, "###### case binaryexp RIGHT type something elese ###### ");
				}
				fprintf(stdout, "\n");

			


			}
			break;
			case prefixExpression:
			{
			}
			break;
			case negationExpression:
			{
				fprintf(stderr, "neg\n");
			}
			break;
			case identifier:
			{
				fprintf(stdout, "LF@%s", actualNode->tData.identifier->id);
			}
			break;
			case empty:
			{
				fprintf(stderr, "empt\n");
			}
			break;
	}
}



void Generate(tProgram* program)
{
	struct meta* metaData = (struct meta*)mmalloc(sizeof(struct meta));
	metaData->ifStatementsInUse = 0;
	metaData->whileStatementsInUse = 0;
	metaData->intVarInUse = 0;
	metaData->doubleVarInUse = 0;
	metaData->boolVarInUse = 0;

	metaData->ifStatementsDeclared = 0;
	metaData->whileStatementsDeclared = 0;
	metaData->intVarDeclared = 0;
	metaData->doubleVarDeclared = 0;
	metaData->boolVarDeclared = 0;

	tProgram prg = *program;
	fprintf(stdout, ".IFJcode17\n");
	TStack_t stack;
	StackInit(&stack);
	Recognize(program->Main, metaData);

}

