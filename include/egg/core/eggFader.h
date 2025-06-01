#ifndef EGG_CORE_FADER_H
#define EGG_CORE_FADER_H
#include <egg/types_egg.h>

namespace EGG {

class Fader {
public:
    enum EStatus {
        STATUS_PREPARE_IN,
        STATUS_PREPARE_OUT,
        STATUS_FADE_IN,
        STATUS_FADE_OUT
    };

public:
    virtual void setStatus(EStatus status) = 0; // at 0x8
    virtual EStatus getStatus() const = 0;      // at 0xC

    virtual bool fadeIn() = 0;  // at 0x10
    virtual bool fadeOut() = 0; // at 0x14

    virtual bool calc() = 0; // at 0x18
    virtual void draw() = 0; // at 0x1C
};

} // namespace EGG

#endif
