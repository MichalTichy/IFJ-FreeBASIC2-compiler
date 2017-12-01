#include "ManagedMalloc.h"
#include "List.h"

int listSize = 0;

tDLList list;
ERR_CODE lastError;

void * mmalloc(size_t size)
{
	if (listSize == 0)
	{
		DLInitList(&list);
	}

	void * toReturn = malloc(size);
	if (toReturn != NULL)
	{
		DLInsertFirst(&list, toReturn);
		listSize++;
	}
	return toReturn;

}

void mfree(void * ptr)
{
	if (ptr != NULL && listSize != 0)		// if there is something to free
	{
		if (list.First->data == ptr)		// if pointer is first in list
		{
			free(ptr);
			DLDeleteFirst(&list);
			listSize--;
			return;
		}
		else								// if pointer is not first
		{
			list.Act = list.Last;			// go from end
			do
			{
				if (list.Act->data == ptr)	// if it's pointer you are looking for
				{
					free(ptr);
					list.Act = list.Act->lptr;
					DLPostDelete(&list);
					listSize--;
					return;
				}
				list.Act = list.Act->lptr;
			} while (list.Act != list.First); // till end of list
		}
	}
	
}

void mfreeall()
{
	if (listSize != 0)					// if list is not empty
	{
		list.Act = list.First;			// set act to first
		while (list.Act != NULL)		// go throw list
		{
			free(list.Act->data);
			list.Act = list.Act->rptr;
			DLDeleteFirst(&list);
			listSize--;
		}
	}
}

void * mrealloc(void * ptr, size_t size)
{
	void * tmp = realloc(ptr, size);		// realloc item
	if (tmp == ptr) return tmp;				// you get the same poiter

	if (list.First->data == ptr)			// is first
	{
		list.First->data = tmp;				// update ptr
		return tmp;
	}
	else
	{
		list.Act = list.Last;				// set act to last
		do
		{
			if (list.Act->data == ptr)		// if it's pointer you are looking for
			{
				list.Act->data = tmp;		// update
				return tmp;
			}
			list.Act = list.Act->lptr;		// go to next item
		} while (list.Act != list.First);	// till went throw all 

		return NULL;						// pointer not in list, ERROR
	}
}

void exitSecurely(ERR_CODE errorCode) {

#if !DEBUG
	mfreeall();
	exit(errorCode);
#endif
#if DEBUG
	lastError = errorCode;
#endif
}

