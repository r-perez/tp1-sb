#ifndef FILE_H
#define FILE_H

#include <stdio.h>

#include "TableOfSymbols.h"
#include "Translator.h"

void bin2mif    (FILE* ifp, FILE* ofp);
void firstStep  (FILE* ifp, int* addr, SymbolsTable* t); 
void secondStep (FILE* ifp, FILE* ofp, SymbolsTable* t);

#endif
