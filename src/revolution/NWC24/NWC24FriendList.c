#include <revolution/NWC24.h>

#define FRIEND_LIST_MAGIC 'WcFl'
#define FRIEND_LIST_VERSION 2

static const char* FLFilePath = "/shared2/wc24/nwc24fl.bin";

static s32 GetCachedFLHeader(NWC24FLHeader** header);

s32 NWC24iOpenFriendList(void) {
    NWC24FLHeader* header = (NWC24FLHeader*)NWC24WorkP->flHeaderWork;
    Mail_memset(header, 0, sizeof(NWC24FLHeader));
    return GetCachedFLHeader(&header);
}

static s32 GetCachedFLHeader(NWC24FLHeader** header) {
    NWC24File file;
    s32 result;
    s32 read;
    s32 close;

    *header = (NWC24FLHeader*)NWC24WorkP->flHeaderWork;

    if ((*header)->magic != FRIEND_LIST_MAGIC) {
        result = NWC24FOpen(&file, FLFilePath, NWC24_OPEN_READ);
        if (result != NWC24_OK) {
            return result;
        }

        NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
        read = NWC24FRead(*header, sizeof(NWC24FLHeader), &file);
        close = NWC24FClose(&file);

        if (read != NWC24_OK) {
            result = read;
        } else {
            result = close;
        }

        if (result != NWC24_OK) {
            return result;
        }

        if ((*header)->magic != FRIEND_LIST_MAGIC) {
            return NWC24_ERR_BROKEN;
        }

        if ((*header)->version != FRIEND_LIST_VERSION) {
            return NWC24_ERR_VER_MISMATCH;
        }
    }

    return NWC24_OK;
}
