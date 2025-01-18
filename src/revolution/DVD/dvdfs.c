/**
 * Based on ARC decompilation by riidefi
 */

#include <ctype.h>
#include <revolution/DVD.h>
#include <revolution/OS.h>

typedef struct DVDNode {
    union {
        struct {
            u32 is_folder : 8;
            u32 name : 24;
        };
        u32 packed_type_name;
    }; // at 0x0

    union {
        struct {
            u32 offset;
            u32 size;
        };

        struct {
            u32 parent;
            u32 sibling_next;
        } folder;
    }; // at 0x4
} DVDNode;

#define DVDNodeIsFolder(node) (((node).packed_type_name & 0xFF000000))
#define DVDNodeGetName(node) ((node).packed_type_name & 0x00FFFFFF)

static OSBootInfo* BootInfo;
static const DVDNode* FstStart;
static char* FstStringStart;
static u32 MaxEntryNum;

OSThreadQueue __DVDThreadQueue;
BOOL __DVDLongFileNameFlag = TRUE;

static s32 currentDirectory;

static void cbForReadAsync(s32 result, DVDCommandBlock* block);
static void cbForReadSync(s32 result, DVDCommandBlock* block);

void __DVDFSInit(void) {
    BootInfo = (OSBootInfo*)OSPhysicalToCached(OS_PHYS_BOOT_INFO);
    FstStart = (const DVDNode*)BootInfo->fstStart;

    if (FstStart != NULL) {
        // Size of FST root
        MaxEntryNum = FstStart->size;
        // String table is placed after FST nodes
        FstStringStart = (char*)&FstStart[MaxEntryNum];
    }
}

static BOOL isSame(const char* lhs, const char* rhs) {
    while (*rhs != '\0') {
        if (tolower(*lhs++) != tolower(*rhs++)) {
            return FALSE;
        }
    }

    if (*lhs == '/' || *lhs == '\0') {
        return TRUE;
    }

    return FALSE;
}

s32 DVDConvertPathToEntrynum(const char* path) {
    const DVDNode* new_var;
    const char* name_end;
    u32 it;
    u32 anchor;
    const char* item_name;
    BOOL name_delimited_by_slash;
    s32 name_length;
    const char* backup_path;
    const char* extension_start;
    BOOL illegal_format;
    BOOL has_extension;

    backup_path = path;
    it = currentDirectory;

    while (TRUE) {
        // End of string -> return what we have
        if (*path == '\0') {
            return it;
        }

        // Ignore initial slash: /Path/File vs Path/File
        if (*path == '/') {
            it = 0;
            path++;
            continue;
        }

        // Handle special cases:
        // -../-, -.., -./-, -.
        if (path[0] == '.') {
            if (path[1] == '.') {
                // Seek to parent ../
                if (path[2] == '/') {
                    it = FstStart[it].folder.parent;
                    path += 3;
                    continue;
                }
                // Return parent folder immediately
                if (path[2] == '\0') {
                    return FstStart[it].folder.parent;
                }
                // Malformed: fall through, causing infinite loop
                goto check_format;
            }

            // "." directory does nothing
            if (path[1] == '/') {
                path += 2;
                continue;
            }

            // Ignore trailing dot
            if (path[1] == '\0') {
                return it;
            }
        }

    check_format:
        if (!__DVDLongFileNameFlag) {
            has_extension = FALSE;
            illegal_format = FALSE;

            name_end = path;
            while (*name_end != '\0' && *name_end != '/') {
                if (*name_end == '.') {
                    // 8.3 format limits file name to 8 characters.
                    if (name_end - path > 8 || has_extension == TRUE) {
                        illegal_format = TRUE;
                        goto validate_format;
                    } else {
                        has_extension = TRUE;
                        extension_start = name_end + 1;
                    }
                }
                // 8.3 format does not allow spaces in file name.
                else if (*name_end == ' ') {
                    illegal_format = TRUE;
                }

                name_end++;
            }

        validate_format:
            if (has_extension == TRUE && name_end - extension_start > 3) {
                illegal_format = TRUE;
            }

            // clang-format off
#line 443
            OS_ASSERT(!illegal_format, "DVDConvertEntrynumToPath(possibly DVDOpen or DVDChangeDir or DVDOpenDir): specified directory or file (%s) doesn't match standard 8.3 format. This is a temporary restriction and will be removed soon\n", backup_path);
            // clang-format on
        } else {
            // We've ensured the directory is not special.
            // Isolate the name of the current item in the path string.
            name_end = path;
            while (*name_end != '\0' && *name_end != '/') {
                name_end++;
            }
        }

        // If the name was delimited by a '/' rather than truncated.
        // This must be expressed as a ternary, and an enum cannot be used..
        name_delimited_by_slash = (*name_end == '\0') ? 0 : 1;
        name_length = name_end - path;

        // Traverse all children of the parent.
        anchor = it + 1;
        new_var = FstStart;
        while (anchor < new_var[it].folder.sibling_next) {
            while (TRUE) {
                if (DVDNodeIsFolder(FstStart[anchor]) ||
                    name_delimited_by_slash != TRUE) {
                    item_name =
                        FstStringStart + DVDNodeGetName(FstStart[anchor]);

                    // Advance to the next item in the path
                    if (isSame(path, item_name) == TRUE) {
                        goto descend;
                    }
                }

                if (DVDNodeIsFolder(FstStart[anchor])) {
                    anchor = FstStart[anchor].folder.sibling_next;
                    break;
                }

                anchor++;
                break;
            }
        }

        return -1;

    descend:
        // If the path was truncated, there is nowhere else to go
        // These basic blocks have to go here right at the end, accessed via a
        // goto. An odd choice.
        if (!name_delimited_by_slash) {
            return anchor;
        }

        it = anchor;
        path += name_length + 1;
    }
}

BOOL DVDFastOpen(s32 entrynum, DVDFileInfo* info) {
    if (entrynum < 0 || entrynum >= MaxEntryNum ||
        DVDNodeIsFolder(FstStart[entrynum])) {
        return FALSE;
    }

    info->offset = FstStart[entrynum].offset >> __DVDLayoutFormat;
    info->size = FstStart[entrynum].size;
    info->callback = NULL;
    info->block.state = DVD_STATE_IDLE;

    return TRUE;
}

BOOL DVDOpen(const char* path, DVDFileInfo* info) {
    s32 entrynum = DVDConvertPathToEntrynum(path);

    if (entrynum < 0) {
        char dir[128];
        DVDGetCurrentDir(dir, sizeof(dir));

        OSReport("Warning: DVDOpen(): file '%s' was not found under %s.\n",
                 path, dir);

        return FALSE;
    }

    if (DVDNodeIsFolder(FstStart[entrynum])) {
        return FALSE;
    }

    info->offset = FstStart[entrynum].offset >> __DVDLayoutFormat;
    info->size = FstStart[entrynum].size;
    info->callback = NULL;
    info->block.state = DVD_STATE_IDLE;

    return TRUE;
}

BOOL DVDClose(DVDFileInfo* info) {
    DVDCancel(&info->block);
    return TRUE;
}

static u32 myStrncpy(char* dst, const char* src, u32 maxlen) {
    u32 i;
    for (i = maxlen; i != 0 && *src != '\0'; --i) {
        *dst++ = *src++;
    }

    return maxlen - i;
}

static u32 entryToPath(s32 entrynum, char* string, u32 maxlen) {
    const char* name;
    u32 written;

    if (entrynum == 0) {
        return 0;
    }

    name = FstStringStart + FstStart[entrynum].name;

    written = entryToPath(FstStart[entrynum].folder.parent, string, maxlen);
    if (written == maxlen) {
        return written;
    }

    string[written++] = '/';
    return written + myStrncpy(string + written, name, maxlen - written);
}

static BOOL DVDConvertEntrynumToPath(s32 entrynum, char* string, u32 maxlen) {
    u32 written = entryToPath(entrynum, string, maxlen);

    if (written == maxlen) {
        string[maxlen - 1] = '\0';
        return FALSE;
    }

    if (DVDNodeIsFolder(FstStart[entrynum])) {
        if (written == maxlen - 1) {
            string[written] = '\0';
            return FALSE;
        }

        string[written++] = '/';
    }

    string[written] = '\0';
    return TRUE;
}

BOOL DVDGetCurrentDir(char* buffer, u32 maxlen) {
    return DVDConvertEntrynumToPath(currentDirectory, buffer, maxlen);
}

BOOL DVDReadAsyncPrio(DVDFileInfo* info, void* dst, s32 size, s32 offset,
                      DVDAsyncCallback callback, s32 prio) {
    // clang-format off
#line 823
    OS_ASSERT(offset >= 0 && offset <= info->size, "DVDReadAsync(): specified area is out of the file  ");
    // clang-format on

    // clang-format off
#line 829
    OS_ASSERT(offset + size >= 0 && offset + size < info->size + 32, "DVDReadAsync(): specified area is out of the file  ");
    // clang-format on

    info->callback = callback;

    DVDReadAbsAsyncPrio(&info->block, dst, size, info->offset + (offset >> 2),
                        cbForReadAsync, prio);

    return TRUE;
}

static void cbForReadAsync(s32 result, DVDCommandBlock* block) {
    DVDFileInfo* info = (DVDFileInfo*)block;

    if (info->callback != NULL) {
        info->callback(result, info);
    }
}

s32 DVDReadPrio(DVDFileInfo* info, void* dst, s32 size, s32 offset, s32 prio) {
    DVDCommandBlock* block;
    BOOL enabled;
    s32 ret;

    // clang-format off
#line 893
    OS_ASSERT(offset >= 0 && offset <= info->size, "DVDRead(): specified area is out of the file  ");
    // clang-format on

    // clang-format off
#line 899
    OS_ASSERT(offset + size >= 0 && offset + size < info->size + 32, "DVDRead(): specified area is out of the file  ");
    // clang-format on

    block = &info->block;
    if (!DVDReadAbsAsyncPrio(block, dst, size, info->offset + (offset >> 2),
                             cbForReadSync, prio)) {
        return DVD_RESULT_FATAL;
    }

    enabled = OSDisableInterrupts();

    while (TRUE) {
        s32 state = block->state;

        if (state == DVD_STATE_IDLE) {
            ret = block->transferTotal;
            break;
        } else if (state == DVD_STATE_FATAL) {
            ret = DVD_RESULT_FATAL;
            break;
        } else if (state == DVD_STATE_CANCELED) {
            ret = DVD_RESULT_CANCELED;
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return ret;
}

static void cbForReadSync(s32 result, DVDCommandBlock* block) {
#pragma unused(result)
#pragma unused(block)

    OSWakeupThread(&__DVDThreadQueue);
}
