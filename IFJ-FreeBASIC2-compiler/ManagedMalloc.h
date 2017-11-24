#pragma once
#ifndef MMALLOC
#define MMALLOC
#include <stdlib.h>

void * mmalloc(size_t size);
void mfree(void *);
void mfreeall(void);
void * mrealloc(void *ptr, size_t size);

#endif // !MMALLOC
