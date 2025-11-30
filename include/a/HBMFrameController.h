#ifndef HOME_BUTTON_MINI_LIB_FRAME_CONTROLLER_H
#define HOME_BUTTON_MINI_LIB_FRAME_CONTROLLER_H
#include <homebuttonMiniLib/HBMTypes.h>

namespace homebutton {

class FrameController {
public:
    enum eState {
        eState_Stopped,
        eState_Playing,
    };

    enum eAnmType {
        eAnmType_Forward,
        eAnmType_Backward,
        eAnmType_Wrap,
        eAnmType_Oscillate,

        eAnmType_Max
    };

public:
    FrameController() {}
    virtual ~FrameController() {} // at 0x8

    virtual void calc(); // at 0xC

    void init(int anmType, f32 maxFrame, f32 minFrame, f32 delta);
    void initFrame();

    void start() {
        initFrame();
        restart();
    }

    void restart() {
        mState = eState_Playing;
    }
    void stop() {
        mState = eState_Stopped;
    }

    f32 getMaxFrame() const {
        return mMaxFrame;
    }
    f32 getCurrentFrame() const {
        return mCurFrame;
    }
    f32 getLastFrame() const {
        return mMaxFrame - 1.0f;
    }
    bool isPlaying() const {
        return mState == eState_Playing;
    }

    void setAnmType(int anmType) {
        mAnmType = anmType;
    }

protected:
    f32 mMaxFrame;   // at 0x4
    f32 mMinFrame;   // at 0x8
    f32 mCurFrame;   // at 0xC
    f32 mFrameDelta; // at 0x10
    int mState;      // at 0x14
    int mAnmType;    // at 0x18
    bool mAltFlag;   // at 0x1C
};

} // namespace homebutton

#endif
