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
    FILE* hexfp;
    
    SymbolsTable t;

    initSymbolsTable(&t);

    int addr = 0;
    
    ifp = fopen("test.a","r");
    firstStep(ifp, &addr, &t);
    fclose(ifp);

    ifp = fopen("test.a","r");
    ofp = fopen("test.out","w");
    secondStep(ifp, ofp, &t);

    fclose(ifp);
    fclose(ofp);
    
    ofp   = fopen("test.out","r");
    hexfp = fopen("test.hex","w");
    bin2hex(ofp, hexfp);
    
    fclose(ofp);
    fclose(hexfp);
    
    return 0;
}
