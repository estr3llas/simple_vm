#ifndef VM_EXCEPTION_HANDLER_H
#define VM_EXCEPTION_HANDLER_H

#include "common.hpp"
#include "vm.hpp"

class ExceptionHandler : public VM{
public:

    enum exception_codes {
        EXCEPTION_DIVIDE_BY_ZERO = 1,
        EXCEPTION_UNKNOWN_OPCODE = 2,
        EXCEPTION_ARITHMETIC_OVERFLOW = 3,
        EXCEPTION_IP_OVERFLOW = 4,
    };

    bool CheckForArithmeticOverflow(int32_t operand1, int32_t operand2, int32_t opcode);

    void Handler(uint32_t exception_code, int32_t opcode);

    void EH_exit();
    void EH_abort();
};

#endif