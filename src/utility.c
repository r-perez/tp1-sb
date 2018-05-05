#include "utility.h"

void constantTo9bitString (int n, char* out) {
        int j = 0;
    for (int i = 9; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            out[j] = '1';
        else
            out[j] = '0';
        j++;
    }
}
