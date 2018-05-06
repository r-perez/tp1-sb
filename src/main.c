#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file.h"
#include "translator.h"
#include "symbols.h"
#include "utility.h"

int main (void) {
    FILE* ifp;
    FILE* ofp;
    
    SymbolsTable t;

    initSymbolsTable(&t);

    int addr = 0;
    
    ifp = fopen("contador.a","r");
    firstStep(ifp, &addr, &t);
    fclose(ifp);

    ifp = fopen("contador.a","r");
    ofp = fopen("contador.out","w");
    secondStep(ifp, ofp, &t);
    
    fclose(ifp);
    fclose(ofp);
    
    return 0;
}
