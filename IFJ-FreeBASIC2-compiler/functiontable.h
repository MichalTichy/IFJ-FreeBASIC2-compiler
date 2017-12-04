#pragma once
#ifndef FUNCTIONTABLE
#define FUNCTIONTABLE

#include "Scanner.h"
#include "Parser.h"

typedef struct
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

void AddParemeter(tFTItemPtr* funItem, char* name, ScalarType type);

void AddReturnValue(tFTItemPtr* funItem, char* name, ScalarType type);

tFTItemPtr FTInsert(tFTItemPtr* tableptr, char* token, bool isDeclaration);

void FTRemove(tFTItemPtr* funItem, char* token);

void FTFree(tFTItemPtr* tableptr);

void CompareParameterSignature(tFTItemPtr item, unsigned int position, char* name, ScalarType type);

#endif
