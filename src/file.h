#ifndef FILE_H
#define FILE_H

#include <stdio.h>

#include "translator.h"
#include "symbols.h"

void firstStep  (FILE* ifp, int* addr, SymbolsTable* t); 
void secondStep (FILE* ifp, FILE* ofp, SymbolsTable* t);

#endif
