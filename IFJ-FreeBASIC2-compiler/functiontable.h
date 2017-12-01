
typedef struct tFTItem
{
	char** parameters;
	char* data;
	unsigned int len;
	struct tSTItem* lptr;
	struct tSTItem* rptr;
} *tFTItemPtr;

void FTInit(tFTItemPtr* tableptr);

tFTItemPtr FTSearch(tFTItemPtr* tableptr, char* key);

void FTInsert(tFTItemPtr* tableptr, char* key, char** parameters);

void FTFree(tFTItemPtr* tableptr);
