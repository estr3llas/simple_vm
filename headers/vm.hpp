#ifndef VM_VM_H
#define VM_VM_H

#include "./common.hpp"

#define DATA_MAX_SIZE 1000
#define STACK_MAX_SIZE DATA_MAX_SIZE
#define LOCALS_MAX_SIZE 256

#define VM_TRUE true
#define VM_FALSE false
#define VM_ZERO 0
#define VM_SP_START -1

class Context {
private:

    Context* prev;
    int32_t return_ip;
    std::vector<int32_t> locals;
public:
    Context() :
    return_ip(0)
    {}
    ;

    Context(Context* _prev, int32_t _return_ip) :
    prev(_prev),
    return_ip(_return_ip)
    {}
    ;

    std::vector<int32_t>& getLocals() {
        return locals;
    }

    int32_t getReturnIp() {
        return return_ip;
    }
};

class VM {
private:
    std::vector<int32_t> data;
    std::vector<int32_t> code;
    std::vector<int32_t> stack;

    Context ctx;

    std::string bc_filename;

    uint32_t ip;
    //must start below stack, every operation pushes something onto stack (preventing off by one)
    int32_t sp = VM_SP_START;
    int32_t fp;

    bool trace = false;
public:

    VM();
    VM(const std::vector<int>& bytecode, int32_t addr_of_main, size_t datasize);

    void execVM(int32_t entrypoint);
    void cpu();
    void disassemble(int32_t opcode);
    void vm_print(int32_t arg);

    uint32_t get_ip();

    void SetTrace(VM &vm, bool value);
    void set_bytecode_filename(const std::string &filename);
    const std::string &get_bytecode_filename();

    Context& getCtx(){
        return ctx;
    }

};

#endif