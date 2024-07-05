#ifndef VM_VM_H
#define VM_VM_H

#include "./common.hpp"

#define DATA_MAX_SIZE 256
#define STACK_MAX_SIZE DATA_MAX_SIZE

#define VM_TRUE true
#define VM_FALSE false
#define VM_ZERO 0
#define VM_SP_START -1

class VM {
private:
    std::vector<int32_t> data;
    std::vector<int32_t> code;
    std::vector<int32_t> stack;

    uint32_t ip;
    //must start below stack, every operation pushes something onto stack (preventing off by one)
    int32_t sp = VM_SP_START;
    int32_t fp;

    bool trace = false;
public:

    VM();
    VM(const std::vector<int>& bytecode, size_t datasize);

    void cpu(VM &vm);
    void SetTrace(VM &vm, bool value);
    void disassemble(int32_t opcode);

};

#endif