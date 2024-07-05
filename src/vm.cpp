#include "../headers/common.hpp"
#include "../headers/vm.hpp"
#include "../headers/Bytecode.hpp"

VM::VM() :
    ip(VM_ZERO),
    sp(sp),
    fp(VM_ZERO)
    {};

VM::VM(const std::vector<int>& bytecode, size_t datasize) :
    code(bytecode),
    ip(VM_ZERO),
    data(
        datasize 
            != DATA_MAX_SIZE 
            ? datasize 
            : DATA_MAX_SIZE
        ),
    stack(STACK_MAX_SIZE) 
    {};
    
void VM::SetTrace(VM &vm, bool value) {
    vm.trace = value;
}

void VM::vmExit(){
    exit(-1);
}

void VM::exceptionHandler(uint32_t exception_code) {

    if(exception_code == VM_ZERO) {
        return;
    }

    switch(exception_code){
        case EXCEPTION_DIVIDE_BY_ZERO:
            fprintf(stderr, "[-] EXCEPTION_DIVIDE_BY_ZERO: Operation not permitted.\n");
            vmExit();
            break;
        default:
            return;
    }

}

void VM::disassemble(int32_t opcode) {
    Instruction instr = opcodes[opcode];
    printf("%04d: %s", ip, instr.getMnemonic());

    //print operands
    if(instr.getOperand() == 1){
        printf(" %d", code[ip+1]);
    } else if(instr.getOperand() == 2) {
        printf(" %d, %d", code[ip+1], code[ip+2]);
    }

    //print current stack
    if (sp == -1) {
        printf("\t\t[ ]\n");
    } else {
        printf("\t\t");
        for (int i = 0; i <= sp; ++i) {
            printf("[%d]", stack[i]);
            if (i < sp) {
                printf(", ");
            }
        }

        printf("\n");
    }
}

void VM::cpu(VM &vm) {
    
    int32_t operand;
    int32_t opcode, a, b;

    while(ip < code.size()) {
        opcode = code[ip];
        if(vm.trace) {
            vm.disassemble(opcode);
        }
        ip++;
        switch (opcode)
        {
        case IADD:
            b = stack[sp--];
            a = stack[sp--];
            stack[++sp] = a + b;
            break;
        case ISUB:
            b = stack[sp--];
            a = stack[sp--];
            stack[++sp] = a - b;
            break;
        case IMUL:
            b = stack[sp--];
            a = stack[sp--];
            stack[++sp] = a * b;
            break;
        case IDIV:
            b = stack[sp--];
            a = stack[sp--];
            if(b == 0) {
                exceptionHandler(EXCEPTION_DIVIDE_BY_ZERO);
            }
            stack[++sp] = a / b;
            break;
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