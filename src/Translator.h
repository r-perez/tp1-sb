#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TableOfSymbols.h"
#include "Converter.h"

void  processSymbols (char* line, int* addr, SymbolsTable* t);
void  translateLine  (char* line, char* out, SymbolsTable* t);
void  translateReg   (char* reg , char* out);

#endif
