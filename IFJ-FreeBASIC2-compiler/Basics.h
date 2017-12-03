#include <stdbool.h>
#include "errors.h"

#ifndef SCALARTYPEDEF
#define SCALARTYPEDEF

typedef enum {
	TYPE_Integer,
	TYPE_Double,
	TYPE_String,
	TYPE_Void
} ScalarType;

#endif

#undef NULL
#define NULL 0