#ifndef EGG_AUDIO_AUDIO_SYSTEM_H
#define EGG_AUDIO_AUDIO_SYSTEM_H
#include <egg/types_egg.h>

namespace EGG {

class AudioSystem {
public:
    enum EResetStatus {
        RESET_STATUS_NONE,
        RESET_STATUS_QUEUED,
        RESET_STATUS_FINISH,
    };

    enum EShutDownStatus {
        SHUTDOWN_STATUS_NONE,
        SHUTDOWN_STATUS_QUEUED,
        SHUTDOWN_STATUS_FINISH,
    };

public:
    static AudioSystem* instance() {
        return sInstanse;
    }

    void calc();

    EResetStatus getResetStatus() {
        return mResetStatus;
    }
    EShutDownStatus getShutDownStatus() {
        return mShutDownStatus;
    }

private:
    AudioSystem();
    ~AudioSystem();

private:
    f32 FLOAT_0x0;
    EResetStatus mResetStatus;       // at 0x4
    EShutDownStatus mShutDownStatus; // at 0x8

    static AudioSystem* sInstanse;
};

} // namespace EGG

#endif
