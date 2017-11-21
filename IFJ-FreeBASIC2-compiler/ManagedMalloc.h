#pragma once
#ifndef MMALLOC
#define MMALLOC
#include <stdlib.h>

void * mmaloc(size_t size);
void mfree(void *);
void mfreeall(void);

#endif // !MMALLOC
