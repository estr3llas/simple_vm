#include "../headers/Bytecode.hpp"
#include "../headers/vm.hpp"

int main (int argc, char** argv) {  
    
    std::vector<int> bytecode = {
        ICONST, 2,
        ICONST, 2,
        IDIV,
        PRINT,
        HALT
    };

    VM vm(bytecode, DATA_MAX_SIZE);
    
    vm.SetTrace(vm, VM_TRUE);
    vm.cpu(vm);
}