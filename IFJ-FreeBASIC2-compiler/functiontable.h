#pragma once
#ifndef FUNCTIONTABLE
#define FUNCTIONTABLE

#include "Scanner.h"
#include "Parser.h"


typedef struct tFTItem
{
	char** parameters;
	char* data;
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

tFTItemPtr FTInsert(tFTItemPtr* tableptr, char* token);

void FTRemove(tFTItemPtr* funItem, char* token);

void FTFree(tFTItemPtr* tableptr);
#endif
