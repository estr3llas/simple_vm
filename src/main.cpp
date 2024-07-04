#include "../headers/Bytecode.hpp"
#include "../headers/vm.hpp"

int main (int argc, char** argv) {  
    
    std::vector<int> bytecode = {
        ICONST, 99,
        PRINT,
        HALT
    };

    VM vm(bytecode, 256);
    
    vm.SetTrace(vm, true);
    vm.cpu(vm);
}