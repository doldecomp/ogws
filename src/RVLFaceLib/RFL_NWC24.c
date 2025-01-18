#include <RVLFaceLib/RVLFaceLibInternal.h>
#include <revolution/NWC24.h>

RFLErrcode RFLCommitNWC24Msg(NWC24MsgObj* msg, u16 index) {
    RFLiCharData data;
    RFLErrcode rflerr;
    NWC24Err wc24err;

    if (!RFLAvailable()) {
        return RFLErrcode_NotAvailable;
    }

    rflerr = RFLiGetCharRawData(&data, index);

    switch (rflerr) {
    case RFLErrcode_Success:
        if (RFLiGetIsolation()) {
            data.localonly = TRUE;
        }

        data.favorite = FALSE;

        wc24err = NWC24SetMsgFaceData(msg, (RFLCharData*)&data);
        if (wc24err != NWC24_OK) {
            RFLiGetManager()->lastErrCode = RFLErrcode_NWC24Fail;
            RFLiGetManager()->lastReason = wc24err;
            return RFLErrcode_NWC24Fail;
        }

        wc24err = NWC24CommitMsg(msg);
        if (wc24err != NWC24_OK) {
            RFLiGetManager()->lastErrCode = RFLErrcode_NWC24Fail;
            RFLiGetManager()->lastReason = wc24err;
            return RFLErrcode_NWC24Fail;
        }

        return RFLErrcode_Success;
    default:
        return rflerr;
    }
}
