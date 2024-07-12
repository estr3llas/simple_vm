#include "../headers/common.hpp"
#include "../headers/Bytecode.hpp"

namespace Examples {

    const int FACTORIAL_ADDRESS = 0;
    const int FACTORIAL_ENTRYPOINT = 23;
    std::vector<int32_t> factorial = {
//.def factorial: ARGS=1, LOCALS=0	ADDRESS
//	IF N < 2 RETURN 1
        LOAD, 0,                // 0
        ICONST, 2,              // 2
        ILT,                    // 4
        BRF, 10,                // 5
        ICONST, 1,              // 7
        RET,                    // 9
//CONT:
//	RETURN N * FACT(N-1)
        LOAD, 0,                // 10
        LOAD, 0,                // 12
        ICONST, 1,              // 14
        ISUB,                   // 16
        CALL, FACTORIAL_ADDRESS, 1, 0,    // 17
        IMUL,                   // 21
        RET,                    // 22
//.DEF MAIN: ARGS=0, LOCALS=0
// PRINT FACT(1)
        ICONST, 5,              // 23    <-- MAIN METHOD!
        CALL, FACTORIAL_ADDRESS, 1, 0,    // 25
        PRINT,                  // 29
        HALT                    // 30
    };

    const int MATH_ENTRYPOINT = 0;
    std::vector<int> math = {
    // MATH DEMONSTRATION
    // PUSH 1, 2
        ICONST, 1,                  // 0
        ICONST, 2,                  // 2
    // 1 + 2 = 3
        IADD,                       // 3
    // PUSH 1
        ICONST, 1,                  // 4
    // 3 - 1 = 2
        ISUB,                       // 6
    // PUSH 2
        ICONST, 2,                  // 7
    // 2 * 2 = 4
        IMUL,                       // 9
    // PUSH 4
        ICONST, 4,                  // 10
    // 4 * 4 = 16
        IMUL,                       // 12
    // PUSH 2
        ICONST, 2,                  // 13
    // 16 / 2 = 8
        IDIV,                       // 15
    // PRINT(8)
        PRINT,                      // 16
        HALT                        // 17
    };

    const int EXCEPTION_ENTRYPOINT = 0;
    std::vector<int> exception = {
    // TRIGGER EXCEPTION
    // STORE 1 ON GLOBAL MEMORY    
        ICONST, 1,                  // 0
        GSTORE, 0,                  // 2
    // STORE 0 ON GLOBAL MEMORY
        ICONST, 0,                  // 4
        GSTORE, 1,                  // 6
    // LOAD BOTH ON STACK
        GLOAD, 0,                   // 8
        GLOAD, 1,                   // 10
    // TRY TO DIVIDE 1 BY 0
        IDIV,                       // 11
    // CAUSES EXCEPTION
        PRINT,                      // 12
        HALT                        // 13
    };

    const int TEST_FUNC_ADDR = 12;
    const int TEST_ENTRYPOINT = 0;
    std::vector<int32_t> test = {
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