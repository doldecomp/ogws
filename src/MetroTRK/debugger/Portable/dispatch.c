#include <MetroTRK.h>

DSError TRKInitializeDispatcher(void) { return kNoError; }

DSError TRKDispatchMessage(TRKMessageBuffer* buf) {
    DSError err = kMsgInvalid;

    TRKSetBufferPosition(buf, 0);
    switch (TRKMessageBufferGet(buf, unsigned char, 4)) {
    case kDSConnect:
        err = TRKDoConnect(buf);
        break;
    case kDSDisconnect:
        err = TRKDoDisconnect(buf);
        break;
    case kDSReset:
        err = TRKDoReset(buf);
        break;
    case kDSOverride:
        err = TRKDoOverride(buf);
        break;
    case kDSVersions:
        err = TRKDoVersions(buf);
        break;
    case kDSSupportMask:
        err = TRKDoSupportMask(buf);
        break;
    case kDSReadMemory:
        err = TRKDoReadMemory(buf);
        break;
    case kDSWriteMemory:
        err = TRKDoWriteMemory(buf);
        break;
    case kDSReadRegisters:
        err = TRKDoReadRegisters(buf);
        break;
    case kDSWriteRegisters:
        err = TRKDoWriteRegisters(buf);
        break;
    case kDSContinue:
        err = TRKDoContinue(buf);
        break;
    case kDSStep:
        err = TRKDoStep(buf);
        break;
    case kDSStop:
        err = TRKDoStop(buf);
        break;
    case kDSSetOption:
        err = TRKDoSetOption(buf);
        break;
    }

    return err;
}