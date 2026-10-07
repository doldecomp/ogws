#include <nw4r/db.h>

#include <revolution/DVD.h>
#include <revolution/OS.h>

namespace nw4r {
namespace db {

#define MAP_WORK_SIZE 512
static u8 sMapBuf[MAP_WORK_SIZE] ALIGN(32) = {};
static s32 sMapBufOffset = -1;

static DVDFileInfo sFileInfo;
static u32 sFileLength = 0;

static MapFile* sMapFileList = NULL;

static void AppendMapFile_(MapFile* pMapFile) {
    NW4R_NULL_ASSERT(pMapFile);

    if (sMapFileList == NULL) {
        sMapFileList = pMapFile;
        return;
    }

    // Static linkage takes priority
    if (pMapFile->moduleInfo != NULL) {
        pMapFile->next = sMapFileList->next;
        sMapFileList->next = pMapFile;
    } else {
        pMapFile->next = sMapFileList;
        sMapFileList = pMapFile;
    }
}

static void RemoveMapFile_(MapFile* pMapFile) {
    NW4R_NULL_ASSERT(pMapFile);

    if (pMapFile == sMapFileList) {
        sMapFileList = sMapFileList->next;
        return;
    }

    MapFile* it = sMapFileList;

    for (; it != NULL; it = it->next) {
        if (it->next == pMapFile) {
            it->next = pMapFile->next;
            break;
        }
    }
}

MapFile* MapFile_RegistOnMem(void* pMapWork, u8* pMapData, u32 /* mapSize */,
                             const OSModuleInfo* pModuleInfo) {
    NW4R_NULL_ASSERT(pMapWork);
    NW4R_NULL_ASSERT(pMapData);

    MapFile* pMapFile = static_cast<MapFile*>(pMapWork);

    pMapFile->mapBuf = pMapData;
    pMapFile->moduleInfo = pModuleInfo;
    pMapFile->fileEntry = -1;
    pMapFile->next = NULL;

    AppendMapFile_(pMapFile);
    return pMapFile;
}

MapFile* MapFile_RegistOnDvd(void* pMapWork, const char* pPath,
                             const OSModuleInfo* pModuleInfo) {
    NW4R_NULL_ASSERT(pMapWork);
    NW4R_NULL_ASSERT(pPath);

    MapFile* pMapFile = static_cast<MapFile*>(pMapWork);

    pMapFile->mapBuf = NULL;
    pMapFile->moduleInfo = pModuleInfo;
    pMapFile->fileEntry = DVDConvertPathToEntrynum(pPath);
    pMapFile->next = NULL;

    NW4R_ASSERT(pMapFile->fileEntry >= 0);

    AppendMapFile_(pMapFile);
    return pMapFile;
}

void MapFile_Unregist(MapFile* pMapFile) {
    RemoveMapFile_(pMapFile);
}

void MapFile_UnregistAll() {
    sMapFileList = NULL;
}

bool MapFile_Exists() {
    return sMapFileList != NULL ? true : false;
}

typedef u8 (*GetCharFunc)(const u8* pBuffer);
static GetCharFunc GetCharPtr_ = NULL;

static u8 GetCharOnMem_(const u8* pBuffer) {
    return *pBuffer;
}

static u8 GetCharOnDvd_(const u8* pBuffer) {
    s32 address = reinterpret_cast<s32>(pBuffer) & ~0x80000000;
    s32 offset = address - sMapBufOffset;
    s32 len, size;

    if (address >= sFileLength) {
        return '\0';
    }

    if (sMapBufOffset < 0 || offset < 0 || offset >= MAP_WORK_SIZE) {
        size = MAP_WORK_SIZE;

        sMapBufOffset = ROUND_DOWN(address, 32);
        offset = address - sMapBufOffset;

        if (sMapBufOffset + MAP_WORK_SIZE >= sFileLength) {
            size = ROUND_UP(sFileLength - sMapBufOffset, 32);
        }

        BOOL enabled = OSEnableInterrupts();

        len = DVDReadAsyncPrio(&sFileInfo, sMapBuf, size, sMapBufOffset, NULL,
                               DVD_PRIO_MEDIUM);

        while (DVDGetCommandBlockStatus(&sFileInfo.block) != DVD_STATE_IDLE) {
            ;
        }

        OSRestoreInterrupts(enabled);

        if (len <= 0) {
            return '\0';
        }
    }

    return sMapBuf[offset];
}

static u8* SearchNextLine_(u8* pBuffer, s32 lines) {
    u8 ch;

    NW4R_NULL_ASSERT(LINE(363), GetCharPtr_);

    if (pBuffer == NULL) {
        return NULL;
    }

    while ((ch = GetCharPtr_(pBuffer)) != '\0') {
        if (ch == '\n' && --lines <= 0) {
            return pBuffer + 1;
        }

        pBuffer++;
    }

    return NULL;
}

static u8* SearchNextSection_(u8* pBuffer) {
    NW4R_NULL_ASSERT(LINE(399), GetCharPtr_);

    do {
        pBuffer = SearchNextLine_(pBuffer, 1);
        if (pBuffer == NULL) {
            return NULL;
        }
    } while (GetCharPtr_(pBuffer) != '.');

    return pBuffer;
}

static u8* SearchParam_(u8* pLineTop, u32 argNum, u8 delim) {
    BOOL inArg = FALSE;
    u8* pBuffer = pLineTop;

    NW4R_NULL_ASSERT(LINE(434), GetCharPtr_);

    if (pBuffer == NULL) {
        return NULL;
    }

    while (true) {
        u8 ch = GetCharPtr_(pBuffer);

        if (ch == '\0' || ch == '\n') {
            return NULL;
        }

        if (inArg) {
            if (ch == delim) {
                inArg = FALSE;
            }
        } else {
            if (ch != delim) {
                if (argNum-- <= 0) {
                    return pBuffer;
                } else {
                    inArg = TRUE;
                }
            }
        }

        pBuffer++;
    }
}

static u32 XStrToU32_(const u8* str) {
    u32 value = 0;

    NW4R_NULL_ASSERT(LINE(488), str);
    NW4R_NULL_ASSERT(LINE(489), GetCharPtr_);

    while (true) {
        u32 num;
        u8 ch = GetCharPtr_(str);

        if (ch >= '0' && ch <= '9') {
            num = ch - '0';
        } else if (ch >= 'a' && ch <= 'z') {
            num = ch - ('a' - 0xA);
        } else if (ch >= 'A' && ch <= 'Z') {
            num = ch - ('A' - 0xA);
        } else {
            return value;
        }

        if (value >= 0x10000000) {
            return 0;
        }

        value = num + (value << 4);
        str++;
    }
}

static u32 CopySymbol_(const u8* buf, u8* str, u32 maxlen, u8 delim) {
    u32 written = 0;

    NW4R_NULL_ASSERT(LINE(546), buf);
    NW4R_NULL_ASSERT(LINE(547), str);
    NW4R_NULL_ASSERT(LINE(548), GetCharPtr_);

    while (true) {
        u8 ch = GetCharPtr_(buf++);

        if (ch == delim || ch == '\0' || ch == '\n') {
            *str = '\0';
            return written;
        }

        *str++ = ch;
        written++;

        if (written >= maxlen - 1) {
            *str = '\0';
            return written;
        }
    }
}

static bool QuerySymbolToMapFile_(u8* pBuffer, const OSModuleInfo* pModuleInfo,
                                  u32 address, u8* strBuf, u32 strBufSize) {
    OSSectionInfo* pSectionInfo = NULL;
    u32 sectionNum;

    NW4R_NULL_ASSERT(LINE(604), strBuf);
    NW4R_ASSERT(LINE(605), strBufSize > 0);

    if (pModuleInfo != NULL) {
        pSectionInfo = (OSSectionInfo*)pModuleInfo->sectionInfoOffset;
        sectionNum = pModuleInfo->numSections;
    }

    while (true) {
        u32 offset = 0;

        // Skip link map
        pBuffer = SearchNextSection_(pBuffer);
        // Skip section header
        pBuffer = SearchNextLine_(pBuffer, 3);

        if (pSectionInfo != NULL) {
            offset = pSectionInfo->offset;

            if (address < offset || address >= offset + pSectionInfo->size) {
                goto _next_section;
            }
        }

        while (true) {
            u8* pParam;
            u32 startAddr;
            u32 size;

            pBuffer = SearchNextLine_(pBuffer, 1);
            if (pBuffer == NULL) {
                return false;
            }

            // 'Size' parameter
            pParam = SearchParam_(pBuffer, 1, ' ');
            if (pParam == NULL) {
                break;
            }

            size = XStrToU32_(pParam);

            // 'Virtual address' parameter
            pParam = SearchParam_(pBuffer, 2, ' ');
            if (pParam == NULL) {
                break;
            }

            startAddr = XStrToU32_(pParam);
            if (startAddr == 0) {
                continue;
            }

            startAddr += offset;
            if (address < startAddr || startAddr + size <= address) {
                continue;
            }

            // Symbol name
            pParam = SearchParam_(pBuffer, 5, ' ');
            if (pParam == NULL) {
                strBuf[0] = '\0';
                return true;
            }

            // Skip section header symbols
            if (GetCharPtr_(pBuffer) == '.') {
                continue;
            }

            CopySymbol_(pParam, strBuf, strBufSize, ' ');
            return true;
        }

    _next_section:
        if (pSectionInfo != NULL) {
            if (--sectionNum <= 0) {
                return false;
            }

            pSectionInfo++;
        }
    }
}

static bool QuerySymbolToSingleMapFile_(MapFile* pMapFile, u32 address,
                                        u8* strBuf, u32 strBufSize) {
    NW4R_NULL_ASSERT(LINE(725), pMapFile);
    NW4R_NULL_ASSERT(LINE(726), strBuf);

    if (pMapFile->mapBuf != NULL) {
        GetCharPtr_ = GetCharOnMem_;

        return QuerySymbolToMapFile_(pMapFile->mapBuf, pMapFile->moduleInfo,
                                     address, strBuf, strBufSize);
    }

    if (pMapFile->fileEntry >= 0) {
        u8* pBuffer = reinterpret_cast<u8*>(0x00000000 | 0x80000000);

        if (DVDFastOpen(pMapFile->fileEntry, &sFileInfo)) {
            sFileLength = sFileInfo.size;
            GetCharPtr_ = GetCharOnDvd_;

            bool success = QuerySymbolToMapFile_(pBuffer, pMapFile->moduleInfo,
                                                 address, strBuf, strBufSize);

            DVDClose(&sFileInfo);
            return success;
        }
    }

    strBuf[0] = '\0';
    return false;
}

bool MapFile_QuerySymbol(u32 address, u8* pBuffer, u32 maxlen) {
    MapFile* pMapFile = sMapFileList;

    while (pMapFile != NULL) {
        if (QuerySymbolToSingleMapFile_(pMapFile, address, pBuffer, maxlen)) {
            return true;
        }

        pMapFile = pMapFile->next;
    }

    return false;
}

} // namespace db
} // namespace nw4r
