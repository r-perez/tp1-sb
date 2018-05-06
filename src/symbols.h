#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <string.h>

#include "utility.h"

#define MAXSYMBOLSIZE 100
#define TABLESIZE     64

typedef struct {
    int rowIsSet;
    char symbol[MAXSYMBOLSIZE]; 
    char addr[10]; // 9 bit string that tells the address.
} SymbolRow;

typedef struct {
    SymbolRow rows[TABLESIZE];
} SymbolsTable;

void  insertSymbolToTable (char* symbol, int addr, SymbolsTable* t);
void  initSymbolsTable    (SymbolsTable* t);
char* getAddress          (char* symbol, SymbolsTable* t);
long  hashSymbol          (char* symbol);

#endif
