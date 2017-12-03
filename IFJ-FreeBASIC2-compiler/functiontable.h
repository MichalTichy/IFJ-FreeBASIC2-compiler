#pragma once
#ifndef FUNCTIONTABLE
#define FUNCTIONTABLE

#include "Scanner.h"
#include "Parser.h";


typedef struct tFTItem
{
	char** parameters;
	char* data;
	tFunction* body;
	unsigned int len;
	struct tFTItem* lptr;
	struct tFTItem* rptr;
} *tFTItemPtr;

void FTInit(tFTItemPtr* tableptr);

tFTItemPtr FTSearch(tFTItemPtr* tableptr, char* token);

void AddParemeter(tFTItemPtr funItem,char* name,ScalarType type);
void AddReturnValue(tFTItemPtr funItem,ScalarType type);

struct tFTItem* FTInsert(tFTItemPtr* tableptr, char* token);
void FTRemove(tFTItemPtr funItem);

void FTFree(tFTItemPtr* tableptr);
#endif
