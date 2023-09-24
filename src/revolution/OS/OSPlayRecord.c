#include <revolution/NAND.h>
#include <revolution/OS.h>

// Why?!? :(
#define MY_SEC_TO_TICKS(x) (x * (s64)OS_SEC_TO_TICKS(1))

typedef enum {
    PLAY_RECORD_STATE_STARTED,   //!< __OSStartPlayRecord
    PLAY_RECORD_STATE_OPEN,      //!< Open play record
    PLAY_RECORD_STATE_READ,      //!< Read play record
    PLAY_RECORD_STATE_SEEK,      //!< Seek play record
    PLAY_RECORD_STATE_SET_ALARM, //!< Set alarm callback
    PLAY_RECORD_STATE_WRITE,     //!< Save play record
    PLAY_RECORD_STATE_CLOSE,     //!< Close play record
    PLAY_RECORD_STATE_CLOSED,    //!< Play record was closed
    PLAY_RECORD_STATE_TIMEOUT,   //!< Play record could not be closed
    PLAY_RECORD_STATE_STOPPED    //!< __OSStopPlayRecord
} OSPlayRecordState;

typedef struct OSPlayRecord {
    u32 checksum;          // at 0x0
    wchar_t titleName[40]; // at 0x4
    char UNK_0x54[0x4];
    s64 startTime;   // at 0x58
    s64 stopTime;    // at 0x60
    char titleId[6]; // at 0x68
    char UNK_0x6E[0x80 - 0x6E];
} OSPlayRecord;

static OSPlayRecordState PlayRecordState = PLAY_RECORD_STATE_STOPPED;

static s64 PlayRecordLastCloseTime;
static s32 PlayRecordLastError;
static BOOL PlayRecordRetry;
static BOOL PlayRecordTerminated;
static BOOL PlayRecordTerminate;
static BOOL PlayRecordError;
static BOOL PlayRecordGet;

static OSPlayRecord PlayRecord ALIGN(32);
static NANDFileInfo FileInfo;
static NANDCommandBlock Block;
static OSAlarm PlayRecordAlarm;

static void PlayRecordCallback(s32 result, NANDCommandBlock* block);

static u32 RecordCheckSum(const OSPlayRecord* playRec) {
    int i;
    const u32* ptr = (const u32*)&playRec->titleName;
    u32 checksum = 0;

    for (i = 0; i < (sizeof(OSPlayRecord) / sizeof(u32)) - 1; i++) {
        checksum += *ptr++;
    }

    return checksum;
}

DECOMP_FORCEACTIVE(OSPlayRecord_c, PlayRecord);

static void PlayRecordAlarmCallback(OSAlarm* alarm, OSContext* ctx) {
#pragma unused(alarm)
#pragma unused(ctx)

    PlayRecordCallback(NAND_RESULT_OK, NULL);
}

static void PlayRecordCallback(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    s32 error = NAND_RESULT_OK;
    PlayRecordLastError = result;

    if (PlayRecordTerminate) {
        PlayRecordTerminated = TRUE;
        return;
    }

    if (!PlayRecordRetry) {
        switch (PlayRecordState) {
        case PLAY_RECORD_STATE_STARTED:
            PlayRecordState = PLAY_RECORD_STATE_OPEN;
            break;
        case PLAY_RECORD_STATE_OPEN:
            if (result == NAND_RESULT_MAXFD) {
                PlayRecordRetry = TRUE;
                OSCreateAlarm(&PlayRecordAlarm);
                OSSetAlarm(&PlayRecordAlarm, MY_SEC_TO_TICKS(1),
                           PlayRecordAlarmCallback);
                return;
            } else if (result == NAND_RESULT_OK) {
                if (!PlayRecordGet) {
                    PlayRecordState = PLAY_RECORD_STATE_READ;
                } else {
                    PlayRecordState = PLAY_RECORD_STATE_SET_ALARM;
                }
                break;
            } else {
                PlayRecordError = TRUE;
                PlayRecordState = PLAY_RECORD_STATE_CLOSED;
                return;
            }
        case PLAY_RECORD_STATE_READ:
            if (result == sizeof(OSPlayRecord)) {
                PlayRecordGet = TRUE;
                PlayRecordLastCloseTime = PlayRecord.stopTime;
                PlayRecordState = PLAY_RECORD_STATE_SEEK;
            } else {
                PlayRecordError = TRUE;
                PlayRecordState = PLAY_RECORD_STATE_CLOSE;
            }
            break;
        case PLAY_RECORD_STATE_SEEK:
            if (result == NAND_RESULT_OK) {
                PlayRecordState = PLAY_RECORD_STATE_SET_ALARM;
            } else {
                PlayRecordError = TRUE;
                PlayRecordState = PLAY_RECORD_STATE_CLOSE;
            }
            break;
        case PLAY_RECORD_STATE_SET_ALARM:
            PlayRecordState = PLAY_RECORD_STATE_WRITE;
            break;
        case PLAY_RECORD_STATE_WRITE:
            if (result == sizeof(OSPlayRecord)) {
                if (OSGetTime() - PlayRecordLastCloseTime >
                    MY_SEC_TO_TICKS(300)) {
                    PlayRecordState = PLAY_RECORD_STATE_CLOSE;
                } else {
                    PlayRecordState = PLAY_RECORD_STATE_SEEK;
                }
            } else {
                PlayRecordError = TRUE;
                PlayRecordState = PLAY_RECORD_STATE_CLOSE;
            }
            break;
        case PLAY_RECORD_STATE_CLOSE:
            if (PlayRecordError) {
                PlayRecordState = PLAY_RECORD_STATE_CLOSED;
                return;
            } else if (result == NAND_RESULT_OK) {
                PlayRecordLastCloseTime = PlayRecord.stopTime;
                PlayRecordState = PLAY_RECORD_STATE_OPEN;
            } else {
                PlayRecordState = PLAY_RECORD_STATE_CLOSED;
                PlayRecordError = TRUE;
                return;
            }
            break;
        default:
            PlayRecordState = PLAY_RECORD_STATE_CLOSED;
            PlayRecordError = TRUE;
            return;
        }
    }

    PlayRecordRetry = FALSE;

    switch (PlayRecordState) {
    case PLAY_RECORD_STATE_OPEN:
        error = NANDOpenAsync("/title/00000001/00000002/data/play_rec.dat",
                              &FileInfo, NAND_ACCESS_RW, PlayRecordCallback,
                              &Block);
        break;
    case PLAY_RECORD_STATE_READ:
        error = NANDReadAsync(&FileInfo, &PlayRecord, sizeof(OSPlayRecord),
                              PlayRecordCallback, &Block);
        break;
    case PLAY_RECORD_STATE_SEEK:
        error = NANDSeekAsync(&FileInfo, 0, NAND_SEEK_BEG, PlayRecordCallback,
                              &Block);
        break;
    case PLAY_RECORD_STATE_SET_ALARM:
        OSCreateAlarm(&PlayRecordAlarm);
        OSSetAlarm(&PlayRecordAlarm, MY_SEC_TO_TICKS(60),
                   PlayRecordAlarmCallback);
        break;
    case PLAY_RECORD_STATE_WRITE:
        PlayRecord.stopTime = OSGetTime();
        PlayRecord.checksum = RecordCheckSum(&PlayRecord);
        error = NANDWriteAsync(&FileInfo, &PlayRecord, sizeof(OSPlayRecord),
                               PlayRecordCallback, &Block);
        break;
    case PLAY_RECORD_STATE_CLOSE:
        error = NANDCloseAsync(&FileInfo, PlayRecordCallback, &Block);
        break;
    }

    if (error != NAND_RESULT_OK) {
        if (error == NAND_RESULT_BUSY) {
            OSCreateAlarm(&PlayRecordAlarm);
            OSSetAlarm(&PlayRecordAlarm, MY_SEC_TO_TICKS(1),
                       PlayRecordAlarmCallback);
            PlayRecordRetry = TRUE;
        } else {
            PlayRecordError = TRUE;

            switch (PlayRecordState) {
            case PLAY_RECORD_STATE_READ:
            case PLAY_RECORD_STATE_SEEK:
            case PLAY_RECORD_STATE_WRITE:
                PlayRecordState = PLAY_RECORD_STATE_CLOSE;
                error = NANDCloseAsync(&FileInfo, PlayRecordCallback, &Block);
                if (error == NAND_RESULT_BUSY) {
                    PlayRecordRetry = TRUE;
                    OSCreateAlarm(&PlayRecordAlarm);
                    OSSetAlarm(&PlayRecordAlarm, MY_SEC_TO_TICKS(1),
                               PlayRecordAlarmCallback);
                }
                break;
            default:
                PlayRecordState = PLAY_RECORD_STATE_CLOSED;
                break;
            }
        }
    }

    PlayRecordLastError = error;
}

void __OSStartPlayRecord(void) {
    if (NANDInit() == NAND_RESULT_OK) {
        PlayRecordTerminate = FALSE;
        PlayRecordGet = FALSE;
        PlayRecordState = PLAY_RECORD_STATE_STARTED;
        PlayRecordError = FALSE;
        PlayRecordRetry = FALSE;
        PlayRecordTerminated = FALSE;
        PlayRecordLastError = NAND_RESULT_OK;
        PlayRecordCallback(NAND_RESULT_OK, NULL);
    }
}

void __OSStopPlayRecord(void) {
    BOOL enabled;
    s64 start;

    enabled = OSDisableInterrupts();

    PlayRecordTerminate = TRUE;

    if (PlayRecordState == PLAY_RECORD_STATE_CLOSED ||
        PlayRecordState == PLAY_RECORD_STATE_STARTED ||
        PlayRecordState == PLAY_RECORD_STATE_STOPPED ||
        PlayRecordState == PLAY_RECORD_STATE_TIMEOUT) {
        OSRestoreInterrupts(enabled);
    } else if (PlayRecordState == PLAY_RECORD_STATE_SET_ALARM) {
        OSCancelAlarm(&PlayRecordAlarm);
        OSRestoreInterrupts(enabled);
        PlayRecord.stopTime = OSGetTime();
        PlayRecord.checksum = RecordCheckSum(&PlayRecord);
        NANDWrite(&FileInfo, &PlayRecord, sizeof(OSPlayRecord));
        NANDClose(&FileInfo);
    } else {
        if (PlayRecordRetry) {
            OSCancelAlarm(&PlayRecordAlarm);
            OSRestoreInterrupts(enabled);
        } else {
            OSRestoreInterrupts(enabled);
            start = OSGetTime();

            while (TRUE) {
                if (PlayRecordTerminated) {
                    break;
                }

                if (OSGetTime() - start > OS_MSEC_TO_TICKS(500)) {
                    PlayRecordState = PLAY_RECORD_STATE_TIMEOUT;
                    return;
                }
            }
        }

        switch (PlayRecordState) {
        case PLAY_RECORD_STATE_READ:
        case PLAY_RECORD_STATE_SEEK:
        case PLAY_RECORD_STATE_WRITE:
            NANDClose(&FileInfo);
            break;
        case PLAY_RECORD_STATE_OPEN:
            if (PlayRecordLastError == NAND_RESULT_OK && !PlayRecordRetry) {
                NANDClose(&FileInfo);
            }
            break;
        case PLAY_RECORD_STATE_CLOSE:
            if (PlayRecordRetry) {
                NANDClose(&FileInfo);
            }
            break;
        }
    }

    PlayRecordState = PLAY_RECORD_STATE_STOPPED;
}
