#include <revolution/OS.h>
#include <runtime/Gecko_ExceptionPPC.h>
#include <runtime/global_destructor_chain.h>

static int fragmentID = -2;

#ifdef __cplusplus
extern "C" {
#endif
void __init_cpp_exceptions(void);
void __fini_cpp_exceptions(void);
#ifdef __cplusplus
}
#endif

static void* GetTOC(void) {
    register void* toc;

    // clang-format off
    asm {
        mr toc, r2
    };
    // clang-format on

    return toc;
}

void __init_cpp_exceptions(void) {
    if (fragmentID == -2) {
        fragmentID = __register_fragment(_eti_init_info, GetTOC());
    }
}

void __fini_cpp_exceptions(void) {
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

#pragma section ".ctors$10"
DECL_SECTION(".ctors$10")
funcptr_t __init_cpp_exceptions_reference = __init_cpp_exceptions;

#pragma section ".dtors$10"
DECL_SECTION(".dtors$10")
funcptr_t __destroy_global_chain_reference = __destroy_global_chain;

#pragma section ".dtors$15"
DECL_SECTION(".dtors$15")
funcptr_t __fini_cpp_exceptions_reference = __fini_cpp_exceptions;