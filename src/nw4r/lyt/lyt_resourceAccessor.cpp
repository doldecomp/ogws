#include <nw4r/lyt.h>

namespace nw4r {
namespace lyt {

ResourceAccessor::~ResourceAccessor() {}

ResourceAccessor::ResourceAccessor() {}

ut::Font* ResourceAccessor::GetFont(const char* pName) {
#pragma unused(pName)

    return NULL;
}

} // namespace lyt
} // namespace nw4r
