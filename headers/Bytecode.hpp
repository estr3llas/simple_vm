#ifndef VM_BYTECODE_H
#define VM_BYTECODE_H

#include "./common.hpp"
#include "vm.hpp"

enum Bytecode {
    IADD = 1,
    ISUB = 2,
    IMUL = 3,
    ILT = 4,
    IEQ = 5,
    BR = 6,
    BRT = 7,
    BRF = 8,
    ICONST = 9,
    LOAD = 10,
    GLOAD = 11,
    STORE = 12,
    GSTORE = 13,
    PRINT = 14,
    POP = 15,
    HALT = 16
};

class Instruction {
private:
    const char* mnemonic;
    int operand;
public:

    Instruction() : 
        mnemonic(nullptr), 
        operand(VM_ZERO) 
        {};

    Instruction(const char* mnemonic_value) : 
        mnemonic(mnemonic_value), 
        operand(VM_ZERO) 
        {};

    Instruction(const char *mnemonic_value, int operand_arg) : 
        mnemonic(mnemonic_value), 
        operand(operand_arg) 
        {};
    
    const char* getMnemonic(){
        return mnemonic;
    }

    int getOperand(){
        return operand;
    }

};


namespace {
    Instruction opcodes[] = {
        Instruction(""),
        Instruction("IADD"),
        Instruction("ISUB"),
        Instruction("IMUL"),
        Instruction("ILT"),
        Instruction("IEQ"),
        Instruction("BR", 1),
        Instruction("BRT", 1),
        Instruction("BRF", 1),
        Instruction("ICONST", 1),
        Instruction("LOAD", 1),
        Instruction("GLOAD", 1),
        Instruction("STORE", 1),
        Instruction("GSTORE", 1),
        Instruction("PRINT"),
        Instruction("POP"),
        Instruction("HALT")
    };
}

#endif