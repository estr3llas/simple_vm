#ifndef VM_VM_H
#define VM_VM_H

#include "./common.hpp"

#define DATA_MAX_SIZE 4096
#define STACK_MAX_SIZE 1000
#define LOCALS_MAX_SIZE 256

#define VM_TRUE true
#define VM_FALSE false
#define VM_ZERO 0
#define VM_SP_START -1

class Context {
private:

    Context* prev;
    uint32_t return_ip;
public:

    std::vector<int32_t> locals;

    Context() :
    return_ip(0)
    {}
    ;

    Context(Context* _prev, uint32_t _return_ip, int32_t number_of_locals) :
    prev(_prev),
    return_ip(_return_ip),
    locals(number_of_locals)
    {}
    ;

    std::vector<int32_t>& getLocals() {
        return locals;
    }

    int32_t getReturnIp() {
        return return_ip;
    }

    Context* getPrev() {
        return prev;
    }
};

typedef enum {
    STATUS_EXECUTION_OK = 0,
    STATUS_COMPILE_ERROR = 1,
    STATUS_RUNTIME_ERROR = 2,
} VMReturn;

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
    VM(const std::vector<int>& bytecode, int32_t entrypoint, size_t datasize);

    VMReturn VMExec();
    void Cpu();
    void Disassemble(int32_t opcode);
    void VMPrint(int32_t arg);

    uint32_t get_ip();

    void SetTrace(bool value);
    void SetBcFilename(const std::string &filename);
    const std::string &GetBcFilename();

    Context& GetCtx(){
        return ctx;
    }

};

#endif