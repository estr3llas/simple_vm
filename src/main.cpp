#include "../headers/Bytecode.hpp"
#include "../headers/vm.hpp"

#define MAIN_ADDR 0

    std::vector<int> bc_loop = {
	// .GLOBALS 2; N, I
	// N = 10						ADDRESS
			ICONST, 10,				// 0
			GSTORE, 0,				// 2
	// I = 0
			ICONST, 0,				// 4
			GSTORE, 1,				// 6
	// WHILE I<N:
			GLOAD, 1,				// 8
			GLOAD, 0,				// 10
			ILT,					// 12
			BRF, 24,				// 13
	// I = I + 1
			GLOAD, 1,				// 15
			ICONST, 1,				// 17
			IADD,					// 19
			GSTORE, 1,				// 20
			BR, 8,					// 22
	// DONE (24):
			HALT					// 24
    };

    std::vector<int> bc_exception_divide_by_zero = {
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

    std::vector<int> bc_math = {
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

    const int FACTORIAL_ADDRESS = 0;
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

const int FUNC_ADDR = 10;
std::vector<int> test_bc = {
    ICONST, 1,
    CALL, FUNC_ADDR, 1, 0,
    ICONST, 2,
    PRINT,
    HALT,

    ICONST, 3,
    RET
};

int main (int argc, char** argv) {  

    VM vm_test(test_bc, 0, 0);
    vm_test.SetTrace(VM_TRUE);
    vm_test.VMExec();

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
}
