/**
*	Project: IFJ17 Compiler
*
*	FILE: generator.c
*
*	File author:
*	  Gabriel Mastny, xmastn02
*
*	Project authors:
*	  Michal Tichy, xtichy26
*	  Michal Martinu, xmarti78
*	  Gabriel Mastny, xmastn02
*	  Ondra Deingruber, xdeing00
*
**/
#include "Parser.h"
#include "generator.h"
#include "List.h"
#include "ADT.h"
#include <stdlib.h>
#include <string.h>

// Wraps subset of Node atributes back to Node 
struct Node * wrapa(NodeType type, union Data d)
{
	struct Node *tmp = (struct Node*)mmalloc(sizeof(struct Node));
	tmp->type = type;
	tmp->tData = d;
	
	return tmp;
}

//structure that stores metadata about program
typedef struct meta
{
	int ifStatementsInUse;
	int ifStatementsDeclared;
	TStack_t labelStackIf;

	int whileStatementsInUse;
	int whileStatementsDeclared;
	TStack_t labelStackWhile;

	int intVarInUse;
	int intVarDeclared;

	int doubleVarInUse;
	int doubleVarDeclared;

	int boolVarInUse;
	int boolVarDeclared;

	int stringVarInUse;
	int stringVarDeclared;

	int submerge;
} tMetaData;

//definition of posible values used in metadata
enum metaMember
{
	intVar,
	doubleVar,
	ifStatement,
	whileStatement,
	boolVar,
	stringVar,
	submergion,

};

// updates values in metadata
void metaDec(enum metaMember memb, tMetaData* meta)
{
	switch (memb)
	{
	case ifStatement:
	{
		meta->ifStatementsInUse--;
		StackTopPop(&meta->labelStackIf);
	}
		break;
	case whileStatement:
	{
		meta->whileStatementsInUse--;
		StackTopPop(&meta->labelStackWhile);
	}
		break;
	case intVar: meta->intVarInUse--;
		break;
	case doubleVar: meta->doubleVarInUse--;
		break;
	case boolVar: meta->boolVarInUse--;
		break;
	case stringVar: meta->stringVarInUse--;
		break;
	case submergion: meta->submerge--;
	}
}

//updates values in metadata
void metaInc(enum metaMember memb, tMetaData* meta)
{
	switch (memb)
	{
	case ifStatement: 
	{	

		StackPush(&meta->labelStackIf, (void *)meta->ifStatementsDeclared);
		meta->ifStatementsDeclared++;
		meta->ifStatementsInUse++;
	}
	break;
	case whileStatement:
	{
		StackPush(&meta->labelStackWhile, (void *)meta->whileStatementsDeclared);
		meta->whileStatementsDeclared++;
		meta->whileStatementsInUse++;
	}
	break;
	case intVar:
	{
		if (meta->intVarInUse == meta->intVarDeclared)
		{
			meta->intVarDeclared++;
			fprintf(stdout, "DEFVAR LF@_intVar%d\n", meta->intVarInUse+1);
			fprintf(stdout, "MOVE LF@_intVar%d int@0\n", meta->intVarInUse + 1);
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
			fprintf(stdout, "MOVE LF@_floatVar%d float@0.0\n", meta->doubleVarInUse + 1);
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
			fprintf(stdout, "MOVE LF@_boolVar%d bool@false\n", meta->boolVarInUse + 1);
		}
		meta->boolVarInUse++;
	}
	break;
	case stringVar:
	{
		if (meta->stringVarInUse == meta->stringVarDeclared)
		{
			meta->stringVarDeclared++;
			fprintf(stdout, "DEFVAR LF@_stringVar%d\n", meta->stringVarInUse+1);

		}
		meta->stringVarInUse++;
	}
	case submergion: meta->submerge++;
		break;
	default:
		break;
	}
}

//recognizes Node subset of statements 
void StatementRecognize(struct NodeStatement* statement, struct meta* metadata)
{
	switch (statement->type)
	{
	case varDeclaration:	Recognize(wrapa(statement->type, (union Data)statement->tStatementNode.variable_declaration), metadata);
		break;
	case varAssigment: Recognize(wrapa(statement->type, (union Data)statement->tStatementNode.variable_assigment), metadata);
		break;
	case scope: Recognize(wrapa(statement->type, (union Data)statement->tStatementNode.scope), metadata);
		break;
	case ifCondition: Recognize(wrapa(statement->type, (union Data)statement->tStatementNode.ifBlock), metadata);
		break;
	case whileBlock:Recognize(wrapa(statement->type, (union Data)statement->tStatementNode.whileBlock), metadata);
		break;
	case print:Recognize(wrapa(statement->type, (union Data)statement->tStatementNode.printStatement), metadata);
		break;
	case input:Recognize(wrapa(statement->type, (union Data)statement->tStatementNode.inputStatement), metadata);
		break;
	case empty:Recognize(wrapa(statement->type, (union Data)statement->tStatementNode.inputStatement), metadata);
		break;
	default: fprintf(stderr, "###### StatementRecognize something else #######\n");
		break;
	}
}

//determinates if there is nesting in expression 
bool IsAnotherExp(struct Node* actualNode, bool side)
{
	if (side)//left
	{
		if (actualNode->tData.binaryExpression->left->type == binaryExpression ||
			actualNode->tData.binaryExpression->left->type == expression ||
			actualNode->tData.binaryExpression->left->type == prefixExpression ||
			actualNode->tData.binaryExpression->left->type == negationExpression)
		{
			return true;
		}
	}
	else //right
	{
		if (actualNode->tData.binaryExpression->right->type == binaryExpression ||
			actualNode->tData.binaryExpression->right->type == expression ||
			actualNode->tData.binaryExpression->right->type == prefixExpression ||
			actualNode->tData.binaryExpression->right->type == negationExpression)
		{
			return true;
		}
	}return false;
	

	
}

//prints return value first operand and second operand of binary expression
void BinaryPrintOperands(struct Node* actualNode, struct meta* met)
{
	ScalarType resType = actualNode->tData.binaryExpression->resultType;
	if (actualNode->tData.binaryExpression->OP != T_ADD &&
		actualNode->tData.binaryExpression->OP != T_SUB &&
		actualNode->tData.binaryExpression->OP != T_MULTIPLY &&
		actualNode->tData.binaryExpression->OP != T_DIVIDE &&
		actualNode->tData.binaryExpression->OP != T_INTDIVIDE)
	{
		resType = TYPE_String;
	}

	if ((IsAnotherExp(actualNode, true) && IsAnotherExp(actualNode, false))) //there is lefside nesting and right side nesting
	{
		PrintOperands(actualNode->tData.binaryExpression->resultType,resType, NULL, NULL, met);
	}
	else if (IsAnotherExp(actualNode, true)) //only left nesting
	{
		PrintOperands(actualNode->tData.binaryExpression->resultType,resType, NULL, actualNode->tData.binaryExpression->right, met);
	}
	else if (IsAnotherExp(actualNode, false)) // only right nesting
	{
		PrintOperands(actualNode->tData.binaryExpression->resultType,resType, actualNode->tData.binaryExpression->left, NULL, met);
	}
	else // no nesting at all
	{
		PrintOperands(actualNode->tData.binaryExpression->resultType,resType, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
	}
}
// helper method for BinaryPrintOperands
void PrintOperands(ScalarType type,ScalarType restype, struct Node* lop, struct Node* rop, struct meta* met)
{
		if (restype == TYPE_Integer) fprintf(stdout, "LF@_intVar%d ", met->intVarInUse);
		else if (restype == TYPE_Double) fprintf(stdout, "LF@_floatVar%d ", met->doubleVarInUse);
		else if (restype == TYPE_String) fprintf(stdout, "LF@_boolVar%d ", met->boolVarInUse); // todo replace for bool
	
	

	if (lop != NULL)
	{
		Recognize(lop, met);
	}
	else
	{
		if (type == TYPE_Integer) fprintf(stdout, "LF@_intVar%d ", met->intVarInUse);
		else if (type == TYPE_Double) fprintf(stdout, "LF@_floatVar%d ", met->doubleVarInUse);
		else if (type == TYPE_String) fprintf(stdout, "LF@_boolVar%d ", met->boolVarInUse);
	}
	fprintf(stdout, " ");

	if (rop != NULL)
	{
		Recognize(rop, met);
	}
	else
	{
		if (type == TYPE_Integer) fprintf(stdout, "LF@_intVar%d ", met->intVarInUse);
		else if (type == TYPE_Double) fprintf(stdout, "LF@_floatVar%d ", met->doubleVarInUse);
		else if (type == TYPE_String) fprintf(stdout, "LF@_boolVar%d ", met->boolVarInUse);
	}
	fprintf(stdout, "\n");
}


//Recursive method for recognizing of ADT
void Recognize(struct Node* root, struct meta* metadata)
{
	struct Node* actualNode = root;
	struct meta* met = metadata;
	if (root != NULL)
	{
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
			fprintf(stdout, "string@%s", actualNode->tData.stringValue->value);
		}
		break;
		case varDeclaration:
		{
			fprintf(stdout, "DEFVAR LF@%s\n", actualNode->tData.variable_declaration->id);
			if (actualNode->tData.variable_declaration->Expression != NULL) //var dec has also expression
			{
				switch (actualNode->tData.variable_declaration->varType)
				{
				case TYPE_Integer: fprintf(stdout, "MOVE LF@%s ", actualNode->tData.variable_declaration->id);
					break;
				case TYPE_Double: fprintf(stdout, "MOVE LF@%s ", actualNode->tData.variable_declaration->id);
					break;
				case TYPE_String: fprintf(stdout, "MOVE LF@%s ", actualNode->tData.variable_declaration->id);
				}

				Recognize(actualNode->tData.variable_declaration->Expression, met);
				fprintf(stdout, "\n");
			}
			else // only var dec
			{
				switch (actualNode->tData.variable_declaration->varType)
				{
				case TYPE_Integer: fprintf(stdout, "MOVE LF@%s int@0\n", actualNode->tData.variable_declaration->id);
					break;
				case TYPE_Double: fprintf(stdout, "MOVE LF@%s float@0.0\n", actualNode->tData.variable_declaration->id);
					break;
				case TYPE_String: fprintf(stdout, "MOVE LF@%s string@\n", actualNode->tData.variable_declaration->id);
				}
			}
		}
		break;
		case varAssigment:
		{
			switch (actualNode->tData.variable_assigment->varType)
			{
			case TYPE_String:
			{
				Recognize(wrapa(stringVal, (union Data)actualNode->tData.variable_assigment->Expression->tData), met);
			}
			break;
			case TYPE_Integer:
			{
				if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == integerVal) //simple var assigment
				{
					fprintf(stdout, "MOVE LF@%s ", actualNode->tData.variable_assigment->id);
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					fprintf(stdout, "\n");
				}
				else if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == expression) //var assig with expression, first need resolve expression then assigment
				{
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					fprintf(stdout, "MOVE LF@%s LF@_intVar%d\n", actualNode->tData.variable_assigment->id, met->intVarInUse+1);
				}
				else if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == binaryExpression)//var assig with bin expression, first need resolve expression then assigment
				{
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->tData.binaryExpression->left->type == binaryExpression) // there will be nesting
					{
						fprintf(stdout, "MOVE LF@%s LF@_intVar%d\n", actualNode->tData.variable_assigment->id, met->intVarInUse+1);
					}
					else //simple expression resoolve
					{
						fprintf(stdout, "MOVE LF@%s LF@_intVar%d\n", actualNode->tData.variable_assigment->id, met->intVarInUse+1);
					}
					
				}
				else if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == functionCall)
				{
					Recognize(actualNode->tData.functionCall, met);
					
					switch (actualNode->tData.functionCall->result)
					{
					case TYPE_Integer:
						break;
					case TYPE_Double:
						break;
					case TYPE_String:
						break;
					default:
						break;
					}
				}

			}
			break;
			case TYPE_Double:
			{
				if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == doubleVal) //simple var assigment
				{
					fprintf(stdout, "MOVE LF@%s ", actualNode->tData.variable_assigment->id);
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					fprintf(stdout, "\n");
				}
				else if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == expression) //var assig with expression, first need resolve expression then assigment
				{
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					fprintf(stdout, "MOVE LF@%s LF@_floatVar%d\n", actualNode->tData.variable_assigment->id, met->doubleVarInUse);
				}
				else if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == binaryExpression)//var assig with bin expression, first need resolve expression then assigment
				{
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->tData.expression->expression->tData.binaryExpression->left->type == binaryExpression) // there will be nesting
					{
						fprintf(stdout, "MOVE LF@%s LF@_floatVar%d\n", actualNode->tData.variable_assigment->id, met->doubleVarInUse - 1);
					}
					else
					{
						fprintf(stdout, "MOVE LF@%s LF@_floatVar%d\n", actualNode->tData.variable_assigment->id, met->doubleVarInUse);
					}
					
				}
			}
			break;
			}


		}
		break;
		case expression:
		{
			Recognize(actualNode->tData.expression->expression, met);
		}
		break;
		case scope:
		{
			fprintf(stdout, "CREATEFRAME\n");
			fprintf(stdout, "PUSHFRAME\n");
			Recognize(wrapa(statement, (union Data)actualNode->tData.scope->Statement), met);
			fprintf(stdout, "POPFRAME\n");

		}
		break;
		case statement:
		{
			StatementRecognize(actualNode->tData.statement, met);
			if (actualNode->tData.statement->Next != NULL)
				Recognize(wrapa(statement, (union Data)actualNode->tData.statement->Next), met);
		}
		break;
		case ifCondition:
		{
			metaInc(ifStatement, met);
			Recognize(actualNode->tData.ifStatement->Condition, met); // IFSTATEMENT CONDITION
			fprintf(stdout, "JUMPIFNEQ _ifStatementElse%d LF@_boolVar%d bool@true\n", (int)StackTop(&met->labelStackIf) , met->boolVarInUse+1);
			if(actualNode->tData.ifStatement->Pass != NULL) Recognize(actualNode->tData.ifStatement->Pass, met);			// PASS BLOCK
			fprintf(stdout, "JUMP _IfStatementConditionEnd%d\n", (int)StackTop(&met->labelStackIf));					// JUMP to the end of if statment in case of pass
			//metaDec(boolVar, met)

			if (actualNode->tData.ifStatement->Fail != NULL)									// FAIL BLOCK
			{
				fprintf(stdout, "LABEL _ifStatementElse%d\n", (int)StackTop(&met->labelStackIf));
				if (actualNode->tData.ifStatement->Fail->type == varAssigment)
				{
					StatementRecognize(actualNode->tData.ifStatement->Fail, met);
					fprintf(stdout, "\n");
					Recognize(actualNode->tData.ifStatement->Fail->Next, met);
				}
				else
				{
					StatementRecognize(actualNode->tData.ifStatement->Fail, met);
				}
			}



			if (actualNode->tData.ifStatement->elseIf != NULL)  StatementRecognize(actualNode->tData.ifStatement->elseIf, met);
			
			fprintf(stdout, "LABEL _IfStatementConditionEnd%d\n", (int)StackTop(&met->labelStackIf)); // this is end of if statement
			metaDec(ifStatement, met);
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
			fprintf(stdout, "JUMP _WhileStatementCondition%d\n", (int)StackTop(&met->labelStackWhile));
			fprintf(stdout, "LABEL _WhileStatementStart%d\n", (int)StackTop(&met->labelStackWhile));

			StatementRecognize(actualNode->tData.whileBlock->Statement, met);

			fprintf(stdout, "LABEL _WhileStatementCondition%d\n", (int)StackTop(&met->labelStackWhile));
			Recognize(actualNode->tData.whileBlock->Condition, met);
			fprintf(stdout, "JUMPIFEQ _WhileStatementStart%d LF@_boolVar%d bool@true\n", (int)StackTop(&met->labelStackWhile), met->boolVarInUse+1);
			metaDec(boolVar, met);
			metaDec(whileStatement, met);





		}
		break;
		case binaryExpression:
		{
			if (IsAnotherExp(actualNode, true)) // left nesting
			{
				met->submerge++;
				Recognize(actualNode->tData.binaryExpression->left, met);
				met->submerge--;
			}
			if (IsAnotherExp(actualNode, false)) //right nesting
			{
				met->submerge++;
				Recognize(actualNode->tData.binaryExpression->right, met);
				met->submerge--;
			}
			


			switch (actualNode->tData.binaryExpression->OP)
			{
			case T_ADD:
			{
				
				metaInc(actualNode->tData.binaryExpression->resultType, met);
				fprintf(stdout, "ADD ");
				BinaryPrintOperands(actualNode, met);
				metaDec(actualNode->tData.binaryExpression->resultType, met);				
			}
			break;
			case T_SUB:
			{
				metaInc(actualNode->tData.binaryExpression->resultType, met);
				fprintf(stdout, "SUB ");
				BinaryPrintOperands(actualNode, met);
				metaDec(actualNode->tData.binaryExpression->resultType, met);
			}
			break;
			case T_MULTIPLY:
			{
				metaInc(actualNode->tData.binaryExpression->resultType, met);
				fprintf(stdout, "MUL ");
				BinaryPrintOperands(actualNode, met);
				metaDec(actualNode->tData.binaryExpression->resultType, met);
			}
			break;
			case T_INTDIVIDE:
			{
				metaInc(actualNode->tData.binaryExpression->resultType, met);
				fprintf(stdout, "DIV ");
				BinaryPrintOperands(actualNode, met);
				metaDec(actualNode->tData.binaryExpression->resultType, met);
			}
			break;
			case T_DIVIDE:
			{
				metaInc(actualNode->tData.binaryExpression->resultType, met);
				fprintf(stdout, "DIV ");
				BinaryPrintOperands(actualNode, met);
				metaDec(actualNode->tData.binaryExpression->resultType, met);
			}
			break;
			case T_ASSIGN: // also equal
			{
				metaInc(boolVar, met);
				fprintf(stdout, "EQ ");
				BinaryPrintOperands(actualNode, met);
				metaDec(boolVar, met);
			}
			break;
			case T_NOTEQUAL:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "EQ ");
				BinaryPrintOperands(actualNode, met); // check if equal
				
				//creating fake negation node
				struct Node* nd = mmalloc(sizeof(struct Node));
				struct Node* nd2 = mmalloc(sizeof(struct Node));
				struct Node* wrapNd = mmalloc(sizeof(struct Node));
				struct NodeExpression* ndngex = mmalloc(sizeof(struct NodeExpression));
				struct NodeExpression* exnd = mmalloc(sizeof(struct NodeExpression));
				struct NodeIdentifier* idnd = mmalloc(sizeof(struct NodeIdentifier));

				nd->type = negationExpression;
				nd->tData = (union Data)ndngex;
				ndngex->expression = nd2;
				ndngex->ResultType = actualNode->tData.binaryExpression->resultType;
				nd2->type = expression;
				nd2->tData = (union Data)exnd;
				exnd->ResultType = actualNode->tData.binaryExpression->resultType;
				exnd->expression = wrapNd;
				wrapNd->type = identifier;
				wrapNd->tData = (union Data)idnd;

				char* s1 = "_boolVar";
				char* s2 = mmalloc(sizeof(char));
				int i = sizeof(char);
				sprintf(s2, "%d", i);
				char *result = mmalloc(strlen(s1) + strlen(s2) + 1);
				strcpy(result, s1);
				strcat(result, s2);
				mfree(s2);
				idnd->id = result;
				idnd->type = actualNode->tData.binaryExpression->resultType;
				Recognize(nd, met);
				metaDec(boolVar, met);
				

			}
			break;
			case T_LESS:
			{
				metaInc(actualNode->tData.binaryExpression->resultType, met);
				metaInc(boolVar, met);
				fprintf(stdout, "LS ");
				BinaryPrintOperands(actualNode, met);
				metaDec(boolVar, met);
				metaDec(actualNode->tData.binaryExpression->resultType, met);
			}
			break;
			case T_GREATER:
			{
				metaInc(actualNode->tData.binaryExpression->resultType, met);
				metaInc(boolVar, met);
				fprintf(stdout, "GT ");
				BinaryPrintOperands(actualNode, met);
				metaDec(boolVar, met);
				metaDec(actualNode->tData.binaryExpression->resultType, met);
			}
			break;
			case T_GREATEROREQUAL:
			{
				metaInc(boolVar, met);
				
				if (actualNode->tData.binaryExpression->right->type == expression) //nesting
				{
					fprintf(stdout, "GT LF@_boolVar%d ", met->boolVarInUse);
					Recognize(actualNode->tData.binaryExpression->left, met);
					switch (actualNode->tData.binaryExpression->resultType)
					{
					case TYPE_Integer:fprintf(stdout, " LF@_intVar%d\n", met->intVarInUse + 1);
						break;
					case TYPE_Double:fprintf(stdout, " LF@_floatVar%d\n", met->doubleVarInUse + 1);
					default:
						break;
					}
					metaInc(boolVar, met);
					fprintf(stdout, "EQ LF@_boolVar%d ",met->boolVarInUse);
					Recognize(actualNode->tData.binaryExpression->left, met);
					switch (actualNode->tData.binaryExpression->resultType)
					{
					case TYPE_Integer:fprintf(stdout, " LF@_intVar%d\n", met->intVarInUse + 1);
						break;
					case TYPE_Double:fprintf(stdout, " LF@_floatVar%d\n", met->doubleVarInUse + 1);
					default:
						break;
						
					}
					fprintf(stdout, "OR LF@_boolVar%d LF@_boolVar%d LF@_boolVar%d\n", met->boolVarInUse, met->boolVarInUse-1, met->boolVarInUse);
					metaDec(boolVar, met);
				}
				else //simple or totaty submerged expression
				{
					fprintf(stdout, "GT ");
				BinaryPrintOperands(actualNode, met);
					//metaInc(boolVar, met);
					struct Node* nd = mmalloc(sizeof(struct Node));
					struct Node* nd2 = mmalloc(sizeof(struct Node));
					struct Node* wrapNd = mmalloc(sizeof(struct Node));
					struct NodeBinaryExpression* ndngex = mmalloc(sizeof(struct NodeBinaryExpression));
					struct NodeExpression* exnd = mmalloc(sizeof(struct NodeExpression));
					struct NodeIdentifier* idnd = mmalloc(sizeof(struct NodeIdentifier));

					nd->type = binaryExpression;
					nd->tData = (union Data)ndngex;

					ndngex->left = actualNode->tData.binaryExpression->left;
					ndngex->right = actualNode->tData.binaryExpression->right;
					ndngex->resultType = actualNode->tData.binaryExpression->resultType;
					ndngex->OP = T_ASSIGN;
					Recognize(nd, met);
					fprintf(stdout, "OR LF@_boolVar%d LF@_boolVar%d LF@_boolVar%d\n", met->boolVarInUse, met->boolVarInUse, met->boolVarInUse + 1);
				}
				
				metaDec(boolVar, met);
				//metaDec(boolVar, met);
				
			}
			break;
			case T_LESSEROREQUAL:
			{
				metaInc(boolVar, met);
				if (actualNode->tData.binaryExpression->right->type == expression)// nesting
				{
					fprintf(stdout, "LT LF@_boolVar%d ", met->boolVarInUse);
					Recognize(actualNode->tData.binaryExpression->left, met);
					switch (actualNode->tData.binaryExpression->resultType)
					{
					case TYPE_Integer:fprintf(stdout, " LF@_intVar%d\n", met->intVarInUse + 1);
						break;
					case TYPE_Double:fprintf(stdout, " LF@_floatVar%d\n", met->doubleVarInUse + 1);
					default:
						break;
					}
					metaInc(boolVar, met);
					fprintf(stdout, "EQ LF@_boolVar%d ", met->boolVarInUse);
					Recognize(actualNode->tData.binaryExpression->left, met);
					switch (actualNode->tData.binaryExpression->resultType)
					{
					case TYPE_Integer:fprintf(stdout, " LF@_intVar%d\n", met->intVarInUse + 1);
						break;
					case TYPE_Double:fprintf(stdout, " LF@_floatVar%d\n", met->doubleVarInUse + 1);
					default:
						break;

					}
					fprintf(stdout, "OR LF@_boolVar%d LF@_boolVar%d LF@_boolVar%d\n", met->boolVarInUse, met->boolVarInUse - 1, met->boolVarInUse);
					metaDec(boolVar, met);
				}
				else  //simple or totaty submerged expression
				{
					fprintf(stdout, "LT ");
					BinaryPrintOperands(actualNode, met);
					//metaInc(boolVar, met);
					struct Node* nd = mmalloc(sizeof(struct Node));
					struct Node* nd2 = mmalloc(sizeof(struct Node));
					struct Node* wrapNd = mmalloc(sizeof(struct Node));
					struct NodeBinaryExpression* ndngex = mmalloc(sizeof(struct NodeBinaryExpression));
					struct NodeExpression* exnd = mmalloc(sizeof(struct NodeExpression));
					struct NodeIdentifier* idnd = mmalloc(sizeof(struct NodeIdentifier));

					nd->type = binaryExpression;
					nd->tData = (union Data)ndngex;

					ndngex->left = actualNode->tData.binaryExpression->left;
					ndngex->right = actualNode->tData.binaryExpression->right;
					ndngex->resultType = actualNode->tData.binaryExpression->resultType;
					ndngex->OP = T_ASSIGN;
					Recognize(nd, met);
					fprintf(stdout, "OR LF@_boolVar%d LF@_boolVar%d LF@_boolVar%d\n", met->boolVarInUse, met->boolVarInUse, met->boolVarInUse + 1);
					//PrintOperands(TYPE_String, NULL, NULL, met);
				}
				
				metaDec(boolVar, met);
				//metaDec(boolVar, met);
			}
			break;
			case T_AND:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "AND ");
				BinaryPrintOperands(actualNode, met);
			}
			break;
			case T_OR:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "OR ");
				BinaryPrintOperands(actualNode, met);
			}
			break;
				
			}
			
			
		}
		break;
		case prefixExpression:
		{
		}
		break;
		case negationExpression:
		{
			fprintf(stdout, "NOT ");
			Recognize(actualNode->tData.negationExpression->expression, met);
			fprintf(stdout, "\n");
		}
		break;
		case identifier:
		{
			fprintf(stdout, "LF@%s", actualNode->tData.identifier->id);
		}
		break;
		case empty:
		break;
		case input:
		{
			
			switch (actualNode->tData.input->identifier->type)
			{
			case TYPE_Integer:
			{
				fprintf(stdout, "READ ");
				Recognize(wrapa(identifier, (union Data)actualNode->tData.input->identifier), met);
				fprintf(stdout, " int\n");
				

			}
			break;
			case TYPE_String:
			{
				fprintf(stdout, "READ ");
				Recognize(wrapa(identifier, (union Data)actualNode->tData.input->identifier), met);
				fprintf(stdout, " string\n");
			}
			break;
			case TYPE_Double:
			{
				fprintf(stdout, "READ ");
				Recognize(wrapa(identifier, (union Data)actualNode->tData.input->identifier), met);
				fprintf(stdout, " float\n");
			}
			break;
			}
			fprintf(stdout, "WRITE string@?\\032\n");
		}
		break;
		case print:
		{
			if (actualNode->tData.print->Expression->tData.expression->expression->type == expression ||   //nesting
				actualNode->tData.print->Expression->tData.expression->expression->type == binaryExpression ||
				actualNode->tData.print->Expression->tData.expression->expression->type == negationExpression)
			{
				switch (actualNode->tData.print->Expression->tData.expression->expression->tData.expression->ResultType)
				{
				case TYPE_Integer: 
				{
					metaInc(intVar, met);
					Recognize(actualNode->tData.print->Expression, met);
					fprintf(stdout, "WRITE LF@_intVar%d\n",met->intVarInUse+1);
					metaDec(intVar, met);
				}

					break;
				case TYPE_Double: 
				{
					metaInc(doubleVar, met);
					Recognize(actualNode->tData.print->Expression, met);
					fprintf(stdout, "WRITE LF@_floatVar%d\n", met->doubleVarInUse+1);
					metaDec(intVar, met);
				}
				break;
				case functionCall:
				{
					//actualNode->tData.functionCall.
				}
				break;
					
				}
			}
			else
			{
				fprintf(stdout, "WRITE ");
				Recognize(actualNode->tData.print->Expression, met);
				fprintf(stdout, "\n");
				if (actualNode->tData.print->nextPrint != NULL)
				{
					StatementRecognize(wrapa(print, (union Data)actualNode->tData.print->nextPrint), met);
				}
			}
			
		}
		break;
		}
	}
		
}



void Generate(tProgram* program)
{
	struct meta* metaData = (struct meta*)mmalloc(sizeof(struct meta));
	metaData->ifStatementsInUse = 0;
	metaData->ifStatementsDeclared = 0;
	StackInit(&metaData->labelStackIf);

	metaData->whileStatementsInUse = 0;
	metaData->whileStatementsDeclared = 0;
	StackInit(&metaData->labelStackWhile);

	metaData->intVarInUse = 0;
	metaData->intVarDeclared = 0;

	metaData->doubleVarInUse = 0;
	metaData->doubleVarDeclared = 0;

	metaData->boolVarInUse = 0;
	metaData->boolVarDeclared = 0;
	metaData->stringVarInUse = 0;
	metaData->stringVarDeclared = 0;
	metaData->submerge = 0;


	tProgram* prg = program;
	fprintf(stdout, ".IFJcode17\n");
	Recognize(prg->Main, metaData);
}
