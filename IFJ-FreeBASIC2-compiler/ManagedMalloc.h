#pragma once
#ifndef MMALLOC
#define MMALLOC
#include <stdlib.h>
#include "errors.h"
ERR_CODE lastError;
void * mmalloc(size_t size);
void mfree(void *);
void mfreeall(void);
void * mrealloc(void *ptr, size_t size);
void exitSecurely(ERR_CODE errorCode);
#endif // !MMALLOC
