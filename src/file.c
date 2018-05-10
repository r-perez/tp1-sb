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

void bin2hex (FILE* ifp, FILE* ofp) {
    int i = 0;
    int k = 0;
    char c;   
    
    while ((c = fgetc(ifp)) != EOF) {
        if (i == 0) {
            fprintf(ofp, "%d ", k);
            k++;
        }
        
        if (i == 4)
            fprintf(ofp, " ");

        fprintf(ofp, "%c", c);

        i = (i+1) % 8;
        
        if (i == 0)
            fprintf(ofp, "\n");
    }
}
