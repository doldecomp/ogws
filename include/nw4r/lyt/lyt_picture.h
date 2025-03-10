#ifndef NW4R_LYT_PICTURE_H
#define NW4R_LYT_PICTURE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_common.h>
#include <nw4r/lyt/lyt_pane.h>

namespace nw4r {
namespace lyt {

// Forward declarations
struct ResBlockSet;
class TexMap;

namespace res {

/******************************************************************************
 *
 * PIC1 binary layout
 *
 ******************************************************************************/
struct Picture : Pane {
    static const u32 SIGNATURE = 'pic1';

    u32 vtxCols[VERTEXCOLOR_MAX]; // at 0x4C
    u16 materialIdx;              // at 0x5C
    u8 texCoordNum;               // at 0x5E
    u8 PADDING_0x5F;              // at 0x5F
};

} // namespace res

/******************************************************************************
 *
 * Picture
 *
 ******************************************************************************/
class Picture : public Pane {
public:
    NW4R_UT_RTTI_DECL(Picture);

public:
    Picture(u8 num);
    Picture(const res::Picture* pRes, const ResBlockSet& rBlockSet);
    virtual ~Picture(); // at 0x8

    virtual void DrawSelf(const DrawInfo& rInfo); // at 0x18

    virtual ut::Color GetVtxColor(u32 idx) const;       // at 0x24
    virtual void SetVtxColor(u32 idx, ut::Color color); // at 0x28

    virtual u8 GetVtxColorElement(u32 idx) const;       // at 0x34
    virtual void SetVtxColorElement(u32 idx, u8 value); // at 0x38

    virtual void Append(const TexMap& rTexMap); // at 0x64

protected:
    ut::Color mVtxColors[VERTEXCOLOR_MAX]; // at 0xD4
    detail::TexCoordAry mTexCoordAry;      // at 0xE4

protected:
    void ReserveTexCoord(u8 num);
    void SetTexCoordNum(u8 num);

private:
    void Init(u8 num);
};

} // namespace lyt
} // namespace nw4r

#endif
