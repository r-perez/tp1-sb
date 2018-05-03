#include "hash.h"

long hashSymbol (char* symbol) {
    long hashVal = 0;

    while (*symbol != '\0') {
        hashVal = (hashVal << 4) + *(symbol++);
        long g = hashVal & 0xF0000000L;
        if (g != 0) hashVal ^= g >> 24;
        hashVal &= ~g;
    }
    
    return hashVal;

}
