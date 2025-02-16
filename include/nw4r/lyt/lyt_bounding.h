#ifndef NW4R_LYT_TEX_MAP_H
#define NW4R_LYT_TEX_MAP_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_pane.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace lyt {

namespace res {

/******************************************************************************
 *
 * BND1 binary layout
 *
 ******************************************************************************/
struct Bounding : Pane {};

} // namespace res

/******************************************************************************
 *
 * Bounding
 *
 ******************************************************************************/
class Bounding : public Pane {
public:
    NW4R_UT_RTTI_DECL(Bounding);

public:
    Bounding(const res::Bounding* pRes, const ResBlockSet& rBlockSet);
    virtual ~Bounding(); // at 0x8

    virtual void DrawSelf(const DrawInfo& rInfo); // at 0x18
};

} // namespace lyt
} // namespace nw4r

#endif
