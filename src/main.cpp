#include <fstream>

#include "../headers/Bytecode.hpp"
#include "../headers/vm.hpp"

#include "../lib/include/boost/program_options.hpp"

#define MAIN_ADDR 0
#define VM_VERSION "0.0.1"
#define USAGE " Estrellas's simple vm.\n\n"                 \
              " Version: 0.0.1\n\n"                            \
              " [+] Usage: vm.exe -f [bytecode.txt]\n\n"    \
              " Contact: https://github.com/estr3llas\n"

namespace po = boost::program_options;

int main (int argc, char** argv) {

    if(argc < 2) {
        printf(USAGE, VM_VERSION);
    };

    po::options_description desc("Allowed Options");
    desc.add_options()
        ("-h", USAGE)
        ("-f", po::value<std::string>(), "specify the bytecode filename")
        ;

    po::variables_map var_map;
    po::store(po::parse_command_line(argc, argv, desc), var_map);
    po::notify(var_map);

    if(var_map.count("-h")) {
        std::cout << desc << std::endl;
        return 0;
    }

    if(var_map.count("-f")) {
        std::cout << var_map["-f"].as<std::string>() << std::endl;
    } else {
        std::cout << "No filename!";
    }

    printf("%s", argv[2]);

    /*
    VM vm_test(bytecode_from_file, 0, 0);
    vm_test.SetTrace(VM_TRUE);
    VMReturn ret = vm_test.VMExec();

    printf("\n[!] VMReturn: %d", ret);

    
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
