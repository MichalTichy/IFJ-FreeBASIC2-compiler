
#include "Scanner.h"

typedef struct tFTItem
{
	char** parameters;
	char* data;
	unsigned int len;
	struct tFTItem* lptr;
	struct tFTItem* rptr;
} *tFTItemPtr;

void FTInit(tFTItemPtr* tableptr);

tFTItemPtr FTSearch(tFTItemPtr* tableptr, char* token);

void AddParemeter(tFTItemPtr* funItem,char* name,ScalarType type);
void AddReturnValue(tFTItemPtr* funItem,ScalarType type);

tFTItemPtr* FTInsert(tFTItemPtr* tableptr, char* token);
tFTItemPtr* FTRemove(tFTItemPtr* funItem);

void FTFree(tFTItemPtr* tableptr);
