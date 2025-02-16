#ifndef NW4R_LYT_RESOURCE_ACCESSOR_H
#define NW4R_LYT_RESOURCE_ACCESSOR_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace lyt {

class ResourceAccessor {
public:
    ResourceAccessor();
    virtual ~ResourceAccessor(); // at 0x8

    virtual void* GetResource(u32 type, const char* pName,
                              u32* pSize) = 0; // at 0xC

    virtual ut::Font* GetFont(const char* pName); // at 0x10
};

} // namespace lyt
} // namespace nw4r

#endif
