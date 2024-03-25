#include <ctype.h>
#include <revolution/ARC.h>
#include <revolution/OS/OSError.h>

/**
 * Modified from decompilation by riidefi in WiiCore
 */

#define ARC_FILE_MAGIC 0x55AA382D

#define ARCNodeIsFolder(node) ((node).packed_type_name & 0xFF000000)
#define ARCNodeGetName(node) ((node).packed_type_name & 0x00FFFFFF)

static u32 entryToPath(ARCHandle* handle, u32 entrynum, char* string,
                       u32 maxlen);

static BOOL isSame(const char* lhs, const char* rhs) {
    while (rhs[0] != '\0') {
        if (tolower(*lhs++) != tolower(*rhs++))
            return FALSE;
    }

    if (lhs[0] == '/' || lhs[0] == '\0') {
        return TRUE;
    }

    return FALSE;
}

static u32 myStrncpy(char* dst, char* src, u32 maxlen) {
    u32 i;
    for (i = maxlen; i != 0 && src[0] != '\0'; --i) {
        *dst++ = *src++;
    }

    return maxlen - i;
}

static BOOL ARCConvertEntrynumToPath(ARCHandle* handle, s32 entrynum,
                                     char* string, u32 maxlen) {
    ARCNode* nodes = handle->nodes;
    u32 written = entryToPath(handle, entrynum, string, maxlen);

    if (written == maxlen) {
        string[maxlen - 1] = '\0';
        return FALSE;
    }

    if (ARCNodeIsFolder(nodes[entrynum])) {
        if (written == maxlen - 1) {
            string[written] = '\0';
            return FALSE;
        }

        string[written++] = '/';
    }

    string[written] = '\0';
    return TRUE;
}

BOOL ARCGetCurrentDir(ARCHandle* handle, char* string, u32 maxlen) {
    return ARCConvertEntrynumToPath(handle, handle->entrynum, string, maxlen);
}

BOOL ARCInitHandle(void* bin, ARCHandle* handle) {
    ARCNode* nodes;
    ARCHeader* header = (ARCHeader*)bin;

    // clang-format off
#line 74
    OS_ASSERT(header->magic == ARC_FILE_MAGIC, "ARCInitHandle: bad archive format");
    // clang-format on

    handle->header = header;

    nodes = (ARCNode*)((u8*)header + header->nodes.offset);
    handle->nodes = nodes;

    handle->file = ((u8*)header + header->files.offset);
    // The right bound of the root node is the number of nodes
    handle->count = nodes[0].folder.sibling_next;
    // Strings exist directly after the last node.
    handle->strings = (const char*)(nodes + handle->count);
    handle->fstSize = header->nodes.size;
    handle->entrynum = 0;

    return TRUE;
}

BOOL ARCOpen(ARCHandle* handle, const char* path, ARCFileInfo* info) {
    ARCNode* nodes = handle->nodes;
    s32 entrynum = ARCConvertPathToEntrynum(handle, path);

    if (entrynum < 0) {
        char dir[128];
        ARCGetCurrentDir(handle, dir, sizeof(dir));

        OSReport("Warning: ARCOpen(): file '%s' was not found under %s in the "
                 "archive.\n",
                 path, dir);

        return FALSE;
    }

    if (entrynum < 0 || ARCNodeIsFolder(nodes[entrynum])) {
        return FALSE;
    }

    info->handle = handle;
    info->offset = nodes[entrynum].file.offset;
    info->size = nodes[entrynum].file.size;
    return TRUE;
}

BOOL ARCFastOpen(ARCHandle* handle, s32 entrynum, ARCFileInfo* info) {
    ARCNode* nodes = handle->nodes;

    if (entrynum < 0 || entrynum >= handle->count ||
        ARCNodeIsFolder(nodes[entrynum])) {
        return FALSE;
    }

    info->handle = handle;
    info->offset = nodes[entrynum].file.offset;
    info->size = nodes[entrynum].file.size;

    return TRUE;
}

s32 ARCConvertPathToEntrynum(ARCHandle* handle, const char* path) {
    const char* name_end;
    BOOL name_delimited_by_slash;
    s32 name_length;
    u32 anchor;
    u32 it = handle->entrynum;
    ARCNode* nodes = handle->nodes;

    while (TRUE) {
        // End of string -> return what we have
        if (path[0] == '\0') {
            return it;
        }

        // Ignore initial slash: /Path/File vs Path/File
        if (path[0] == '/') {
            it = 0;
            ++path;
            continue;
        }

        // Handle special cases:
        // -../-, -.., -./-, -.
        if (path[0] == '.') {
            if (path[1] == '.') {
                // Seek to parent ../
                if (path[2] == '/') {
                    it = nodes[it].folder.parent;
                    path += 3;
                    continue;
                }
                // Return parent folder immediately
                if (path[2] == '\0') {
                    return nodes[it].folder.parent;
                }
                // Malformed: fall through, causing infinite loop
                goto compare;
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

    compare:
        // We've ensured the directory is not special.
        // Isolate the name of the current item in the path string.
        name_end = path;
        while (name_end[0] != '\0' && name_end[0] != '/') {
            ++name_end;
        }

        // If the name was delimited by a '/' rather than truncated.
        // This must be expressed as a ternary, and an enum cannot be used..
        name_delimited_by_slash = (name_end[0] != '\0') ? 1 : 0;
        name_length = name_end - path;

        // Traverse all children of the parent.
        anchor = it;
        ++it;
        while (it < nodes[anchor].folder.sibling_next) {
            while (TRUE) {
                if (ARCNodeIsFolder(nodes[it]) ||
                    name_delimited_by_slash != TRUE) {
                    char* name_of_it =
                        ((char*)handle->strings) + ARCNodeGetName(nodes[it]);

                    // Skip empty directories
                    if (name_of_it[0] == '.' && name_of_it[1] == '\0') {
                        ++it;
                        continue;
                    }

                    // Advance to the next item in the path
                    if (isSame(path, name_of_it) == TRUE) {
                        goto descend;
                    }
                }

                if (ARCNodeIsFolder(nodes[it])) {
                    it = nodes[it].folder.sibling_next;
                    break;
                }

                ++it;
                break;
            }
        }

        return -1;

    descend:
        // If the path was truncated, there is nowhere else to go
        // These basic blocks have to go here right at the end, accessed via a
        // goto. An odd choice.
        if (!name_delimited_by_slash) {
            return it;
        }

        path += name_length + 1;
    }
}

static u32 entryToPath(ARCHandle* handle, u32 entrynum, char* string,
                       u32 maxlen) {
    char* name;
    u32 written;
    ARCNode* nodes = handle->nodes;

    if (entrynum == 0) {
        return 0;
    }

    name = ((char*)handle->strings) + nodes[entrynum].name;

    written =
        entryToPath(handle, nodes[entrynum].folder.parent, string, maxlen);
    if (written == maxlen) {
        return written;
    }

    string[written++] = '/';
    return written + myStrncpy(string + written, name, maxlen - written);
}

void* ARCGetStartAddrInMem(ARCFileInfo* info) {
    return (u8*)info->handle->header + info->offset;
}

s32 ARCGetStartOffset(ARCFileInfo* info) {
    return info->offset;
}

u32 ARCGetLength(ARCFileInfo* info) {
    return info->size;
}

BOOL ARCClose(ARCFileInfo* info) {
#pragma unused(info)

    return TRUE;
}

BOOL ARCChangeDir(ARCHandle* info, const char* path) {
    s32 entrynum = ARCConvertPathToEntrynum(info, path);
    ARCNode* nodes = info->nodes;

    if (entrynum < 0 || !ARCNodeIsFolder(nodes[entrynum])) {
        return FALSE;
    }

    info->entrynum = entrynum;
    return TRUE;
}

BOOL ARCOpenDir(ARCHandle* info, const char* path, ARCDir* dir) {
    s32 entrynum = ARCConvertPathToEntrynum(info, path);
    ARCNode* nodes = info->nodes;

    if (entrynum < 0 || !ARCNodeIsFolder(nodes[entrynum])) {
        return FALSE;
    }

    dir->handle = info;
    dir->path_begin = entrynum;
    dir->path_it = entrynum + 1;
    dir->path_end = nodes[entrynum].folder.sibling_next;
    return TRUE;
}

BOOL ARCReadDir(ARCDir* dir, ARCEntry* entry) {
    u32 it;
    ARCNode* nodes;
    ARCHandle* arc = dir->handle;

    nodes = arc->nodes;
    it = dir->path_it;

    while (TRUE) {
        if (it <= dir->path_begin || dir->path_end <= it) {
            return FALSE;
        }

        entry->handle = arc;
        entry->path = it;
        // All non-file entries are folders.
        // Collapse to one specific value.
        entry->type =
            ARCNodeIsFolder(nodes[it]) ? ARC_ENTRY_FOLDER : ARC_ENTRY_FILE;
        entry->name = arc->strings + nodes[it].name;

        // skip '.' directories
        if (entry->name[0] == '.' && entry->name[1] == '\0') {
            ++it;
            continue;
        }

        dir->path_it =
            ARCNodeIsFolder(nodes[it]) ? nodes[it].folder.sibling_next : it + 1;
        return TRUE;
    }
}

BOOL ARCCloseDir(ARCDir* dir) {
#pragma unused(dir)

    return TRUE;
}
