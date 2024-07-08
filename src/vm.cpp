#include "../headers/common.hpp"
#include "../headers/vm.hpp"
#include "../headers/Bytecode.hpp"
#include "../headers/exception_handler.hpp"

int_fast32_t global_mem[DATA_MAX_SIZE];

VM::VM() :
    ip(VM_ZERO),
    sp(sp),
    fp(VM_ZERO),
    ctx(Context(nullptr, 0, LOCALS_MAX_SIZE))
    {};

VM::VM(const std::vector<int>& bytecode, int32_t addr_of_main, size_t datasize) :
    code(bytecode),
    ip(addr_of_main),
    data(
        datasize 
            != DATA_MAX_SIZE 
            ? datasize 
            : DATA_MAX_SIZE
        ),
    stack(STACK_MAX_SIZE),
    ctx(Context(nullptr, 0, LOCALS_MAX_SIZE))
    {};
    
void VM::SetTrace(bool value) {
    trace = value;
}

void VM::vm_print(int32_t arg){
    printf("%d\n", arg);
}

uint32_t VM::get_ip() {
    return ip;
}

void VM::set_bytecode_filename(const std::string &filename) {
    if(filename.empty()) bc_filename = nullptr;

    bc_filename = filename;
}

const std::string& VM::get_bytecode_filename() {
    return bc_filename;
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

void VM::execVM(int32_t entrypoint) {
    ip = entrypoint;
    ctx = Context();
    cpu();
}

void VM::cpu() {
    
    int32_t operand;
    int32_t opcode, a, b, addr, offset;

    int32_t first_arg;
    //instruction-specific variables
    int32_t nargs, rvalue;
    ExceptionHandler _exception_handler;

    while(ip < code.size()) {
        opcode = code[ip];
        if(trace) {
            disassemble(opcode);
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
        case CALL:
            addr = code[ip++];
            nargs = code[ip++];
            ctx = Context(&ctx, ip, LOCALS_MAX_SIZE);
            first_arg = sp - (nargs + 1);
            for(int8_t i = 0; i < nargs; i++) {
                ctx.locals[i] = stack[first_arg+i];
            }
            sp -= nargs;
            ip = addr;
            break;
        case RET:
            ip = ctx.getReturnIp();
            ctx = *ctx.getPrev();
            break;
        case LOAD:
            offset = code[ip++];
            stack[++sp] = stack[fp+offset];
            break;
        case IEQ:
            b = stack[sp--];
            a = stack[sp--];
            stack[++sp] = (a == b) ? VM_TRUE : VM_FALSE;
            break;
        case ILT:
            b = stack[sp--];
            a = stack[sp--];
            stack[++sp] = (a < b) ? VM_TRUE : VM_FALSE;
            break;
        case BR:
            ip = code[ip++];
            break;
        case BRT:
            addr = code[ip++];
            if (stack[sp--] == VM_TRUE) ip = addr;
        case BRF:
            addr = code[ip++];
            if (stack[sp--] == VM_FALSE) ip = addr;
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
            stack[++sp] = code[ip++];
            break;
        case POP:
            --sp;
            break;
        case PRINT:
            vm_print(stack[sp--]);
            break;
        case HALT:
            return;
        default:
            _exception_handler.Handler(_exception_handler.EXCEPTION_UNKNOWN_OPCODE, opcode);
            return;
        }
    }
}