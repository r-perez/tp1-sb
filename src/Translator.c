#include "Translator.h"

void translateReg (char* reg, char* out) {
    if (!strcmp(reg,"A0")) {
        strcpy(out, "00");
    }
    
    else if (!strcmp(reg,"A1")) {
        strcpy(out, "01");
    }
    
    else if (!strcmp(reg,"A2")) {
        strcpy(out, "10");
    }
    
    else if (!strcmp(reg,"A3")) {
        strcpy(out, "11");
    }

    else {
        printf("[ERROR] The provided register name, namely \"%s\", is not part of this machine.\n", reg);
        exit(1);
    }
}

void  processSymbols (char* line, int* addr, SymbolsTable* t) {
    // First token: label or instruction name.
    char* token = strtok(line, " ");
    char  symbol[MAXSYMBOLSIZE];
    
    if (token[0] == '_') { // It's a label.
        strcpy(symbol, token);       
        token = strtok(NULL, " "); // Gets the instruction.
        
        if (!strcmp(token, ".data")) {
            
            /* Gets the number of allocated bytes. */
            token = strtok(NULL, " ");
            int allocatedBytes = atoi(token);
             
            token = strtok(symbol, ":");            // Strips ':' character from symbol
            insertSymbolToTable(token, (*addr), t); // and inserts it on the table.

            (*addr) = (*addr) + allocatedBytes; // Computes the address of the next symbol.
            
            return;
        }

        token = strtok(symbol, ":");            // Strips ':' character from symbol
        insertSymbolToTable(token, (*addr), t); // and inserts it on the table.    
    }

    (*addr) = (*addr) + 2; // Computes the address of the next symbol.
}

void translateLine (char* line, char* out, SymbolsTable* t) {
    char* token = strtok(line, " \n");

    if (token[0] == '_') { // It's a label. Ignore it.
        token = strtok(NULL, " "); // Gets the instruction name.
    }

    /* Tries to match a single-word instruction first. */
    if (!strcmp(token, "stop")) {
        strncpy(out, "0000000000000000", 17);
    }
    
    else if (!strcmp(token, "return")) {

        strncpy(out,"1000000000000000", 17);
    }

    /* From now on, deals with non single-word instructions. */
    else if (!strcmp(token, ".data")) {
        int allocatedBytes;
        int value;
        
        token = strtok(NULL, " "); // Gets the number of allocated bytes.
        allocatedBytes = atoi(token);

        token = strtok(NULL, "; \n"); // Gets the initial value.
        value = atoi(token);

        constantToNbitString(value, 8*allocatedBytes, out);
    }
        
    else if (!strcmp(token, "load")) {
        strncpy(out,"00001", 6);
        
        token = strtok(NULL, " "); // Gets dst register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, "; \n"); // Gets dst label.

        /* If the first character is a letter, I'm assuming it's a
           label name, otherwhise I assume it's a constant.
        */
        if (!isdigit(token[0])) {
            strncpy(out+7, getAddress(token, t), 10);
        }
        else {
            constantTo9bitString(atoi(token), out+7);
        }
    }
        
    else if (!strcmp(token, "store")) {
        strncpy(out,"00010", 6);
        
        token = strtok(NULL, " "); // Gets dst register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, "; \n"); // Gets dst label.

        /* If the first character is a letter, I'm assuming it's a
           label name, otherwhise I assume it's a constant.
        */
        if (!isdigit(token[0])) {
            strncpy(out+7, getAddress(token, t), 10);
        }
        else {
            constantTo9bitString(atoi(token), out+7);
        }
    }

    else if (!strcmp(token, "read")) {
        strncpy(out,"00011", 6);
        
        strncpy(out+5,"000000000", 10);
        
        token = strtok(NULL, "; \n"); // Gets dst register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);
    }
        
    else if (!strcmp(token, "write")) {
        strncpy(out,"00100", 6);
        
        strncpy(out+5,"000000000", 10);
        
        token = strtok(NULL, "; \n"); // Gets dst register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);
    }

    else if (!strcmp(token, "add")) {
        strncpy(out,"00101", 6);
        
        token = strtok(NULL, " "); // Gets first register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, "; \n"); // Gets second register.
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
    }
        
    else if (!strcmp(token, "subtract")) {
        strncpy(out,"00110", 6);
        
        token = strtok(NULL, " "); // Gets first register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, "; \n"); // Gets second register.
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
    }

    else if (!strcmp(token, "multiply")) {
        strncpy(out,"00111", 6);
        
        token = strtok(NULL, " "); // Gets first register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, "; \n"); // Gets second register.
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
    }
                
    else if (!strcmp(token, "divide")) {
        strncpy(out,"01000", 6);
        
        token = strtok(NULL, " "); // Gets first register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, "; \n"); // Gets second register.
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
    }

    else if (!strcmp(token, "jump")) {
        strncpy(out,"01001", 6);

        strncpy(out+5, "00", 3);
        
        token = strtok(NULL, "; \n"); // Gets address label.

        /* If the first character is a letter, I'm assuming it's a
           label name, otherwhise I assume it's a constant.
        */
        if (!isdigit(token[0])) {
            strncpy(out+7, getAddress(token, t), 9);
        }
        else {
            constantTo9bitString(atoi(token), out+7);
        }
    }
        
    else if (!strcmp(token, "jmpz")) {
        strncpy(out,"01010", 6);
        
        token = strtok(NULL, " "); // Gets first register.
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, "; \n"); // Gets address label.

        /* If the first character is a letter, I'm assuming it's a
           label name, otherwhise I assume it's a constant.
        */
        if (!isdigit(token[0])) {
            strncpy(out+7, getAddress(token, t), 9);
        }
        else {
            constantTo9bitString(atoi(token), out+7);
        }
    }

    else if (!strcmp(token, "jmpn")) {
        strncpy(out,"01011", 6);
        
        token = strtok(NULL, " "); // Gets first register.
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, "; \n"); // Gets address label.

        /* If the first character is a letter, I'm assuming it's a
           label name, otherwhise I assume it's a constant.
        */
        if (!isdigit(token[0])) {
            strncpy(out+7, getAddress(token, t), 9);
        }
        else {
            constantTo9bitString(atoi(token), out+7);
        }
    }

    else if (!strcmp(token, "move")) {
        strncpy(out,"01100", 6);
        
        token = strtok(NULL, " "); // Gets first register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, "; \n"); // Gets second register.
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
    }

    else if (!strcmp(token, "push")) {
        strncpy(out,"01101", 6);
        
        strncpy(out+5,"000000000", 10);
        
        token = strtok(NULL, "; \n"); // Gets dst register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);
    }
        
    else if (!strcmp(token, "pop")) {
        strncpy(out,"01110", 6);
       
        strncpy(out+5,"000000000", 10);
        
        token = strtok(NULL, "; \n"); // Gets dst register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);
    }

    else if (!strcmp(token, "call")) {
        strncpy(out,"01111", 6);
        
        strncpy(out+5, "00", 3);
        
        token = strtok(NULL, "; \n"); // Gets address label.
        strncpy(out+7, getAddress(token, t), 10);
    }

    else if (!strcmp(token, "load_s")) {
        strncpy(out,"10001", 6);
        
        token = strtok(NULL, " "); // Gets dst register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, "; \n"); // Gets dst label.

        /* If the first character is a letter, I'm assuming it's a
           label name, otherwhise I assume it's a constant.
        */
        if (!isdigit(token[0])) {
            strncpy(out+7, getAddress(token, t), 10);
        }
        else {
            constantTo9bitString(atoi(token), out+7);
        }
    }
        
    else if (!strcmp(token, "store_s")) {
        strncpy(out,"10010", 6);
        
        token = strtok(NULL, " "); // Gets dst register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, "; \n"); // Gets dst label.

        /* If the first character is a letter, I'm assuming it's a
           label name, otherwhise I assume it's a constant.
        */
        if (!isdigit(token[0])) {
            strncpy(out+7, getAddress(token, t), 10);
        }
        else {
            constantTo9bitString(atoi(token), out+7);
        }
    }

    else if (!strcmp(token, "load_c")) {
        strncpy(out,"10011", 6);
        
        token = strtok(NULL, " "); // Gets first register.
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, "; \n"); // Gets constant.
        constantTo9bitString(atoi(token), out+7);
    }
        
    else if (!strcmp(token, "load_i")) {
        strncpy(out,"10100", 6);
        
        token = strtok(NULL, " "); // Gets first register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, "; \n"); // Gets second register.
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
    }
        
    else if (!strcmp(token, "store_i")) {
        strncpy(out,"10101", 6);
        
        token = strtok(NULL, " "); // Gets first register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, "; \n"); // Gets second register.
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
    }
        
    else if (!strcmp(token, "copytop")) {
        strncpy(out,"10110", 6);
        
        strncpy(out+5,"000000000", 10);

        token = strtok(NULL, "; \n"); // Gets register.

        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);
    }
}
