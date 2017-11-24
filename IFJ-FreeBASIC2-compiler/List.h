#ifndef LIST
#define LIST
#include "Basics.h"
#include "Token.h"
typedef struct tDLElem {                 /* prvek dvousměrně vázaného seznamu */
	void* data;                                            /* užitečná data */
	struct tDLElem *lptr;          /* ukazatel na předchozí prvek seznamu */
	struct tDLElem *rptr;        /* ukazatel na následující prvek seznamu */
} *tDLElemPtr;

typedef struct {                                  /* dvousměrně vázaný seznam */
	tDLElemPtr First;                      /* ukazatel na první prvek seznamu */
	tDLElemPtr Act;                     /* ukazatel na aktuální prvek seznamu */
	tDLElemPtr Last;                    /* ukazatel na posledni prvek seznamu */
} tDLList;

void DLInitList(tDLList *);
void DLDisposeList(tDLList *);
void DLInsertFirst(tDLList *, void*);
void DLInsertLast(tDLList *, void*);
void DLFirst(tDLList *);
void DLLast(tDLList *);
void DLDeleteFirst(tDLList *);
void DLDeleteLast(tDLList *);
void DLPostDelete(tDLList *);
void DLPreDelete(tDLList *);
void DLPostInsert(tDLList *, void*);
void DLPreInsert(tDLList *, void*);
void DLActualize(tDLList *, void*);
void DLNext(tDLList *);
void DLPred(tDLList *);
bool DLActive(tDLList *);
bool DLIsEmpty(tDLList *);
bool DLIsActiveItemLast(tDLList *L);
#endif
