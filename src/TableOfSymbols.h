#ifndef TABLEOFSYMBOLS_H
#define TABLEOFSYMBOLS_H

#include <string.h>

#include "Converter.h"

#define MAXSYMBOLSIZE 200 // Maximum characters in a symbol.
#define TABLESIZE     127

typedef struct {
    int rowIsSet;
    
    char symbol[MAXSYMBOLSIZE]; 
    char addr[10]; // 9 bit string that tells the address.
} SymbolRow;

typedef struct {
    SymbolRow rows[TABLESIZE];
} SymbolsTable;

char* getAddress          (char* symbol, SymbolsTable* t);
long  hashSymbol          (char* symbol);
void  initSymbolsTable    (SymbolsTable* t);
void  insertSymbolToTable (char* symbol, int addr, SymbolsTable* t);

#endif
