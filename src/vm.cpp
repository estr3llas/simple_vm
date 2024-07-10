#include "../headers/common.hpp"
#include "../headers/vm.hpp"
#include "../headers/Bytecode.hpp"
#include "../headers/exception_handler.hpp"

VM::VM() :
    ip(VM_ZERO),
    sp(sp),
    fp(VM_ZERO),
    ctx(Context(nullptr, 0, LOCALS_MAX_SIZE))
    {};

VM::VM(const std::vector<int>& bytecode, int32_t entrypoint, size_t datasize) :
    code(bytecode),
    ip(entrypoint),
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

void VM::VMPrint(int32_t arg){
    printf("%d\n", arg);
}

uint32_t VM::get_ip() {
    return ip;
}

void VM::SetBcFilename(const std::string &filename) {
    if(filename.empty()) bc_filename = nullptr;

    bc_filename = filename;
}

const std::string& VM::GetBcFilename() {
    return bc_filename;
}

void VM::Disassemble(int32_t opcode) {

    if (ip >= code.size()) return;

    Instruction instr = opcodes[opcode];
    printf("%04d: %-16s", ip, instr.getMnemonic());

    bool noops = false;
    //print operands
    int operandCount = instr.getOperand();
    switch (operandCount) {
        case 1:
            printf(" %d", code[ip + 1]);
            break;
        case 2:
            printf(" %d, %d", code[ip + 1], code[ip + 2]);
            break;
        case 3:
            printf(" %d, %d, %d", code[ip + 1], code[ip + 2], code[ip + 3]);
            break;
        default:
            noops = true;
            break;
    }

    //print current stack
    printf("\t\t");
    if(noops) printf("\t");
    if (sp == -1) {
        printf("[ ]\n");
    } else {
        printf("[");
        for (int i = 0; i <= sp; ++i) {
        printf("%d", stack[i]);
        if (i < sp) {
            printf(", ");
        }
        }
        printf("]\n");
    }
}

VMReturn VM::VMExec() {
    //ctx = Context();
    Cpu();
    return STATUS_EXECUTION_OK;
}

int_fast32_t global_mem[DATA_MAX_SIZE];

void VM::Cpu() {
    
    int32_t operand, opcode, a, b, addr, offset;
    int32_t first_arg;
    int32_t nargs, locals;
    ExceptionHandler _exception_handler;

    bool arithmetic_overflow;

    std::vector<Context> call_stack;

    while(ip < code.size()) {
        opcode = code[ip];
        if(trace) {
            Disassemble(opcode);
        }
        ip++;
        switch (opcode) {
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
            locals = code[ip++];
            call_stack.push_back(ctx);
            ctx = Context(&call_stack.back(), ip, LOCALS_MAX_SIZE);
            first_arg = sp - (nargs + 1);
            for (int i = 0; i < nargs; i++) {
                ctx.getLocals()[i] = stack[first_arg + i];
            }
            sp -= nargs;
            ip = addr;
            break;
        case RET:
            //ctx = call_stack.back();
            call_stack.pop_back();
            ip = ctx.getReturnIp();
            break;
        case LOAD:
            offset = code[ip++];
            ctx = Context(&ctx, ip, LOCALS_MAX_SIZE);
            stack[++sp] = ctx.getLocals()[offset];
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
            break;
        case BRF:
            addr = code[ip++];
            if (stack[sp--] == VM_FALSE) ip = addr;
            break;
        case IADD:
            b = stack[sp--];
            a = stack[sp--];
            arithmetic_overflow = _exception_handler.CheckForArithmeticOverflow(a, b, opcode);
            stack[++sp] = a + b;
            break;
        case ISUB:
            b = stack[sp--];
            a = stack[sp--];
            arithmetic_overflow = _exception_handler.CheckForArithmeticOverflow(a, b, opcode);
            stack[++sp] = a - b;
            break;
        case IMUL:
            b = stack[sp--];
            a = stack[sp--];
            arithmetic_overflow = _exception_handler.CheckForArithmeticOverflow(a, b, opcode);
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
        case NEG:
            a = stack[sp--];
            stack[++sp] = (-a);
            break;
        case INC:
            a = stack[sp--];
            a = a + 1;
            stack[++sp] = a;
            break;
        case DEC:
            a = stack[sp--];
            a = a - 1;
            stack[++sp] = a;
            break;
        case ICONST:
            stack[++sp] = code[ip++];
            break;
        case POP:
            --sp;
            break;
        case PRINT:
            VMPrint(stack[sp--]);
            break;
        case HALT:
            return;
        default:
            _exception_handler.Handler(_exception_handler.EXCEPTION_UNKNOWN_OPCODE, opcode);
            return;
        }
    }
}