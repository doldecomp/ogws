#ifndef RP_KERNEL_TAG_PROCESSOR_H
#define RP_KERNEL_TAG_PROCESSOR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <nw4r/ut.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Wide-char text tag processor
 */
class RPSysTagProcessor : public nw4r::ut::WideTagProcessor {
    RP_SINGLETON_DECL(RPSysTagProcessor);

public:
    void PreProcessEx(wchar_t const*, wchar_t*, u32, int*, int, va_list);

    void PreProcessEx(wchar_t const*, wchar_t*, u32, int*, int, ...);
};

//! @}

#endif
