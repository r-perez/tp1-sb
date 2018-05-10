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
    char symbol[MAXSYMBOLSIZE];
    
    if (token[0] == '_') { // it's a label
        strcpy(symbol, token);       
        token = strtok(NULL, " "); // get instruction
        
        if (!strcmp(token, ".data")) {
            
            // get the number of allocated bytes
            token = strtok(NULL, " ");
            int allocatedBytes = atoi(token);
             
            token = strtok(symbol, ":"); //strip ':' character from symbol
            insertSymbolToTable(token, (*addr), t); // insert it on the table

            (*addr) = (*addr) + allocatedBytes;
            
            return;
        }

        token = strtok(symbol, ":"); //strip ':' character from symbol
        insertSymbolToTable(token, (*addr), t); // insert it on the table
    }

    (*addr) = (*addr) + 2; // address of the symbol
}

void translateLine (char* line, char* out, SymbolsTable* t) {
    // try to match a single word instructions first
    char* token = strtok(line, "\n");

    if (!strcmp(token, "stop")) {
        strncpy(out, "0000000000000000", 17);
        return;
    }
    
    if (!strcmp(token, "return")) {

        strncpy(out,"1000000000000000", 17);
        
        return;
    }

    // try to match other instructions
    token = strtok(line, " ");

    if (token[0] == '_') { // it's a label. ignore.
        token = strtok(NULL, " "); // get the instruction name
    }

    if (!strcmp(token, ".data")) {
        int allocatedBytes;
        int value;
        
        token = strtok(NULL, " "); // get the number of allocated bytes
        allocatedBytes = atoi(token);

        token = strtok(NULL, " \n"); // get the initial value
        value = atoi(token);

        constantToNbitString(value, 8*allocatedBytes, out);
        
        return;
    }
        
    if (!strcmp(token, "load")) {
        strncpy(out,"00001", 6);
        
        token = strtok(NULL, " "); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, " \n"); // gets dst label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isdigit(token[0]))
            strncpy(out+7, getAddress(token, t), 10);
        else
            constantTo9bitString(atoi(token), out+7);
                
        return;
    }
        
    if (!strcmp(token, "store")) {
        strncpy(out,"00010", 6);
        
        token = strtok(NULL, " "); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, " \n"); // gets dst label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isdigit(token[0]))
            strncpy(out+7, getAddress(token, t), 10);
        else
            constantTo9bitString(atoi(token), out+7);
                
        return;
    }

    if (!strcmp(token, "read")) {
        strncpy(out,"00011", 6);
        
        strncpy(out+5,"000000000", 10);
        
        token = strtok(NULL, " \n"); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);
        
        return;
    }
        
    if (!strcmp(token, "write")) {
        strncpy(out,"00100", 6);
        
        strncpy(out+5,"000000000", 10);
        
        token = strtok(NULL, " \n"); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);

        return;
    }

    if (!strcmp(token, "add")) {
        strncpy(out,"00101", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, " \n"); // gets second register
        translateReg(token, reg);

        strncpy(out+14, reg, 3);

        return;
    }
        
    if (!strcmp(token, "subtract")) {
        strncpy(out,"00110", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, " \n"); // gets second register
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
        
        return;
    }

    if (!strcmp(token, "multiply")) {
        strncpy(out,"00111", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, " \n"); // gets second register
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
        
        return;
    }
                
    if (!strcmp(token, "divide")) {
        strncpy(out,"01000", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, " \n"); // gets second register
        translateReg(token, reg);

        strncpy(out+14, reg, 3);
        
        return;
    }

    if (!strcmp(token, "jump")) {
        strncpy(out,"01001", 6);

        strncpy(out+5, "00", 3);
        
        token = strtok(NULL, " \n"); // gets address label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isdigit(token[0]))
            strncpy(out+7, getAddress(token, t), 9);
        else
            constantTo9bitString(atoi(token), out+7);
        
        return;
    }
        
    if (!strcmp(token, "jmpz")) {
        strncpy(out,"01010", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, " \n"); // gets address label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isdigit(token[0]))
            strncpy(out+7, getAddress(token, t), 9);
        else
            constantTo9bitString(atoi(token), out+7);
        
        return;
    }

    if (!strcmp(token, "jmpn")) {
        strncpy(out,"01011", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, " \n"); // gets address label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isdigit(token[0]))
            strncpy(out+7, getAddress(token, t), 9);
        else
            constantTo9bitString(atoi(token), out+7);
        
        return;
    }

    if (!strcmp(token, "move")) {
        strncpy(out,"01100", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, " \n"); // gets second register
        translateReg(token, reg);

        strncpy(out+14, reg, 3);

        return;
    }

    if (!strcmp(token, "push")) {
        strncpy(out,"01101", 6);
        
        strncpy(out+5,"000000000", 10);
        
        token = strtok(NULL, " \n"); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);

        return;
    }
        
    if (!strcmp(token, "pop")) {
        strncpy(out,"01110", 6);
       
        strncpy(out+5,"000000000", 10);
        
        token = strtok(NULL, " \n"); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);

        return;
    }

    if (!strcmp(token, "call")) {
        strncpy(out,"01111", 6);
        
        strncpy(out+5, "00", 3);
        
        token = strtok(NULL, " \n"); // gets address label
        strncpy(out+7, getAddress(token, t), 10);

        return;
    }

    if (!strcmp(token, "load_s")) {
        strncpy(out,"10001", 6);
        
        token = strtok(NULL, " "); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, " \n"); // gets dst label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isdigit(token[0]))
            strncpy(out+7, getAddress(token, t), 10);
        else
            constantTo9bitString(atoi(token), out+7);
                
        return;
    }
        
    if (!strcmp(token, "store_s")) {
        strncpy(out,"10010", 6);
        
        token = strtok(NULL, " "); // gets dst register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, " \n"); // gets dst label

        // if first character is a letter, I'm assuming it's a
        // label name, otherwhise I assume it's a constant
        if (!isdigit(token[0]))
            strncpy(out+7, getAddress(token, t), 10);
        else
            constantTo9bitString(atoi(token), out+7);
                
        return;
    }

    if (!strcmp(token, "load_c")) {
        strncpy(out,"10011", 6);
        
        token = strtok(NULL, " "); // gets first register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);
        
        token = strtok(NULL, " \n"); // gets constant
        constantTo9bitString(atoi(token), out+7);

        return;
    }
        
    if (!strcmp(token, "load_i")) {
        strncpy(out,"10100", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, " \n"); // gets second register
        translateReg(token, reg);

        strncpy(out+14, reg, 3);

        return;
    }
        
    if (!strcmp(token, "store_i")) {
        strncpy(out,"10101", 6);
        
        token = strtok(NULL, " "); // gets first register

        char reg[3];
        translateReg(token, reg);
        strncpy(out+5, reg, 3);

        strncpy(out+7,"0000000", 8);

        token = strtok(NULL, " \n"); // gets second register
        translateReg(token, reg);

        strncpy(out+14, reg, 3);

        return;
    }
        
    if (!strcmp(token, "copytop")) {
        strncpy(out,"10110", 6);
        
        strncpy(out+5,"000000000", 10);

        token = strtok(NULL, " "); // gets register
        char reg[3];
        translateReg(token, reg);
        strncpy(out+14, reg, 3);

        return;
    }
}
