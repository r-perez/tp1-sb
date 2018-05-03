#ifndef INSTRUCTIONS
#define INSTRUCTIONS

typedef struct {
    char* instruction;
    char* code;
} InstructionTuple;

InstructionTuple instructions[23] =
    { {"stop"  , "00000"}, {"load"  , "00001"}, {"store"   ,"00010"}, {"read"    , "00011"}
    , {"write" , "00100"}, {"add"   , "00101"}, {"subtract","00110"}, {"multiply", "00111"}
    , {"divide", "01000"}, {"jump"  , "01001"}, {"jmpz"    ,"01010"}, {"jmpn"    , "01011"}
    , {"move"  , "01100"}, {"push"  , "01101"}, {"pop"     ,"01110"}, {"call"    , "01111"}
    , {"return", "10000"}, {"load_s", "10001"}, {"store_s" ,"10010"}, {"loadc"   , "10011"}
    , {"loadi" , "10100"}, {"storei", "10101"}, {"copytop" ,"10110"}
    };

#endif
