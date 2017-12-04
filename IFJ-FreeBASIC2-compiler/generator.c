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
} tMetaData;

enum metaMember
{
	intVar,
	doubleVar,
	ifStatement,
	whileStatement,
	boolVar

};


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

void PrintOperands(ScalarType type, struct Node* lop, struct Node* rop, struct meta* met)
{
	if (type == TYPE_Integer) fprintf(stdout, "LF@_intVar%d ", met->intVarInUse);
	else if (type == TYPE_Double) fprintf(stdout, "LF@_floatVar%d ", met->doubleVarInUse);
	else if (type == TYPE_String) fprintf(stdout, "LF@_boolVar%d ", met->boolVarInUse); // todo replace for bool

	if (lop != NULL)
	{
		Recognize(lop, met);
	}
	else
	{
		if (type == TYPE_Integer) fprintf(stdout, "LF@_intVar%d ", met->intVarInUse-1);
		else if (type == TYPE_Double) fprintf(stdout, "LF@_floatVar%d ", met->doubleVarInUse-1);
		else if (type == TYPE_String) fprintf(stdout, "LF@_boolVar%d ", met->boolVarInUse-1);
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

				Recognize(actualNode->tData.variable_declaration->Expression, met);
				//fprintf(stdout, "\n");
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
				if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == integerVal)
				{
					fprintf(stdout, "MOVE LF@_%s ", actualNode->tData.variable_assigment->id);
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					fprintf(stdout, "\n");
				}
				else if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == expression)
				{
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					fprintf(stdout, "MOVE LF@_%s LF@_intVar%d\n", actualNode->tData.variable_assigment->id, met->intVarInUse);
				}
				else fprintf(stderr, "######### case var asig type Integer something elese ########");

			}
			break;
			case TYPE_Double:
			{
				if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == doubleVal)
				{
					fprintf(stdout, "MOVE LF@_%s ", actualNode->tData.variable_assigment->id);
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					fprintf(stdout, "\n");
				}
				else if (actualNode->tData.variable_assigment->Expression->tData.expression->expression->type == expression)
				{
					Recognize(actualNode->tData.variable_assigment->Expression, met);
					fprintf(stdout, "MOVE LF@_%s LF@_doubleVar%d\n", actualNode->tData.variable_assigment->id, met->doubleVarInUse);
				}
				else fprintf(stderr, "######### case var asig type double something elese ########");
			}
			break;
			}


		}
		break;
		case expression:
		{

			if (actualNode->tData.expression->ResultType == TYPE_Integer || actualNode->tData.expression->ResultType == TYPE_Double)
			{
				Recognize(actualNode->tData.expression->expression, met);
			}
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
			fprintf(stdout, "JUMPIFNEQ _ifStatementElse%d LF@_boolVar%d bool@true\n", (int)StackTop(&met->labelStackIf) , met->boolVarInUse);
			metaDec(boolVar, met);
			if(actualNode->tData.ifStatement->Pass != NULL) Recognize(actualNode->tData.ifStatement->Pass, met);			// PASS BLOCK
			fprintf(stdout, "JUMP _IfStatementConditionEnd%d\n", (int)StackTop(&met->labelStackIf));					// JUMP to the end of if statment in case of pass


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
			fprintf(stdout, "JUMPIFEQ _WhileStatementStart%d LF@_boolVar%d bool@true\n", (int)StackTop(&met->labelStackWhile), met->boolVarInUse);
			metaDec(boolVar, met);
			metaDec(whileStatement, met);





		}
		break;
		case binaryExpression:
		{


			switch (actualNode->tData.binaryExpression->OP)
			{
			case T_ADD:
			{
				metaInc(actualNode->tData.binaryExpression->resultType, met);
				fprintf(stdout, "ADD ");
				PrintOperands(actualNode->tData.binaryExpression->resultType, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
			}
			break;
			case T_SUB:
			{
				metaInc(actualNode->tData.binaryExpression->OP, met);
				fprintf(stdout, "SUB ");
				PrintOperands(actualNode->tData.binaryExpression->resultType, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
			}
			break;
			case T_MULTIPLY:
			{
				metaInc(actualNode->tData.binaryExpression->OP, met);
				fprintf(stdout, "MUL ");
				PrintOperands(actualNode->tData.binaryExpression->resultType, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
			}
			break;
			case T_ASSIGN: // also equal
			{
				metaInc(boolVar, met);
				fprintf(stdout, "EQ ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
			}
			case T_NOTEQUAL:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "EQ ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
				fprintf(stdout, "NOT LF@_boolVar%d", met->boolVarInUse);
			}
			break;
			case T_LESS:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "LS ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
			}
			break;
			case T_GREATER:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "GT ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
			}
			break;
			case T_GREATEROREQUAL:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "GT ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
				metaInc(boolVar, met);
				fprintf(stdout, "EQ ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
				fprintf(stdout, "OR ");
				PrintOperands(boolVar, NULL, NULL, met);
				metaDec(boolVar, met);
			}
			break;
			case T_LESSEROREQUAL:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "LS ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
				metaInc(boolVar, met);
				fprintf(stdout, "EQ ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
				fprintf(stdout, "OR ");
				PrintOperands(boolVar, NULL, NULL, met);
				metaDec(boolVar, met);
			}
			break;
			case T_AND:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "AND ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
			}
			break;
			case T_OR:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "OR ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
			}
			break;
			case T_NOT:
			{
				metaInc(boolVar, met);
				fprintf(stdout, "NOT ");
				PrintOperands(boolVar, actualNode->tData.binaryExpression->left, actualNode->tData.binaryExpression->right, met);
			}
			default: fprintf(stderr, "#### case binary expression op #####");
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
			fprintf(stderr, "neg\n");
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
				metaInc(intVar, met);
				fprintf(stdout, "!\"? \"\n");
				fprintf(stdout, "READ LF@_intVar%d int", met->intVarInUse);
				metaDec(intVar, met);
			}
			default:
				break;
			}
		}
		break;
		case print:
		{
			fprintf(stdout, "WRITE string@");
			Recognize(actualNode->tData.print->Expression, met);
			if (actualNode->tData.print->nextPrint != NULL) StatementRecognize(wrapa(print, (union Data)actualNode->tData.print->nextPrint), met);
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

	tProgram prg = *program;
	fprintf(stdout, ".IFJcode17\n");
	Recognize(program->Main, metaData);

}

