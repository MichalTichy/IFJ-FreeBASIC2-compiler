
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

void FTInsert(tFTItemPtr* tableptr, char* token, char** parameters);

void FTFree(tFTItemPtr* tableptr);
