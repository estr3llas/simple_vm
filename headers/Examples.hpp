#include "../headers/common.hpp"
#include "../headers/Bytecode.hpp"

namespace Examples {

    const int TEST_FUNC_ADDR = 12;
    std::vector<int32_t> test_bc = {
        ICONST, 1,
        CALL, TEST_FUNC_ADDR, 1, 0,
        ICONST, 2,
        DEC,
        NOP,
        PRINT,
        HALT,

        ICONST, 3,
        POP,
        RET
    };

}