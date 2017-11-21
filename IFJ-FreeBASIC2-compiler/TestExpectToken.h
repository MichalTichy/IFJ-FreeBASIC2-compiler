#pragma once

#include "Scanner.h"
#include "Tests.h"

int Exp_ID(char* expectedString);
int Exp_ERR();
int Exp_EOF();
int Exp_EOL();
int Exp_INTVALUE(int expected);
int Exp_DOUBLEVALUE(double expected);
int Exp_STRINGVALUE(char* expectedString);
int Exp_ADD();
int Exp_SUB();
int Exp_MULTIPLY();
int Exp_DIVIDE();
int Exp_INTDIVIDE();
int Exp_SEMICOLON();
int Exp_COLON();
int Exp_LEFTBRACKET();
int Exp_RIGHTBRACKET();
int Exp_ASSIGN();
int Exp_NOTEQUAL();
int Exp_LESS();
int Exp_GREATER();
int Exp_GREATEROREQUAL();
int Exp_LESSEROREQUAL();
int Exp_AS();
int Exp_ASC();
int Exp_DECLARE();
int Exp_DIM();
int Exp_DO();
int Exp_DOUBLE();
int Exp_ELSE();
int Exp_END();
int Exp_CHR();
int Exp_FUNCTION();
int Exp_IF();
int Exp_INPUT();
int Exp_DOUBLE();
int Exp_INTEGER();
int Exp_LENGHT();
int Exp_LOOP();
int Exp_PRINT();
int Exp_RETURN();
int Exp_SCOPE();
int Exp_STRING();
int Exp_SUBSTRING();
int Exp_THEN();
int Exp_WHILE();
int Exp_RESERVEDWORD();






