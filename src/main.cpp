
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

   return 0;
}
