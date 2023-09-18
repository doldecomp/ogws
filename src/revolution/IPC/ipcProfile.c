#include <revolution/IPC.h>

#define REQUEST_MAX 32

static s32 IpcNumUnIssuedReqs;
static s32 IpcNumPendingReqs;

static IPCRequestEx* IpcReqPtrArray[REQUEST_MAX];
static s32 IpcFdArray[REQUEST_MAX];

static void AddReqInfo(IPCRequestEx* req, s32 fd);
static void DelReqInfo(IPCRequestEx* req, s32 fd);

CW_FORCE_ORDER(ipcProfile_c, IpcFdArray);

void IPCiProfInit(void) {
    int i;

    IpcNumPendingReqs = 0;
    IpcNumUnIssuedReqs = 0;

    for (i = 0; i < REQUEST_MAX; i++) {
        IpcReqPtrArray[i] = NULL;
        IpcFdArray[i] = -1;
    }
}

void IPCiProfQueueReq(IPCRequestEx* req, s32 fd) {
    IpcNumPendingReqs++;
    IpcNumUnIssuedReqs++;
    AddReqInfo(req, fd);
}

void IPCiProfAck(void) { IpcNumUnIssuedReqs--; }

void IPCiProfReply(IPCRequestEx* req, s32 fd) {
    IpcNumPendingReqs--;
    DelReqInfo(req, fd);
}

static void AddReqInfo(IPCRequestEx* req, s32 fd) {
    u32 i;

    for (i = 0; i < REQUEST_MAX; i++) {
        if (IpcReqPtrArray[i] == NULL && IpcFdArray[i] == -1) {
            IpcReqPtrArray[i] = req;
            IpcFdArray[i] = fd;
            return;
        }
    }
}

static void DelReqInfo(IPCRequestEx* req, s32 fd) {
    u32 i;

    for (i = 0; i < REQUEST_MAX; i++) {
        if (req == IpcReqPtrArray[i] && IpcFdArray[i] == fd) {
            IpcReqPtrArray[i] = NULL;
            IpcFdArray[i] = -1;
            return;
        }
    }
}
