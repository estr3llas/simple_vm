#include "../headers/common.hpp"
#include "../headers/vm.hpp"
#include "../headers/Bytecode.hpp"
#include "../headers/exception_handler.hpp"

int_fast32_t global_mem[DATA_MAX_SIZE];

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

void VM::disassemble(int32_t opcode) {

    if (ip >= code.size()) return;

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
    int32_t opcode, a, b, addr;
    ExceptionHandler _exception_handler;

    while(ip < code.size()) {
        opcode = code[ip];
        if(vm.trace) {
            vm.disassemble(opcode);
        }
        ip++;
        switch (opcode)
        {
        case GLOAD:
            addr = code[ip];
            ip++;
            operand = global_mem[addr];
            sp++;
            stack[sp] = operand;
            break;
        case GSTORE:
            operand = stack[sp];
            sp--;
            addr = code[ip];
            ip++;
            global_mem[addr] = operand;
            break;
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
                _exception_handler.Handler(_exception_handler.EXCEPTION_DIVIDE_BY_ZERO, opcode);
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
        default:
            _exception_handler.Handler(_exception_handler.EXCEPTION_UNKNOWN_OPCODE, opcode);
            return;
        }
    }
}