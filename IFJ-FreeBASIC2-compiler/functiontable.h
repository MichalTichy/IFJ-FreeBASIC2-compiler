/**
*	Project: IFJ17 Compiler
*
*	FILE: functiontable.h
*
*	File author:
*	  Ondrej Deingruber, xdeing00
*
*	Project authors:
*	  Michal Tichy, xtichy26
*	  Michal Martinu, xmarti78
*	  Gabriel Mastny, xmastn02
*	  Ondrej Deingruber, xdeing00
*
**/

#pragma once
#ifndef FUNCTIONTABLE
#define FUNCTIONTABLE

#include "Scanner.h"
#include "Scanner.h"
#include "ADT.h"
#include <stdbool.h>

void CompareParameterSignature(tFTItemPtr item, unsigned int position, char* name, ScalarType type);

#endif
