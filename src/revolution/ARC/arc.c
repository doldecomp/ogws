#include <revolution/ARC.h>
#include <revolution/OS.h>

#include <ctype.h>

#undef NULL
#define NULL ((void*)0)

#define TRUE 1
#define FALSE 0

#undef ADD_PTR
#define ADD_PTR(ptr, offset) ((void*)((u32)ptr + offset))

#undef IS_DIR
#define IS_DIR(fst, entrynum)                                                  \
    ((fst[entrynum].isDirAndStringOff & 0xFF000000) == 0 ? FALSE : TRUE)

#define ARC_FILE_MAGIC 0x55AA382D

typedef struct {
    unsigned int magic; // at 0x0
    int fstStart;       // at 0x4
    int fstSize;        // at 0x8
    int fileStart;      // at 0xC
    int reserve[4];     // at 0x10
} ARCHeader;

typedef struct FSTEntry {
    unsigned int isDirAndStringOff; // at 0x0
    unsigned int parentOrPosition;  // at 0x4
    unsigned int nextEntryOrLength; // at 0x8
} FSTEntry;

BOOL ARCInitHandle(void* arcStart, ARCHandle* handle) {
    FSTEntry* FSTEntries;
    ARCHeader* arcHeader = (ARCHeader*)arcStart;

    if (arcHeader->magic != ARC_FILE_MAGIC) {
#line 74
        OS_ERROR("ARCInitHandle: bad archive format");
    }

    handle->archiveStartAddr = arcStart;

    FSTEntries = (FSTEntry*)ADD_PTR(arcStart, arcHeader->fstStart);
    handle->FSTStart = FSTEntries;
    handle->fileStart = ADD_PTR(arcStart, arcHeader->fileStart);

    handle->entryNum = FSTEntries[0].nextEntryOrLength;
    handle->FSTStringStart =
        (char*)ADD_PTR(FSTEntries, handle->entryNum * sizeof(FSTEntry));
    handle->FSTLength = arcHeader->fstSize;
    handle->currDir = 0;

    return TRUE;
}

BOOL ARCOpen(ARCHandle* handle, const char* fileName, ARCFileInfo* af) {
    s32 entry;
    char currentDir[128];
    FSTEntry* FSTEntries;

    FSTEntries = (FSTEntry*)handle->FSTStart;
    entry = ARCConvertPathToEntrynum(handle, fileName);

    if (entry < 0) {
        ARCGetCurrentDir(handle, currentDir, sizeof(currentDir));
        OSReport("Warning: ARCOpen(): file '%s' was not found under %s in the "
                 "archive.\n",
                 fileName, currentDir);
        return FALSE;
    }

    if (entry < 0 || IS_DIR(FSTEntries, entry)) {
        return FALSE;
    }

    af->handle = handle;
    af->startOffset = FSTEntries[entry].parentOrPosition;
    af->length = FSTEntries[entry].nextEntryOrLength;

    return TRUE;
}

BOOL ARCFastOpen(ARCHandle* handle, s32 entrynum, ARCFileInfo* af) {
    FSTEntry* FSTEntries = (FSTEntry*)handle->FSTStart;

    if (!(entrynum >= 0 && entrynum < handle->entryNum) ||
        IS_DIR(FSTEntries, entrynum)) {
        return FALSE;
    }

    af->handle = handle;
    af->startOffset = FSTEntries[entrynum].parentOrPosition;
    af->length = FSTEntries[entrynum].nextEntryOrLength;

    return TRUE;
}

// Subroutine for ARCConvertPathToEntrynum
static BOOL isSame(const char* path, const char* string) {
    while (*string != '\0') {
        if (tolower(*path++) != tolower(*string++)) {
            return FALSE;
        }
    }

    // '/' if we found the directory, '\0' if we found the file (or directory
    // with no suffix) The caller will delineate between file and directory by
    // checking the FST entry
    if (*path == '/' || *path == '\0') {
        return TRUE;
    }

    return FALSE;
}

s32 ARCConvertPathToEntrynum(ARCHandle* handle, const char* pathPtr) {
    const char* ptr;
    const char* stringPtr;
    BOOL isDir;
    s32 length;
    u32 dirLookAt;
    u32 i;
    const char* origPathPtr = pathPtr; // Unused
    FSTEntry* FSTEntries;

    dirLookAt = handle->currDir;
    FSTEntries = (FSTEntry*)handle->FSTStart;

    while (TRUE) {
        if (pathPtr[0] == '\0') {
            // We found the directory (always a directory)
            return dirLookAt;
        } else if (pathPtr[0] == '/') {
            // Restart at root
            dirLookAt = 0;
            ++pathPtr;
            continue;
        } else if (pathPtr[0] == '.') {
            if (pathPtr[1] == '.') {
                if (pathPtr[2] == '/') {
                    // Restart at parent directory
                    dirLookAt = FSTEntries[dirLookAt].parentOrPosition;
                    pathPtr += 3;
                    continue;
                } else if (pathPtr[2] == '\0') {
                    // We found the parent directory (always a directory)
                    return FSTEntries[dirLookAt].parentOrPosition;
                }
            } else if (pathPtr[1] == '/') {
                // Restart at current directory
                pathPtr += 2;
                continue;
            } else if (pathPtr[1] == '\0') {
                // We found the current directory (always a directory)
                return dirLookAt;
            }
        }

        // Prep a substring formed by [pathPtr, ptr)
        // We need this to compute the length so we can keep iterating later
        for (ptr = pathPtr; *ptr != '\0' && *ptr != '/'; ++ptr) {
        }

        // We need to iterate over all the items in the directory and see if the
        // substring matches. Example: first we search [a]/b/c, then a/[b]/c,
        // and finally find the leaf a/b/[c]. If ptr is '/', we need to search
        // the next layer down and restart. If ptr is '\0', we need to find the
        // file/subdirectory in that directory.

        // NOTE: isDir == TRUE guarantees it's a directory but it can still be a
        // directory if FALSE
        isDir = *ptr == '\0' ? FALSE : TRUE;
        length = ptr - pathPtr;
        ptr = pathPtr; // Why?? There's no writes to pathPtr in the loop

        for (i = dirLookAt + 1; i < FSTEntries[dirLookAt].nextEntryOrLength;
             i = IS_DIR(FSTEntries, i) ? FSTEntries[i].nextEntryOrLength
                                       : i + 1) {
            // We need a nested loop with no condition so that we can handle an
            // edgecase. If the directory includes itself, we need to move onto
            // the next FST entry. We can't do that in one loop without
            // triggering the incrementer, so use a nested loop.
            while (TRUE) {
                if (!IS_DIR(FSTEntries, i) && isDir == TRUE) {
                    break;
                }

                stringPtr = handle->FSTStringStart +
                            (FSTEntries[i].isDirAndStringOff & 0xFFFFFF);
                // The directory includes itself, skip it
                if (stringPtr[0] == '.' && stringPtr[1] == '\0') {
                    ++i;
                    continue;
                }

                if (isSame(ptr, stringPtr) == TRUE) {
                    // NOTE: This goto is to delineate breaking vs fallthrough
                    // This emulates Python's loop/else pattern
                    goto found;
                }

                break;
            }
        }

        // Natural fallthrough: We searched through the whole directory and
        // didn't find it. Therefore, this path does not exist under these
        // search conditions.
        return -1;

    found:
        // Unnatural fallthrough: If it's a leaf, we found it
        if (isDir == FALSE) {
            return i;
        }

        // Otherwise, we restart in the subdirectory we found
        dirLookAt = i;
        pathPtr += length + 1;
    }

    return -1;
}

BOOL ARCEntrynumIsDir(const ARCHandle* handle, s32 entrynum) {
    FSTEntry* FSTEntries = (FSTEntry*)handle->FSTStart;
    return IS_DIR(FSTEntries, entrynum);
}

// Subroutine for ARCConvertEntrynumToPath
static u32 myStrncpy(char* dest, char* src, u32 maxlen) {
    u32 i = maxlen;
    for (; i != 0 && *src != '\0'; --i) {
        *dest++ = *src++;
    }
    return maxlen - i;
}

// Subroutine for ARCConvertEntrynumToPath
static u32 entryToPath(ARCHandle* handle, u32 entry, char* path, u32 maxlen) {
    char* name;
    u32 loc;
    FSTEntry* FSTEntries = (FSTEntry*)handle->FSTStart;

    if (entry == 0) {
        return 0;
    }

    name = handle->FSTStringStart +
           (FSTEntries[entry].isDirAndStringOff & 0xFFFFFF);
    loc = entryToPath(handle, FSTEntries[entry].parentOrPosition, path, maxlen);
    if (loc == maxlen) {
        return loc;
    }

    path[loc++] = '/';
    loc += myStrncpy(path + loc, name, maxlen - loc);
    return loc;
}

static BOOL ARCConvertEntrynumToPath(ARCHandle* handle, s32 entrynum,
                                     char* path, u32 maxlen) {
    u32 loc;
    FSTEntry* FSTEntries = (FSTEntry*)handle->FSTStart;

    loc = entryToPath(handle, entrynum, path, maxlen);
    if (loc == maxlen) {
        path[maxlen - 1] = '\0';
        return FALSE;
    }

    if (IS_DIR(FSTEntries, entrynum)) {
        if (loc == maxlen - 1) {
            path[loc] = '\0';
            return FALSE;
        }

        path[loc++] = '/';
    }

    path[loc] = '\0';
    return TRUE;
}

BOOL ARCGetCurrentDir(ARCHandle* handle, char* path, u32 maxlen) {
    return ARCConvertEntrynumToPath(handle, handle->currDir, path, maxlen);
}

void* ARCGetStartAddrInMem(ARCFileInfo* af) {
    ARCHandle* handle = af->handle;
    return ADD_PTR(handle->archiveStartAddr, af->startOffset);
}

u32 ARCGetStartOffset(ARCFileInfo* af) {
    return af->startOffset;
}

u32 ARCGetLength(ARCFileInfo* af) {
    return af->length;
}

BOOL ARCClose(ARCFileInfo* af) {
#pragma unused(af)

    return TRUE;
}

BOOL ARCChangeDir(ARCHandle* handle, const char* dirName) {
    s32 entry;
    FSTEntry* FSTEntries;

    entry = ARCConvertPathToEntrynum(handle, dirName);
    FSTEntries = (FSTEntry*)handle->FSTStart;

    if (entry < 0 || !IS_DIR(FSTEntries, entry)) {
        return FALSE;
    }

    handle->currDir = entry;
    return TRUE;
}

BOOL ARCOpenDir(ARCHandle* handle, const char* dirName, ARCDir* dir) {
    s32 entry;
    FSTEntry* FSTEntries;

    entry = ARCConvertPathToEntrynum(handle, dirName);
    FSTEntries = (FSTEntry*)handle->FSTStart;

    if (entry < 0 || !IS_DIR(FSTEntries, entry)) {
        return FALSE;
    }

    dir->handle = handle;
    dir->entryNum = entry;
    dir->location = entry + 1;
    dir->next = FSTEntries[entry].nextEntryOrLength;
    return TRUE;
}

BOOL ARCReadDir(ARCDir* dir, ARCDirEntry* dirent) {
    u32 loc;
    FSTEntry* FSTEntries;
    ARCHandle* handle = dir->handle;

    FSTEntries = (FSTEntry*)handle->FSTStart;
    loc = dir->location;

    while (TRUE) {
        if (loc <= dir->entryNum || dir->next <= loc) {
            return FALSE;
        }

        dirent->handle = handle;
        dirent->entryNum = loc;
        dirent->isDir = IS_DIR(FSTEntries, loc);
        dirent->name = handle->FSTStringStart +
                       (FSTEntries[loc].isDirAndStringOff & 0xFFFFFF);
        if (dirent->name[0] == '.' && dirent->name[1] == '\0') {
            ++loc;
            continue;
        }

        break;
    }

    dir->location =
        IS_DIR(FSTEntries, loc) ? FSTEntries[loc].nextEntryOrLength : loc + 1;

    return TRUE;
}

BOOL ARCCloseDir(ARCDir* dir) {
#pragma unused(dir)

    return TRUE;
}
