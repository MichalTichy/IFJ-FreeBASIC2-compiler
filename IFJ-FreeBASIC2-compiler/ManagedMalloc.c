#include "ManagedMalloc.h"
#include "List.h"

int listSize = 0;

tDLList list;

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
	if (ptr != NULL && listSize != 0)
	{
		if (list.First->data == ptr)
		{
			free(ptr);
			DLDeleteFirst(&list);
			listSize--;
			return;
		}
		else
		{
			list.Act = list.Last;
			do
			{
				if (list.Act->data == ptr)
				{
					free(ptr);
					list.Act = list.Act->lptr;
					DLPostDelete(&list);
					listSize--;
					return;
				}
				list.Act = list.Act->lptr;
			} while (list.Act != list.First);
		}
	}
	
}

void mfreeall()
{
	if (listSize != 0)
	{
		list.Act = list.First;
		while (list.Act != NULL)
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
	void * tmp = realloc(ptr, size);
	if (tmp == ptr) return tmp;

	if (list.First->data == ptr)
	{
		DLDeleteFirst(&list);
		return tmp;
	}
	else
	{
		list.Act = list.Last;
		do
		{
			if (list.Act->data == ptr)
			{
				list.Act->data = tmp;
				return tmp;
			}
			list.Act = list.Act->lptr;
		} while (list.Act != list.First);


	}
}

