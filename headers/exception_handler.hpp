#ifndef VM_EXCEPTION_HANDLER_H
#define VM_EXCEPTION_HANDLER_H

#include "common.hpp"
#include "vm.hpp"

class ExceptionHandler : public VM {
public:

    enum exception_codes {
        EXCEPTION_DIVIDE_BY_ZERO = 1,
        EXCEPTION_UNKNOWN_OPCODE = 2,
    };

    void Handler(uint32_t exception_code, int32_t opcode);

    void EH_exit();
    void EH_abort();
};

#endif