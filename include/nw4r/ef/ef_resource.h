#ifndef NW4R_EF_RESOURCE_H
#define NW4R_EF_RESOURCE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_res_emitter.h>
#include <nw4r/ef/ef_res_texture.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace ef {

// Forward declarations
struct EmitterResource;

struct EffectProject {
    u32 headersize;       // at 0x0
    ut::Link projectlink; // at 0x4
    u16 projectnameLen;   // at 0xC
    u16 PADDING_0xE;      // at 0xE
    u8 projectname[4];    // at 0x10
};

struct TextureProject {
    u32 headersize;       // at 0x0
    ut::Link projectlink; // at 0x4
    u16 projectnameLen;   // at 0xC
    u16 PADDING_0xE;      // at 0xE
    u8 projectname[4];    // at 0x10
};

class Resource {
private:
    static const u16 VERSION = 7;

public:
    ut::List mBREFFList; // at 0x0
    u32 mNumEmitter;     // at 0xC
    ut::List mBREFTList; // at 0x10
    u32 mNumTexture;     // at 0x1C

public:
    static u16 GetVersion() {
        return VERSION;
    }

    static Resource* GetInstance();

    EffectProject* Add(u8* pData);
    TextureProject* AddTexture(u8* pData);

    ResEmitter FindEmitter(const char* pName, EffectProject* pEffProject) const;
    EmitterResource* _FindEmitter(const char* pName,
                                  EffectProject* pEffProject) const;

    u32 NumEmitter(EffectProject* pEffProject) const;
    EmitterResource* _GetEmitterIndexOf(u32 idx,
                                        EffectProject* pEffProject) const;

    ResTexture FindTexture(const char* pName,
                           TextureProject* pTexProject) const;
    TextureData* _FindTexture(const char* pName,
                              TextureProject* pTexProject) const;

    u32 RelocateCommand();

    bool RemoveEffectProject(EffectProject* pEffProject);
    bool RemoveTextureProject(TextureProject* pTexProject);

private:
    Resource();

    void Initialize();

    u32 relocateCurveTexture(u8* pCmdList);
    u32 relocateCurveChild(u8* pCmdList);

private:
    static Resource mResource;
};

} // namespace ef
} // namespace nw4r

#endif
