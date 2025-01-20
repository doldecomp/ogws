#ifndef NW4R_EF_RESOURCE_H
#define NW4R_EF_RESOURCE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace ef {

// Forward declarations
struct EmitterResource;

struct TextureProject {
    u32 headersize;       // at 0x0
    ut::Link projectlink; // at 0x4
    u16 projectnameLen;   // at 0xC
    u16 PADDING_0xE;      // at 0xE
    u8 projectname[4];    // at 0x10
};

struct EffectProject {
    u32 headersize;       // at 0x0
    ut::Link projectlink; // at 0x4
    u16 projectnameLen;   // at 0xC
    u16 PADDING_0xE;      // at 0xE
    u8 projectname[4];    // at 0x10
};

class Resource {
public:
    ut::List mBREFFList; // at 0x0
    u32 mNumEmitter;     // at 0xC
    ut::List mBREFTList; // at 0x10
    u32 mNumTexture;     // at 0x1C

public:
    static Resource* GetInstance();

    EmitterResource* _FindEmitter(const char* pName,
                                  EffectProject* pEffProject) const;
};

} // namespace ef
} // namespace nw4r

#endif
