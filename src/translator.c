#include "translator.h"

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

    if (token[0] == '_') { // it's a label. ignore.
        token = strtok(NULL, " "); // get the instruction name
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
        strncpy(out,"00001", 5);
        
        token = strtok(NULL, " "); // gets dst register
        strncpy(out+5, translateReg(token), 2);
        
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
        strncpy(out,"00010", 5);
        
        token = strtok(NULL, " "); // gets dst register
        strncpy(out+5, translateReg(token), 2);
        
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
        strncpy(out,"00011", 5);
        
        strncpy(out+5,"000000000", 9);
        
        token = strtok(NULL, " "); // gets dst register
        strncpy(out+14, translateReg(token), 2);
        
        return;
    }
        
    if (!strcmp(token, "write")) {
        strncpy(out,"00100", 5);
        
        strncpy(out,"000000000", 9);
        
        token = strtok(NULL, " "); // gets dst register
        strncpy(out+5, translateReg(token), 2);

        return;
    }

    if (!strcmp(token, "add")) {
        strncpy(out,"00101", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);
        
        return;
    }
        
    if (!strcmp(token, "subtract")) {
        strncpy(out,"00110", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);
        
        return;
    }

    if (!strcmp(token, "multiply")) {
        strncpy(out,"00111", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);

        return;
    }
                
    if (!strcmp(token, "divide")) {
        strncpy(out,"01000", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        strncpy(out,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        strncpy(out+14, translateReg(token), 2);

        return;
    }

    if (!strcmp(token, "jump")) {
        strncpy(out,"01001", 5);

        strncpy(out+5, "00", 2);
        
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
        strncpy(out,"01010", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
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
        strncpy(out,"01011", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
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
        strncpy(out,"01100", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        strncpy(out+7,"0000000", 7);
        
        token = strtok(NULL, " "); // gets second register

        strncpy(out+14, translateReg(token), 2);
        return;
    }

    if (!strcmp(token, "push")) {
        strncpy(out,"01101", 5);
        
        strncpy(out+5,"000000000", 9);
        token = strtok(NULL, " "); // gets register
        
        strncpy(out+14, translateReg(token), 2);
        
        return;
    }
        
    if (!strcmp(token, "pop")) {
        strncpy(out,"01110", 5);
       
        strncpy(out+5,"000000000", 9);
        token = strtok(NULL, " "); // gets register
        
        strncpy(out+14, translateReg(token), 2);
        
        return;
    }

    if (!strcmp(token, "call")) {
        strncpy(out,"01111", 5);
        
        strncpy(out+5, "00", 2);
        
        token = strtok(NULL, " "); // gets address label
        strncpy(out+7, getAddress(token, t), 9);

        return;
    }
        
    if (!strcmp(token, "return")) {
        strncpy(out,"10000", 5);
        
        strncpy(out,"00000000000", 11);
        
        return;
    }

    if (!strcmp(token, "load_s")) {
        strncpy(out,"10001", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        token = strtok(NULL, " "); // gets address
        constantTo9bitString(atoi(token), out+7);

        return;
    }
        
    if (!strcmp(token, "store_s")) {
        strncpy(out,"10010", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        token = strtok(NULL, " "); // gets address
        constantTo9bitString(atoi(token), out+7);

        return;
    }

    if (!strcmp(token, "loadc")) {
        strncpy(out,"10011", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        token = strtok(NULL, " "); // gets address
        constantTo9bitString(atoi(token), out+7);

        return;
    }
        
    if (!strcmp(token, "loadi")) {
        strncpy(out,"10100", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        strncpy(out+7,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        
        strncpy(out+14, translateReg(token), 2);

        return;
    }
        
    if (!strcmp(token, "storei")) {
        strncpy(out,"10101", 5);
        
        token = strtok(NULL, " "); // gets first register
        strncpy(out+5, translateReg(token), 2);
        
        strncpy(out+7,"0000000", 7);
        token = strtok(NULL, " "); // gets second register
        
        strncpy(out+14, translateReg(token), 2);

        return;
    }
        
    if (!strcmp(token, "copytop")) {
        strncpy(out,"10110", 5);
        
        strncpy(out,"000000000", 9);

        token = strtok(NULL, " "); // gets register
        strncpy(out+5, translateReg(token), 2);

        return;
    }
}
