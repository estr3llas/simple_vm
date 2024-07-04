#include "Bytecode.hpp"
#include "vm.hpp"

int main (int argc, char** argv) {
    Bytecode bc;
    
    std::vector<int> bytecode = {
        ICONST, 99,
        PRINT,
        HALT
    };

    VM vm(bytecode, 256);
    
    vm.SetTrace(vm, true);
    vm.cpu(vm);
}