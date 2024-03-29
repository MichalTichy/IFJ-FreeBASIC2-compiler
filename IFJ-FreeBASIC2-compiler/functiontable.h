/**
*	Project: IFJ17 Compiler
*
*	FILE: functiontable.h
*
*	File author:
*	  Ondrej Deingruber, xdeing00
*
*	Project authors:
*	  Michal Tichy, xtichy26
*	  Michal Martinu, xmarti78
*	  Gabriel Mastny, xmastn02
*	  Ondrej Deingruber, xdeing00
*
**/

#pragma once
#ifndef FUNCTIONTABLE
#define FUNCTIONTABLE

#include "Scanner.h"
#include "Parser.h"
#include <stdbool.h>

typedef struct tParamStruct
{
	char* name;
	ScalarType type;
} tParam;

typedef struct tFTItem
{
	tParam* parametersArr;
	char* data;
	bool declarationOnly;
	struct Function* body;
	unsigned int parametersCount;
	unsigned int parametersMax;
	unsigned int len;
	ScalarType returnValue;
	struct tFTItem* lptr;
	struct tFTItem* rptr;
} *tFTItemPtr;

void FTInit(tFTItemPtr* tableptr);

tFTItemPtr FTSearch(tFTItemPtr* tableptr, char* token);

void AddParemeter(tFTItemPtr itemptr, char* paramName, ScalarType type);

void AddReturnValue(tFTItemPtr itemptr, ScalarType type);

tFTItemPtr FTInsert(tFTItemPtr* tableptr, char* token, bool isDeclaration);

void FTRemove(tFTItemPtr* funItem, char* token);

void FTFree(tFTItemPtr* tableptr);

void CompareParameterSignature(tFTItemPtr item, unsigned int position, char* name, ScalarType type);

bool FTIsDefinitionOnly(tFTItemPtr* tablePtr);

#endif
