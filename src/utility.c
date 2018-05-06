#include "utility.h"

#include <stdio.h>

void constantTo9bitString (int c, char* out) {
    int j = 0;

    for (int i = 8; i >= 0; i--) {
        int k = c >> i;
        if (k & 1)
            out[j] = '1';
        else
            out[j] = '0';
        j++;
    }

    out[9] = '\0';
}

void constantToNbitString (int c, int n, char* out) {
    int j = 0;

    for (int i = n-1; i >= 0; i--) {
        int k = 0;
        
        if (i < 31)
            k = c >> i;
        else
            k = c >> 31;
                
        if (k & 1)
            out[j] = '1';
        else
            out[j] = '0';
        j++;
    }

    out[n] = '\0';
}
