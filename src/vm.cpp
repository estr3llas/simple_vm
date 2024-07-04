#include "../headers/common.hpp"
#include "../headers/vm.hpp"
#include "../headers/Bytecode.hpp"

#define STACK_SIZE 256

VM::VM() :
    ip(0),
    sp(sp),
    fp(0)
    {};

VM::VM(const std::vector<int>& bytecode, size_t datasize) :
    code(bytecode),
    ip(0),
    data(datasize),
    stack(STACK_SIZE) 
    {};
    
void VM::SetTrace(VM &vm, bool value) {
    vm.trace = value;
}

void VM::disassemble(int32_t opcode) {
    Instruction instr = opcodes[opcode];
    printf("%04d: %s", ip, instr.getMnemonic());

    if(instr.getOperand() == 1){
        printf(" %d", code[ip+1]);
    } else if(instr.getOperand() == 2) {
        printf(" %d, %d", code[ip+1], code[ip+2]);
    }
    
    printf("\n");
}

void VM::cpu(VM &vm) {
    
    int32_t operand;
    int32_t opcode;

    while(ip < code.size()) {
        opcode = code[ip];
        if(vm.trace) {
            vm.disassemble(opcode);
        }
        ip++;
        switch (opcode)
        {
        case ICONST:
            operand = code[ip];
            ip++;
            sp++;
            stack[sp] = operand;
            break;
        case PRINT:
            operand = stack[sp];
            sp--;
            printf("%d\n", operand);
            break;
        case HALT:
            return;
        }
    }
}