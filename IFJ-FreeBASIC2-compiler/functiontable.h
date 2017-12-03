#include "ADT.h"
#include "Basics.h"

typedef struct tFTItem
{

	char* data;
	unsigned int len;
	ScalarType returnValue;
	char** parameters;
	unsigned int parametersMax;
	unsigned int parametersCount;

	struct tFTItem* lptr;
	struct tFTItem* rptr;
} *tFTItemPtr;

void FTInit(tFTItemPtr* tableptr);

tFTItemPtr FTSearch(tFTItemPtr* tableptr, char* token);

void FTInsert(tFTItemPtr* tableptr, char* token);

void AddParemeter(tFTItemPtr* funItem, char* name, ScalarType type);

void AddReturnValue(tFTItemPtr* funItem, ScalarType type);

void FTRemove(tFTItemPtr* funItem, char* token);

void FTFree(tFTItemPtr* tableptr);
