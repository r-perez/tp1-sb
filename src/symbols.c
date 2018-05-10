#include "symbols.h"

/* debug */
#include <stdio.h>

void initSymbolsTable (SymbolsTable* t) {
    for (int i = 0; i < TABLESIZE; i++) {
        t->rows[i].rowIsSet = 0;
    }
}

void insertSymbolToTable (char* symbol, int addr, SymbolsTable* t) {
    int pos = hashSymbol(symbol) % TABLESIZE;
    char addrString[10];

    ///* debug */ printf("--%d--", addr);
    
    constantTo9bitString(addr, addrString);

    if (!t->rows[pos].rowIsSet) {
        strcpy(t->rows[pos].symbol, symbol);
        strcpy(t->rows[pos].addr  , addrString);
    }
    else {
        for (; t->rows[pos].rowIsSet; pos = ((pos+1) % TABLESIZE));
        
        strcpy(t->rows[pos].symbol, symbol);
        strcpy(t->rows[pos].addr  , addrString);
    }

    t->rows[pos].rowIsSet = 1;
}

char* getAddress (char* symbol, SymbolsTable* t) {
    int pos = hashSymbol(symbol) % TABLESIZE;

    for (; strcmp(t->rows[pos].symbol, symbol) != 0
         ; pos = ((pos+1) % TABLESIZE));

    return t->rows[pos].addr;
}

long hashSymbol (char* symbol) {
    long hashVal = 0;

    while (*symbol != '\0') {
        hashVal = (hashVal << 4) + *(symbol++);
        
        long g = hashVal & 0xF0000000L;

        if (g != 0)
            hashVal ^= g >> 24;
        
        hashVal &= ~g;
    }
    
    return hashVal;
}
