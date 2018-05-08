#include "translator.h"

void translateReg (char* reg, char* out) {
    if (!strcmp(reg,"A0")) {
        strcpy(out, "00");
    }
    
    if (!strcmp(reg,"A1")) {
        strcpy(out, "01");
    }
    
    if (!strcmp(reg,"A2")) {
        strcpy(out, "10");
    }
    
    if (!strcmp(reg,"A3")) {
        strcpy(out, "11");
    }
}

void  processSymbols (char* line, int* addr, SymbolsTable* t) {
    // first token: label or instruction name
    char* token = strtok(line, " ");

     if (token[0] == '_') { // it's a label
        token = strtok(token, ":"); //strip ':' character
 
        insertSymbolToTable(token, (*addr), t);

        token = strtok(line, " "); // restart tokenizing
        token = strtok(NULL, " "); // pass through the label again
        token = strtok(NULL, " "); // get the instruction name
        
        if (!strcmp(token, ".data")) {
            // get the number of allocated bytes
            token = strtok(NULL, " ");
            
            (*addr) = (*addr) + atoi(token);
            
            return;
        }    
    }

    (*addr) = 2 * (*addr); // address of the symbol
}

void translateLine (char* line, char* out, SymbolsTable* t) {
    // first token: label or instruction name
    char* token = strtok(line, " ");

    /* debug */ printf("%s \n", token);

    if (token[0] == '_') { // it's a label. ignore.
        token = strtok(NULL, " "); // get the instruction name
        
        /* debug */ printf("%s \n", token);
    }

    if (!strcmp(token, ".data")) {
        int allocatedBytes;
        int value;
        
        token = strtok(NULL, " "); // get the number of allocated bytes
        allocatedBytes = atoi(token);

        token = strtok(NULL, " "); // get the initial value
        value = atoi(token);

        constantToNbitString(value, 8*allocatedBytes, out);
        
        return;
    }
    
    if (!strcmp(token, "stop")) {
        strcpy(out, "0000000000000000");
    }
        
    if (!strcmp(token, "load")) {
        strncpy(out,"00001", 6);
        
        token = strtok(NULL, " "); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        token = strtok(NULL, " "); // gets dst label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isalpha(token[0]))
            strncpy(out+7, getAddress(token, t), 9);
        else
            constantTo9bitString(atoi(token), out+7);
                
        return;
    }
        
    if (!strcmp(token, "store")) {
        strncpy(out,"00010", 6);
        
        token = strtok(NULL, " "); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        token = strtok(NULL, " "); // gets dst label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isalpha(token[0]))
            strncpy(out+7, getAddress(token, t), 9);
        else
            constantTo9bitString(atoi(token), out+7);
                
        return;
    }

    if (!strcmp(token, "read")) {
        strncpy(out,"00011", 6);
        
        strncpy(out+5,"000000000", 10);
        
        token = strtok(NULL, " "); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        return;
    }
        
    if (!strcmp(token, "write")) {
        strncpy(out,"00100", 6);
        
        strncpy(out,"000000000", 10);
        
        token = strtok(NULL, " "); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);

        return;
    }

    if (!strcmp(token, "add")) {
        strncpy(out,"00101", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);

        /* debug */ printf("%s \n", token);
        
        strncpy(out+7,"0000000", 8);
        token = strtok(NULL, " "); // gets second register
        
        translateReg(token, reg);
        strncpy(out+5, reg, 2);

        return;
    }
        
    if (!strcmp(token, "subtract")) {
        strncpy(out,"00110", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        strncpy(out,"0000000", 8);
        token = strtok(NULL, " "); // gets second register

        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        return;
    }

    if (!strcmp(token, "multiply")) {
        strncpy(out,"00111", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        strncpy(out,"0000000", 8);
        token = strtok(NULL, " "); // gets second register

        translateReg(token, reg);
        strncpy(out+5, reg, 2);

        return;
    }
                
    if (!strcmp(token, "divide")) {
        strncpy(out,"01000", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);

        
        strncpy(out,"0000000", 8);
        token = strtok(NULL, " "); // gets second register
        
        translateReg(token, reg);
        strncpy(out+5, reg, 2);

        return;
    }

    if (!strcmp(token, "jump")) {
        strncpy(out,"01001", 6);

        strncpy(out+5, "00", 3);
        
        token = strtok(NULL, " "); // gets address label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isalpha(token[0]))
            strncpy(out+7, getAddress(token, t), 9);
        else
            constantTo9bitString(atoi(token), out+7);
        
        strncpy(out+7, getAddress(token, t), 9);
        
        return;
    }
        
    if (!strcmp(token, "jmpz")) {
        strncpy(out,"01010", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        token = strtok(NULL, " "); // gets address label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isalpha(token[0]))
            strncpy(out+7, getAddress(token, t), 9);
        else
            constantTo9bitString(atoi(token), out+7);
        
        strncpy(out+7, getAddress(token, t), 9);
        
        return;
    }

    if (!strcmp(token, "jmpn")) {
        strncpy(out,"01011", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        token = strtok(NULL, " "); // gets address label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isalpha(token[0]))
            strncpy(out+7, getAddress(token, t), 9);
        else
            constantTo9bitString(atoi(token), out+7);
        
        strncpy(out+7, getAddress(token, t), 9);
        
        return;
    }

    if (!strcmp(token, "move")) {
        strncpy(out,"01100", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        strncpy(out+7,"0000000", 8);
        
        token = strtok(NULL, " "); // gets second register

        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        return;
    }

    if (!strcmp(token, "push")) {
        strncpy(out,"01101", 6);
        
        strncpy(out+5,"000000000", 10);
        token = strtok(NULL, " "); // gets register
        
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        return;
    }
        
    if (!strcmp(token, "pop")) {
        strncpy(out,"01110", 6);
       
        strncpy(out+5,"000000000", 10);
        token = strtok(NULL, " "); // gets register
        
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        return;
    }

    if (!strcmp(token, "call")) {
        strncpy(out,"01111", 6);
        
        strncpy(out+5, "00", 3);
        
        token = strtok(NULL, " "); // gets address label
        strncpy(out+7, getAddress(token, t), 9);

        return;
    }
        
    if (!strcmp(token, "return")) {
        strncpy(out,"10000", 6);
        
        strncpy(out,"00000000000", 12);
        
        return;
    }

    if (!strcmp(token, "load_s")) {
        strncpy(out,"10001", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        token = strtok(NULL, " "); // gets address
        constantTo9bitString(atoi(token), out+7);

        return;
    }
        
    if (!strcmp(token, "store_s")) {
        strncpy(out,"10010", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        token = strtok(NULL, " "); // gets address
        constantTo9bitString(atoi(token), out+7);

        return;
    }

    if (!strcmp(token, "loadc")) {
        strncpy(out,"10011", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        token = strtok(NULL, " "); // gets address
        constantTo9bitString(atoi(token), out+7);

        return;
    }
        
    if (!strcmp(token, "loadi")) {
        strncpy(out,"10100", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        strncpy(out+7,"0000000", 8);
        token = strtok(NULL, " "); // gets second register
        
        translateReg(token, reg);
        strncpy(out+5, reg, 2);

        return;
    }
        
    if (!strcmp(token, "storei")) {
        strncpy(out,"10101", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);
        
        strncpy(out+7,"0000000", 8);
        token = strtok(NULL, " "); // gets second register
        
        translateReg(token, reg);
        strncpy(out+5, reg, 2);

        return;
    }
        
    if (!strcmp(token, "copytop")) {
        strncpy(out,"10110", 6);
        
        strncpy(out,"000000000", 10);

        token = strtok(NULL, " "); // gets register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 2);

        return;
    }
}
