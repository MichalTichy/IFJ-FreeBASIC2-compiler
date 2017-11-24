#include "List.h"

void DLInitList(tDLList *L) {
	/*
	** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
	** z následujících funkcí nebude volána nad neinicializovaným seznamem).
	** Tato inicializace se nikdy nebude provádět nad již inicializovaným
	** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
	** že neinicializované proměnné mají nedefinovanou hodnotu.
	**/

	L->Act = NULL;
	L->First = NULL;
	L->Last = NULL;
}

void DLDisposeList(tDLList *L) {
	/*
	** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
	** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
	** uvolněny voláním operace free.
	**/
	tDLElemPtr current = L->First;
	while (current != NULL)
	{
		tDLElemPtr next = current->rptr;
		free(current);
		current = next;
	}

	//why we cant use DLInitList???
	L->Act = NULL;
	L->First = NULL;
	L->Last = NULL;
}

void DLInsertFirst(tDLList *L, void* val) {
	/*
	** Vloží nový prvek na začátek seznamu L.
	** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
	** volá funkci //TODO ERROR HANDLING.
	**/

	tDLElemPtr newElement = malloc(sizeof(struct tDLElem));

	if (newElement == NULL)
	{
		//TODO ERROR HANDLING;
		return;
	}

	newElement->data = val;
	newElement->lptr = NULL;
	newElement->rptr = L->First;

	if (L->First == NULL)
		L->Last = newElement;
	else
		L->First->lptr = newElement;

	L->First = newElement;
}

void DLInsertLast(tDLList *L, void* val) {
	/*
	** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
	** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
	** volá funkci //TODO ERROR HANDLING.
	**/

	tDLElemPtr newElement = malloc(sizeof(struct tDLElem));

	if (newElement == NULL)
	{
		//TODO ERROR HANDLING;
		return;
	}

	newElement->data = val;
	newElement->lptr = L->Last;
	newElement->rptr = NULL;

	if (L->Last == NULL) 
		L->First = newElement;
	else
		L->Last->rptr = newElement;

	L->Last = newElement;
}

void DLFirst(tDLList *L) {
	/*
	** Nastaví aktivitu na první prvek seznamu L.
	** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
	** aniž byste testovali, zda je seznam L prázdný.
	**/

	L->Act = L->First;
}

void DLLast(tDLList *L) {
	/*
	** Nastaví aktivitu na poslední prvek seznamu L.
	** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
	** aniž byste testovali, zda je seznam L prázdný.
	**/
	L->Act = L->Last;
}

void DLDeleteFirst(tDLList *L) {
	/*
	** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
	** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
	**/
	if (L->First == NULL)
		return;

	if (L->First == L->Last)
	{
		L->Act = NULL;
		L->First = NULL;
		L->Last = NULL;
		return;
	}

	if (L->Act == L->First)
	{
		L->Act = NULL;
	}

	tDLElemPtr prevFirstElement = L->First;

	L->First = prevFirstElement->rptr;
	L->First->lptr = NULL;

	free(prevFirstElement);
}

void DLDeleteLast(tDLList *L) {
	/*
	** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
	** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
	**/

	if (L->First == NULL)
		return;

	if (L->First == L->Last)
	{
		L->Act = NULL;
		L->First = NULL;
		L->Last = NULL;
		return;
	}

	if (L->Act == L->Last)
	{
		L->Act = NULL;
	}

	tDLElemPtr prevLastElement = L->Last;

	L->Last = prevLastElement->lptr;
	L->First->rptr = NULL;

	free(prevLastElement);
}

void DLPostDelete(tDLList *L) {
	/*
	** Zruší prvek seznamu L za aktivním prvkem.
	** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
	** posledním prvkem seznamu, nic se neděje.
	**/
	if (L->Act == NULL || L->Last == L->Act)
		return;

	tDLElemPtr ElementToDelete = L->Act->rptr;

	L->Act->rptr = ElementToDelete->rptr;

	if (L->Last == ElementToDelete)
		L->Last = L->Act;

	return;
}

void DLPreDelete(tDLList *L) {
	/*
	** Zruší prvek před aktivním prvkem seznamu L .
	** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
	** prvním prvkem seznamu, nic se neděje.
	**/
	if (L->Act == NULL || L->First == L->Act)
		return;

	tDLElemPtr ElementToDelete = L->Act->lptr;

	L->Act->lptr = ElementToDelete->lptr;

	if (L->First == ElementToDelete)
		L->First = L->Act;

	return;
}

void DLPostInsert(tDLList *L, void* val) {
	/*
	** Vloží prvek za aktivní prvek seznamu L.
	** Pokud nebyl seznam L aktivní, nic se neděje.
	** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
	** volá funkci //TODO ERROR HANDLING.
	**/

	if (L->Act == NULL)
		return;

	tDLElemPtr newElement = malloc(sizeof(struct tDLElem));
	if (newElement == NULL)
		//TODO ERROR HANDLING;

	newElement->data = val;
	newElement->lptr = L->Act;
	newElement->rptr = L->Act->rptr;
	L->Act->rptr = newElement;

	if (newElement->rptr != NULL)
		newElement->rptr->lptr = newElement;

	if (L->Act == L->Last)
		L->Last = newElement;

}

void DLPreInsert(tDLList *L, void* val) {
	/*
	** Vloží prvek před aktivní prvek seznamu L.
	** Pokud nebyl seznam L aktivní, nic se neděje.
	** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
	** volá funkci //TODO ERROR HANDLING.
	**/

	if (L->Act == NULL)
		return;

	tDLElemPtr newElement = malloc(sizeof(struct tDLElem));
	if (newElement == NULL)
		//TODO ERROR HANDLING;

	newElement->data = val;
	newElement->rptr = L->Act;
	newElement->lptr = L->Act->lptr;
	L->Act->rptr = newElement;

	if (newElement->lptr != NULL)
		newElement->lptr->rptr = newElement;

	if (L->Act == L->First)
		L->First = newElement;
}

void DLActualize(tDLList *L, void* val) {
	/*
	** Přepíše obsah aktivního prvku seznamu L.
	** Pokud seznam L není aktivní, nedělá nic.
	**/
	if (L->Act == NULL)
		return;

	L->Act->data = val;
}

void DLNext(tDLList *L) {
	/*
	** Posune aktivitu na následující prvek seznamu L.
	** Není-li seznam aktivní, nedělá nic.
	** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
	**/
	if (L->Act == NULL)
		return;

	L->Act = L->Act->rptr;
}


void DLPred(tDLList *L) {
	/*
	** Posune aktivitu na předchozí prvek seznamu L.
	** Není-li seznam aktivní, nedělá nic.
	** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
	**/

	if (L->Act == NULL)
		return;

	L->Act = L->Act->lptr;
}

bool DLActive(tDLList *L) {
	/*
	** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
	** Funkci je vhodné implementovat jedním příkazem return.
	**/
	return L->Act != NULL;
}

bool DLIsEmpty(tDLList *L) {
	/*
	** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
	** Funkci je vhodné implementovat jedním příkazem return.
	**/
	return L->First == NULL;
}

bool DLIsActiveItemLast(tDLList *L) {
	return L->Last == L->Act;
}