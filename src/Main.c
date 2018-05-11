#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Converter.h"
#include "File.h"
#include "TableOfSymbols.h"
#include "Translator.h"

int main (int argc, char* argv[]) {
    FILE* ifp;
    FILE* ofp;
    FILE* hexfp;

    int keepBinary = 0;
    
    char mifFilename[200];
    char binaryFilename[200];

    /* Declares a table of symbols.*/
    SymbolsTable t;

    /* Initializes it. */
    initSymbolsTable (&t);

    /* Memory address starting from zero. */
    int addr = 0;

    /* Runs the assembler's first step on the input file
       to build the talbe of symbols.
    */
    ifp = fopen (argv[1],"r");
    if (!ifp) {
        printf("[ERROR] The input file, namely \"%s\", could not be opened.", argv[1]);
        exit(1);
    }

    if (argc == 3 && (!strcmp("--keepBinary", argv[2]))) {
        keepBinary = 1;
    }
    
    firstStep (ifp, &addr, &t);
    fclose (ifp);

    /* Runs the assembler's second step on the input file.
       It generates an "out.binary" file with pure translated 
       binary code.
    */
    ifp = fopen (argv[1],"r");

    /* Builds the output files' filenames. */
    char* token = strtok(argv[1], " .");

    strcpy(binaryFilename, token);
    strcat(binaryFilename, ".binary");

    strcpy(mifFilename, token);
    strcat(mifFilename, ".mif");
    
    ofp = fopen (binaryFilename,"w");
    secondStep(ifp, ofp, &t);

    fclose(ifp);
    fclose(ofp);

    /* Translates the binary file into a proper mif file.
       It generates an "out.binary" file with pure translated 
       binary code.
    */
    ofp   = fopen (binaryFilename,"r");
    hexfp = fopen (mifFilename,"w");
    bin2mif (ofp, hexfp);
    
    fclose (ofp);
    fclose (hexfp);

    if (keepBinary) {
        return 0;        
    }

    remove(binaryFilename);
    
    return 0;
}
