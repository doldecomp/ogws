#include <RVLFaceLib/RVLFaceLibInternal.h>

void RFLSetIconDrawDoneCallback(RFLCallback callback) {
    RFLiGetManager()->iconDrawCb = callback;
}