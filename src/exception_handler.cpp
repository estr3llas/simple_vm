#include "../headers/common.hpp"
#include "../headers/vm.hpp"
#include "../headers/exception_handler.hpp"

void ExceptionHandler::EH_exit(){
    exit(1);
}

void ExceptionHandler::EH_abort(){
    abort();
}

void ExceptionHandler::Handler(VM &vm, uint32_t exception_code, int32_t opcode) {

    if(exception_code == VM_ZERO) {
        return;
    }

    const std::string &filename = vm.get_bytecode_filename();

    switch(exception_code){
        case EXCEPTION_DIVIDE_BY_ZERO:
            fprintf(stderr, "\n[-] Line %d in %s:\n\tEXCEPTION_DIVIDE_BY_ZERO: Operation not permitted.\n", (vm.get_ip()-1), filename.c_str());
            EH_exit();
            break;
        case EXCEPTION_UNKNOWN_OPCODE:
            fprintf(stderr, "\n[-] Line %d in %s:\n\t[-] EXCEPTION_UNKNOWN_OPCODE: Unknown opcode: %d\n", (vm.get_ip()-1), filename.c_str(), opcode);
            EH_exit();
            break;
        default:
            return;
    }

}