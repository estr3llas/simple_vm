#ifndef VM_VM_H
#define VM_VM_H

#include "./common.hpp"

class VM {
private:
    std::vector<int32_t> data;
    std::vector<int32_t> code;
    std::vector<int32_t> stack;

    uint32_t ip;
    //must start below stack, every operation pushes something onto stack (preventing off by one)
    int32_t sp = -1;
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