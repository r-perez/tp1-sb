#include "File.h"

#define I_BUFFERSIZE 256
#define O_BUFFERSIZE 1016
/* this is a relatively  big number because of the case
   when a lot of memory will need to be allocated. I'm
   making it 127 * 8 = 1016, i.e, the maximum case.
*/

void firstStep (FILE* ifp, int* addr, SymbolsTable* t) {
    /* It  builds the table of symbols n stuff. */
    char inBuffer[I_BUFFERSIZE];
    
    while (fgets(inBuffer, I_BUFFERSIZE, ifp) != NULL) {
        processSymbols (inBuffer, addr, t);
    }
}

void secondStep (FILE* ifp, FILE* ofp, SymbolsTable* t) {
    /* It translates the instructions to binary. */
    char inBuffer[I_BUFFERSIZE];
    char outBuffer[O_BUFFERSIZE];

    while (fgets(inBuffer, I_BUFFERSIZE, ifp) != NULL) {
        translateLine(inBuffer, outBuffer, t);
        fprintf(ofp, "%s", outBuffer);
    }
}

void bin2mif (FILE* ifp, FILE* ofp) {
    int i = 0; // character counter
    int k = 0; // line counter

    char c;

    /* Prints the .mif header. */
    fprintf(ofp, "DEPTH = 128;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n\n");

    /* Organizes the binary code to match the .mif correct format. */
    while ((c = fgetc(ifp)) != EOF) {
        if (i == 0) {
            fprintf(ofp, "%.2X : ", k);
            k++;
        }

        fprintf(ofp, "%c", c);

        i = (i+1) % 8;
        
        if (i == 0) {
            fprintf(ofp, ";\n");
        }
    }
   
    /* Summarizes the remaining lines*/
    if (k < 127) {
        fprintf(ofp,"[%.2X..7F]: 00000000;\n", k);
    }
    else if (k > 127) {
        printf("[WARNING] Your code exceeds the maximum memory limit.\n");
    }
    
    fprintf(ofp,"END;");
}
