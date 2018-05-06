#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//DEBUG
#include <stdio.h>

#include "symbols.h"
#include "utility.h"

void  translateLine  (char* line, char* out, SymbolsTable* t);
void  processSymbols (char* line, int* addr, SymbolsTable* t);
char* translateReg   (char* reg);


#endif
