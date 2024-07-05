#include "../headers/common.hpp"
#include "../headers/vm.hpp"
#include "../headers/exception_handler.hpp"

void ExceptionHandler::EH_exit(){
    exit(1);
}

void ExceptionHandler::EH_abort(){
    abort();
}

void ExceptionHandler::exceptionHandler(uint32_t exception_code, int32_t opcode) {

    if(exception_code == VM_ZERO) {
        return;
    }

    switch(exception_code){
        case EXCEPTION_DIVIDE_BY_ZERO:
            fprintf(stderr, "[-] EXCEPTION_DIVIDE_BY_ZERO: Operation not permitted.\n");
            EH_exit();
            break;
        case EXCEPTION_UNKNOWN_OPCODE:
            fprintf(stderr, "[-] EXCEPTION_UNKNOWN_OPCODE: Unknown ocpode: %d\n", opcode);
            EH_exit();
            break;
        default:
            return;
    }

}