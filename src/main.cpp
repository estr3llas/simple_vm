#include "../headers/Bytecode.hpp"
#include "../headers/vm.hpp"

#define MAIN_ADDR 0

int main (int argc, char** argv) {  
    
    std::vector<int> bytecode = {
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

    std::vector<int> exception_divide_by_zero = {
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


    VM vm_loop(bytecode, MAIN_ADDR, 0);
    //vm_loop.SetTrace(vm_loop, VM_TRUE);
    vm_loop.cpu(vm_loop);

    
    VM vm_exception(exception_divide_by_zero, MAIN_ADDR, 0);
    vm_exception.SetTrace(vm_exception, VM_TRUE);
    vm_exception.cpu(vm_exception);
    
}