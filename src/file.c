#include "file.h"
#include "symbols.h"

#define BUFFERSIZE 256

void firstStep (FILE* fp) {
    char buffer[BUFFERSIZE];

    while (fgets(buffer, BUFFERSIZE, fp) != NULL) {
        /* do your stuff*/
    }
}

void secondStep (FILE* fp) {
    char buffer[BUFFERSIZE];

    while (fgets(buffer, BUFFERSIZE, fp) != NULL) {
        /* do your stuff*/
    }
}
