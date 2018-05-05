#include "translator.h"
#include "symbols.h"
#include "utility.h"

char* translateReg (char* reg) {
    if (!strcmp(reg,"A0")) {
        return "00";
    }
    
    if (!strcmp(reg,"A1")) {
        return "01";
    }
    
    if (!strcmp(reg,"A2")) {
        return "10";
    }
    
    if (!strcmp(reg,"A3")) {
        return "11";
    }
    
    return NULL;
}

void translateLine (char* line, char* out) {
    char* token = strtok(line, " "); // first token: instruction name
    
    if (!strcmp(line, "stop")) {
        strcpy(out, "00000000000000000000");
    }
        
    if (!strcmp(line, "load")) {
        strncpy(out,"00001", 5);
        token = strtok(NULL, " "); // gets dst register
        strncpy(out+5, translateReg(token), 2);
        token = strtok(NULL, " "); // gets dst label
        strncpy(out+7, getAddress(token), 9);
        return;
    }
        
    if (!strcmp(line, "store")) {
        strncpy(out,"00010", 5);
        token = strtok(NULL, " "); // gets dst register
        strncpy(out+5, translateReg(token), 2);
        token = strtok(NULL, " "); // gets dst label
        strncpy(out+7, getAddress(token), 9);
        return;
    }

    if (!strcmp(line, "read")) {
        strncpy(out,"00011", 5);
        strncpy(out+5,"000000000", 9);
        token = strtok(NULL, " "); // gets dst register
        strncpy(out+14, translateReg(token), 2);
        return;
    }
        
    if (!strcmp(line, "write")) {
        strncpy(out,"00100", 5);
        strncpy(out,"000000000", 9);
        token = strtok(NULL, " "); // gets dst register
        strncpy(out+5, translateReg(token), 2);
        return;
    }

    if (!strcmp(line, "add")) {
        strncpy(out,"00101", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);
        return;
    }
        
    if (!strcmp(line, "subtract")) {
        strncpy(out,"00110", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);
        return;
    }

    if (!strcmp(line, "multiply")) {
        strncpy(out,"00111", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);
        return;
    }
                
    if (!strcmp(line, "divide")) {
        strncpy(out,"01000", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);
        return;
    }

    if (!strcmp(line, "jump")) {
        strncpy(out,"01001", 5);
        strncpy(out+5, "00", 2);
        token = strtok(NULL, " "); // gets address label
        strncpy(out+7, getAddress(token), 9);
        return;
    }
        
    if (!strcmp(line, "jmpz")) {
        strncpy(out,"01010", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        token = strtok(NULL, " "); // gets address label
        strncpy(out+7, getAddress(token), 9);
        return;
    }

    if (!strcmp(line, "jmpn")) {
        strncpy(out,"01011", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        token = strtok(NULL, " "); // gets address label
        strncpy(out+7, getAddress(token), 9);
        return;
    }

    if (!strcmp(line, "move")) {
        strncpy(out,"01100", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);
        return;
    }

    if (!strcmp(line, "push")) {
        strncpy(out,"01101", 5);
        strncpy(out,"000000000", 9);
        token = strtok(NULL, " "); // gets register
        strncpy(out+5, translateReg(token), 2);
        return;
    }
        
    if (!strcmp(line, "pop")) {
        strncpy(out,"01110", 5);
        strncpy(out,"000000000", 9);
        token = strtok(NULL, " "); // gets register
        strncpy(out+5, translateReg(token), 2);
        return;
    }

    if (!strcmp(line, "call")) {
        strncpy(out,"01111", 5);
        strncpy(out+5, "00", 2);
        token = strtok(NULL, " "); // gets address label
        strncpy(out+7, getAddress(token), 9);
        return;
    }
        
    if (!strcmp(line, "return")) {
        strncpy(out,"10000", 5);
        strncpy(out,"00000000000", 11);
        return;
    }

    if (!strcmp(line, "load_s")) {
        strncpy(out,"10001", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        token = strtok(NULL, " "); // gets address label
        strncpy(out+7, getAddress(token), 9);
        return;
    }
        
    if (!strcmp(line, "store_s")) {
        strncpy(out,"10010", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        token = strtok(NULL, " "); // gets address label
        strncpy(out+7, getAddress(token), 9);
        return;
    }

    if (!strcmp(line, "loadc")) {
        strncpy(out,"10011", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        token = strtok(NULL, " "); // gets constant
        constantTo9bitString(atoi(token), out+7);
        return;
    }
        
    if (!strcmp(line, "loadi")) {
        strncpy(out,"10100", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);
        return;
    }
        
    if (!strcmp(line, "storei")) {
        strncpy(out,"10101", 5);
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);
        return;
    }
        
    if (!strcmp(line, "copytop")) {
        strncpy(out,"10110", 5);
        strncpy(out,"000000000", 9);
        token = strtok(NULL, " "); // gets register
        strncpy(out+5, translateReg(token), 2);
        return;
    }
}
