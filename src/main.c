#include <stdio.h>

/* #include "hash.h" */
/* #include "translator.h" */

int main (void) {
    FILE* fp = fopen("main.c", "r");
    
    firstStep(fp);
        
    return 0;
}
