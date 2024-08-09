#ifndef NW4R_SND_FX_BASE_H
#define NW4R_SND_FX_BASE_H
#include "snd_Common.h"
#include "types_nw4r.h"
#include "ut_LinkList.h"

namespace nw4r {
namespace snd {

struct FxBase {
    inline virtual ~FxBase() {}          // at 0x8
    inline virtual bool StartUp() {}     // at 0xc
    inline virtual UNKTYPE Shutdown() {} // at 0x10
    inline virtual UNKTYPE UpdateBuffer(int, void**, u32, SampleFormat, float,
                                        OutputMode) {} // at 0x14

    NW4R_UT_LIST_NODE_DECL(); // at 0x4
};

NW4R_UT_LIST_TYPEDEF_DECL(FxBase);

} // namespace snd
} // namespace nw4r

#endif