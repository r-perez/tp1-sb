#include "file.h"

#define I_BUFFERSIZE 256
#define O_BUFFERSIZE 1000
// this is a relatively  big number because of the case
// when a lot of memory will need to be allocated

void firstStep (FILE* ifp, int* addr, SymbolsTable* t) {
    char inBuffer[I_BUFFERSIZE];
    
    while (fgets(inBuffer, I_BUFFERSIZE, ifp) != NULL) {
        /* build the symbols table and everything*/
        processSymbols (inBuffer, addr, t);
    }
}

void secondStep (FILE* ifp, FILE* ofp, SymbolsTable* t) {
    char inBuffer[I_BUFFERSIZE];
    char outBuffer[O_BUFFERSIZE];

    while (fgets(inBuffer, I_BUFFERSIZE, ifp) != NULL) {
        /* translate to output */
        translateLine(inBuffer, outBuffer, t);
        
        fprintf(ofp, "%s", outBuffer);
    }
}
