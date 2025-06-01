#ifndef EGG_CORE_XFB_MANAGER_H
#define EGG_CORE_XFB_MANAGER_H
#include <egg/types_egg.h>

namespace EGG {

// Forward declarations
class Xfb;

class XfbManager {
public:
    XfbManager()
        : mQueueFront(NULL),
          mQueueEnd(NULL),
          mCopiedXfb(NULL),
          mShowXfb(NULL) {}

    bool attach(Xfb* pXfb);
    void copyEFB(bool clearEfb);
    void setNextFrameBuffer();
    void postVRetrace();

    bool isReadytoCopy() {
        return mQueueEnd != mCopiedXfb && mQueueEnd != mQueueFront;
    }

    Xfb* getShowXfb() {
        return mShowXfb;
    }
    Xfb* getCopiedXfb() {
        return mCopiedXfb;
    }

private:
    Xfb* mQueueFront; // at 0x0
    Xfb* mQueueEnd;   // at 0x4

    Xfb* mShowXfb;   // at 0x8
    Xfb* mCopiedXfb; // at 0xC
};

} // namespace EGG

#endif
