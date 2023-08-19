#include <RVLFaceLib/RVLFaceLibInternal.h>

void RFLSetIconDrawDoneCallback(RFLIconDrawDoneCallback callback) {
    RFLiGetManager()->iconDrawCb = callback;
}