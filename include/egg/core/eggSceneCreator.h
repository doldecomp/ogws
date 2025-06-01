#ifndef EGG_CORE_SCENE_CREATOR_H
#define EGG_CORE_SCENE_CREATOR_H
#include <egg/types_egg.h>

namespace EGG {

// Forward declarations
class Scene;

class SceneCreator {
public:
    virtual Scene* create(s32 id) = 0; // at 0x8
    virtual void destroy(s32 id) = 0;  // at 0xC
};

} // namespace EGG

#endif
