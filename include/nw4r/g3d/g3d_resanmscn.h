#ifndef NW4R_G3D_RESANMSCN_H
#define NW4R_G3D_RESANMSCN_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_resanmamblight.h>
#include <nw4r/g3d/g3d_resanmcamera.h>
#include <nw4r/g3d/g3d_resanmfog.h>
#include <nw4r/g3d/g3d_resanmlight.h>
#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_reslightset.h>

namespace nw4r {
namespace g3d {

struct ResAnmScnInfoData {
    u16 numFrame;              // at 0x0
    u16 numSpecularLight;      // at 0x2
    AnmPolicy policy;          // at 0x4
    u16 numResLightSetData;    // at 0x8
    u16 numResAnmAmbLightData; // at 0xA
    u16 numResAnmLightData;    // at 0xC
    u16 numResAnmFogData;      // at 0xE
    u16 numResAnmCameraData;   // at 0x10
    u8 padding_[2];            // at 0x12
};

struct ResAnmScnData {
    ResBlockHeaderData header;     // at 0x0
    u32 revision;                  // at 0x8
    s32 toResFileData;             // at 0xC
    s32 toScnTopLevelDic;          // at 0x10
    s32 toResLightSetDataArray;    // at 0x14
    s32 toResAnmAmbLightDataArray; // at 0x18
    s32 toResAnmLightDataArray;    // at 0x1C
    s32 toResAnmFogDataArray;      // at 0x20
    s32 toResAnmCameraDataArray;   // at 0x24
    s32 name;                      // at 0x28
    s32 original_path;             // at 0x2C
    ResAnmScnInfoData info;        // at 0x30
};

class ResAnmScn : public ResCommon<ResAnmScnData> {
public:
    static const u32 SIGNATURE = 'SCN0';
    static const int REVISION = 4;

public:
    NW4R_G3D_RESOURCE_FUNC_DEF(ResAnmScn);

    bool Bind(ResAnmScn scene);

    bool Bind() {
        return Bind(*this);
    }

    u32 GetRevision() const {
        return ref().revision;
    }

    bool CheckRevision() const {
        return GetRevision() == REVISION;
    }

    bool HasResAnmAmbLight() const;
    bool HasResAnmLight() const;

    ResLightSet GetResLightSet(int i) const;
    ResLightSet GetResLightSet(u32 i) const;
    u32 GetResLightSetNumEntries() const;

    ResAnmAmbLight GetResAnmAmbLight(ResName name) const;
    ResAnmAmbLight GetResAnmAmbLight(int i) const;

    ResAnmLight GetResAnmLight(ResName name) const;
    ResAnmLight GetResAnmLight(int i) const;

    ResLightSet GetResLightSetByRefNumber(u32 refNumber) const;
    ResAnmAmbLight GetResAnmAmbLightByRefNumber(u32 refNumber) const;
    ResAnmLight GetResAnmLightByRefNumber(u32 refNumber) const;
    ResAnmFog GetResAnmFogByRefNumber(u32 refNumber) const;
    ResAnmCamera GetResAnmCameraByRefNumber(u32 refNumber) const;

    u16 GetResAnmFogMaxRefNumber() const {
        return ref().info.numResAnmFogData;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
