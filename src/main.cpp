
#include "../headers/common.hpp"
#include "../headers/Bytecode.hpp"
#include "../headers/vm.hpp"
#include "../headers/Examples.hpp"

//#include "../lib/include/boost/program_options.hpp"

#define MAIN_ADDR 0
#define VM_VERSION "0.0.1"
#define USAGE " Estrellas's simple vm.\n\n"                     \
              " Version: 0.0.1\n\n"                             \
              " [+] Usage: vm.exe <bytecode.txt>\n\n"           \
              " Contact: https://github.com/estr3llas\n"


int main (int argc, char** argv) {

    if(argc < 2) {
        printf(USAGE, VM_VERSION);
    };

    VM vm_test(Examples::test, Examples::TEST_ENTRYPOINT, 0);
    vm_test.SetTrace(VM_TRUE);
    VMReturn ret = vm_test.VMExec();

    printf("\n[!] VMReturn: %d", ret);

    /*
    VM vm_fact(factorial, 23, 0);
    vm_fact.SetTrace(VM_TRUE);
    vm_fact.execVM(23);

    VM vm_loop(bc_loop, MAIN_ADDR, 0);
    vm_loop.set_bytecode_filename(__FILE__);
    vm_loop.SetTrace(vm_loop, VM_TRUE);
    vm_loop.cpu();

    
    VM vm_exception(bc_exception_divide_by_zero, MAIN_ADDR, 0);
    vm_exception.set_bytecode_filename(__FILE__);
    vm_exception.SetTrace(vm_exception, VM_TRUE);
    vm_exception.execVM(MAIN_ADDR);
    
    
    VM vm_math(bc_math, 0, 0);
    vm_math.set_bytecode_filename(__FILE__);
    vm_math.SetTrace(vm_math, VM_TRUE);
    vm_math.execVM(MAIN_ADDR);
    */

   return 0;
}
