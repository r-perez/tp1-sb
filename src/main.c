#include <stdio.h>

#include "hash.h"
#include "instructions.h"

int main (void) {

    for (int i = 0; i < 23; i++)
        printf("%s %s\n", instructions[i].instruction, instructions[i].code);
   
    return 0;
}
