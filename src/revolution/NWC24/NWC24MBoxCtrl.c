#include <revolution/NWC24.h>

MountInfoStruct MountInfo;

int Mail_sprintf(char* buffer, const char* format, ...);

NWC24Err DuplicationCheck(MBoxControlHeader* header, const NWC24MsgObj* msg, NWC24File* file, s32 mboxType);
NWC24Err DeleteMsg(s32 mboxType, u32 msgId, u32 flags);
NWC24Err GetCachedMBCHeader(s32 mboxType, MBoxControlHeader** headerOut);
NWC24Err AddMBCEntry(MBoxControlHeader* header, const NWC24MsgObj* msg, NWC24File* file);
NWC24Err MountVFMBox(s32 mboxType);
NWC24Err CopyMsgObjToMBCFmt(const NWC24MsgObj* src, MBoxControlEntry* dst);

inline static NWC24Err UnmountVFMBox(void) {
    s32 count;
    u32 freeSize;
    NWC24Err err;
    NWC24Err unmountErr;
    MBoxControlHeader* header;

    count = MountInfo.count;
    if (count == 0) {
        unmountErr = NWC24_OK;
    } else {
        count--;
        MountInfo.count = count;
        if (count > 0) {
            unmountErr = NWC24_OK;
        } else {
            err = GetCachedMBCHeader(MountInfo.type, &header);
            if (err != NWC24_OK) {
                unmountErr = err;
            } else {
                err = NWC24CheckSizeVF("@24", &freeSize);
                if (err != NWC24_OK) {
                    unmountErr = err;
                } else {
                    header->freeSpace = freeSize;
                    unmountErr = NWC24UnmountVF("@24");
                }
            }
        }
    }
    return unmountErr;
}

NWC24Err NWC24iOpenMBox(void) {
    NWC24Err err;
    MBoxControlHeader* header;
    NWC24File recvFile;
    NWC24File sendFile;
    char* pathWork;
    const char* mboxDir;

    pathWork = NWC24WorkP->pathWork;

    Mail_memset(NWC24WorkP->WORK_0x1100, 0, sizeof(MBoxControlHeader));
    err = GetCachedMBCHeader(0, &header);
    if (err != NWC24_OK) {
        return err;
    }

    Mail_memset(NWC24WorkP->WORK_0x1180, 0, sizeof(MBoxControlHeader));
    err = GetCachedMBCHeader(1, &header);
    if (err != NWC24_OK) {
        return err;
    }

    mboxDir = NWC24GetMBoxDir();
    if (STD_strnlen(mboxDir, 0x40) + 14 > 0x100) {
        err = NWC24_ERR_NOMEM;
    } else {
        Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24send.ctl");
        err = NWC24_OK;
    }

    if (err != NWC24_OK) {
        return err;
    }

    err = NWC24FOpen(&recvFile, pathWork, 2);
    if (err == NWC24_OK) {
        err = NWC24FClose(&recvFile);
    }

    if (err != NWC24_OK) {
        return err;
    }

    mboxDir = NWC24GetMBoxDir();
    if (STD_strnlen(mboxDir, 0x40) + 14 > 0x100) {
        err = NWC24_ERR_NOMEM;
    } else {
        Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24recv.ctl");
        err = NWC24_OK;
    }

    if (err != NWC24_OK) {
        return err;
    }

    err = NWC24FOpen(&sendFile, pathWork, 2);
    if (err == NWC24_OK) {
        err = NWC24FClose(&sendFile);
    }

    if (err != NWC24_OK) {
        return err;
    }

    MountInfo.count = 0;
    MountInfo.type = 0;
    return NWC24_OK;
}

NWC24Err NWC24iMBoxOpenNewMsg(s32 mboxType, NWC24File* file, u32* msgId) {
    NWC24Err err;
    MBoxControlHeader* header;
    MBoxControlHeader* footer;
    char* path;
    u32 id;

    err = GetCachedMBCHeader(mboxType, &header);
    if (err != NWC24_OK) {
        return err;
    }

    footer = header;

    if (footer->magic != 0x57635466) {
        err = NWC24_ERR_INVALID_VALUE;
    } else {
        if (footer->nextMsgId > 1000000) {
            footer->nextMsgId = 1;
        }
        err = NWC24_OK;
        *msgId = footer->nextMsgId;
        footer->nextMsgId++;
    }

    if (err != NWC24_OK) {
        return err;
    }

    err = MountVFMBox(mboxType);
    if (err != NWC24_OK) {
        return err;
    }

    id = *msgId;
    path = NWC24WorkP->pathWork;

    switch (mboxType) {
        case 0:
            Mail_sprintf(path, "@24:/mb/s%07d.msg", id);
            break;
        case 1:
            Mail_sprintf(path, "@24:/mb/r%07d.msg", id);
            break;
        default:
            err = NWC24_ERR_INVALID_VALUE;
            goto check_mbox;
    }

    err = NWC24_OK;

check_mbox:
    if (err != NWC24_OK) {
        return err;
    }

    err = NWC24FOpen(file, path, 0x109);
    return err;
}

NWC24Err NWC24iMBoxCloseMsg(NWC24File* file) {
    NWC24Err err;
    u32 freeSize;
    MBoxControlHeader* header;
    s32 count;
    NWC24Err unmountErr;
    NWC24Err closeErr;

    closeErr = NWC24FClose(file);
    // unmountErr = UnmountVFMBox();
    // This code could be replaced with a call to UnmountVFMBox but that causes issues with the assembly matching.

    count = MountInfo.count;
    if (count == 0) {
        unmountErr = NWC24_OK;
    } else {
        count--;
        MountInfo.count = count;
        if (count > 0) {
            unmountErr = NWC24_OK;
        } else {
            err = GetCachedMBCHeader(MountInfo.type, &header);
            if (err != NWC24_OK) {
                unmountErr = err;
            } else {
                err = NWC24CheckSizeVF("@24", &freeSize);
                if (err != NWC24_OK) {
                    unmountErr = err;
                } else {
                    header->freeSpace = freeSize;
                    unmountErr = NWC24UnmountVF("@24");
                }
            }
        }
    }

    if (closeErr != NWC24_OK && unmountErr != NWC24_OK) {
        return unmountErr;
    }
    return closeErr;
}

NWC24Err NWC24iMBoxCancelMsg(NWC24File* file, s32 mboxType, u32 msgId) {
    s32 result = (s32)msgId;
    char* pathWork;
    unsigned int tempErr;
    NWC24Err deleteErr;
    NWC24Err closeErr;
    NWC24Err unmountErr;

    closeErr = NWC24FClose(file);
    unmountErr = MountVFMBox(mboxType);

    if (unmountErr != NWC24_OK) {
        result = unmountErr;
    } else {
        pathWork = NWC24WorkP->pathWork;
        switch (mboxType) {
            case 0:
                Mail_sprintf(pathWork, "@24:/mb/s%07d.msg", result);
                break;

            case 1:
                Mail_sprintf(pathWork, "@24:/mb/r%07d.msg", result);
                break;

            default:
                result = NWC24_ERR_INVALID_VALUE;
                goto check_result;
        }

        result = NWC24_OK;

    check_result:
        // TODO(Alex9303) Permuter fake(?)match
        deleteErr = result;
        if (deleteErr != NWC24_OK) {
            result = deleteErr;
        } else {
            deleteErr = NWC24FDeleteVF(pathWork);
            tempErr = deleteErr;
            unmountErr = UnmountVFMBox();
            if (tempErr != NWC24_OK) {
                result = tempErr;
            } else {
                result = unmountErr;
            }
        }
    }

    MountInfo.count = 1;

    unmountErr = UnmountVFMBox();
    if (closeErr != NWC24_OK) {
        return closeErr;
    }
    if (result != NWC24_OK) {
        return result;
    }
    if (unmountErr != NWC24_OK) {
        return unmountErr;
    }
    return NWC24_OK;
}

NWC24Err NWC24iMBoxAddMsgObj(s32 mboxType, NWC24MsgObj* msg) {
    NWC24Err err;
    NWC24Err closeErr;
    MBoxControlHeader* header;
    MBoxControlHeader* header2;
    const char* mboxDir;
    char* pathWork;
    NWC24File file;

    err = GetCachedMBCHeader(mboxType, &header);
    if (err != NWC24_OK) {
        return err;
    }

    if (header->msgCount == header->capacity) {
        return NWC24_ERR_FULL;
    }

    pathWork = NWC24WorkP->pathWork;

    mboxDir = NWC24GetMBoxDir();

    if (STD_strnlen(mboxDir, 0x40) + 14 > 0x100) {
        err = NWC24_ERR_NOMEM;
    } else {
        switch (mboxType) {
            case 0:
                Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24send.ctl");
                break;
            case 1:
                Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24recv.ctl");
                break;
            default:
                err = NWC24_ERR_INVALID_VALUE;
                goto check_result;
        }
        err = NWC24_OK;
    }
check_result:
    if (err != NWC24_OK) {
        return err;
    }

    err = NWC24FOpen(&file, pathWork, 4);
    if (err != NWC24_OK) {
        return err;
    }

    err = AddMBCEntry(header, msg, &file);
    if (err == NWC24_OK) {
        err = DuplicationCheck(header, msg, &file, mboxType);
        if (err == NWC24_OK) {
            // TODO(Alex9303) Fakematch: (possibly) Missing inline function
            header2 = header;
            NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
            err = NWC24FWrite(header2, sizeof(MBoxControlHeader), &file);
        }
    }

    closeErr = NWC24FClose(&file);
    if (err != NWC24_OK) {
        return err;
    }

    return closeErr;
}

NWC24Err NWC24iMBoxFlushHeader(s32 mboxType) {
    NWC24Err err;
    NWC24Err closeErr;
    MBoxControlHeader* header;
    MBoxControlHeader* header2;
    const char* mboxDir;
    char* pathWork;
    NWC24File file;

    err = GetCachedMBCHeader(mboxType, &header);
    if (err != NWC24_OK) {
        return err;
    }

    pathWork = NWC24WorkP->pathWork;
    mboxDir = NWC24GetMBoxDir();

    if (STD_strnlen(mboxDir, 0x40) + 14 > 0x100) {
        err = NWC24_ERR_NOMEM;
    } else {
        switch (mboxType) {
            case 0:
                err = Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24send.ctl");
                break;
            case 1:
                err = Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24recv.ctl");
                break;
            default:
                err = NWC24_ERR_INVALID_VALUE;
                goto check_result;
        }
        err = NWC24_OK;
    }
check_result:
    if (err != NWC24_OK) {
        return err;
    }

    err = NWC24FOpen(&file, pathWork, 4);
    if (err != NWC24_OK) {
        return err;
    }

    // TODO(Alex9303) Fakematch: (possibly) Missing inline function
    header2 = header;
    NWC24FSeek(&file, 0, 0);
    err = NWC24FWrite(header2, 0x80, &file);
    closeErr = NWC24FClose(&file);

    if (err != NWC24_OK) {
        return err;
    }

    return closeErr;
}

NWC24Err NWC24iMBoxCheck(s32 mboxType, u32 requiredSize) {
    NWC24Err err;
    MBoxControlHeader* header;
    volatile long oldestMsgId;
    u32 spaceWithBuffer;

    if (requiredSize >= 0x31C00) {
        return NWC24_ERR_OVERFLOW;
    }

    spaceWithBuffer = requiredSize + 0x4000;

    err = GetCachedMBCHeader(mboxType, &header);
    if (err != NWC24_OK) {
        return err;
    }

    if (mboxType == 0) {
        if (header->msgCount >= header->capacity) {
            return NWC24_ERR_FULL;
        }
        if (header->freeSpace <= spaceWithBuffer) {
            return NWC24_ERR_FULL;
        }
    } else if (mboxType == 1) {
        while (header->msgCount >= header->capacity || header->freeSpace <= spaceWithBuffer) {
            oldestMsgId = header->oldestMsgId;
            err = DeleteMsg(mboxType, oldestMsgId, 0);
            if (err != NWC24_OK) {
                return err;
            }

            err = GetCachedMBCHeader(mboxType, &header);
            if (err != NWC24_OK) {
                return err;
            }
        }
    } else {
        return NWC24_ERR_INVALID_VALUE;
    }
    return NWC24_OK;
}

NWC24Err DeleteMsg(s32 mboxType, u32 msgId, u32 flags) {
    NWC24Err err;
    const char* mboxDir;
    MBoxControlHeader* header;
    u32 entryOffsetToDelete = 0;
    MBoxControlHeader* header3;
    NWC24File file;
    s32 pathLen;
    u32 offset;
    char* pathWorkCopy;
    MBoxControlHeader* header2;
    int cmp;
    MBoxControlEntry* entry2;
    u32 checkedCount = 0;
    u32 oldestMsgId = 0;
    MBoxControlEntry* entry;
    NWC24Err mountErr = NWC24_OK;
    NWC24Err writeErr = NWC24_OK;
    NWC24Err deleteErr = NWC24_OK;
    char* pathWork;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }
    entry = (MBoxControlEntry*)((char*)NWC24WorkP + 0x1200);

    err = GetCachedMBCHeader(mboxType, &header);
    if (err != NWC24_OK) {
        return err;
    }

    pathWorkCopy = NWC24WorkP->pathWork;
    pathWork = pathWorkCopy;
    mboxDir = NWC24GetMBoxDir();

    pathLen = STD_strnlen(mboxDir, 64);

    if (pathLen + 14 > 256) {
        err = NWC24_ERR_NOMEM;
    } else {
        switch (mboxType) {
            case 0:
                Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24recv.ctl");
                break;
            case 1:
                Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24send.ctl");
                break;
            default:
                err = NWC24_ERR_INVALID_VALUE;
                goto check_result1;
        }

        err = NWC24_OK;
    }
check_result1:
    if (err != NWC24_OK) {
        return err;
    }

    err = NWC24FOpen(&file, pathWork, 4);
    if (err != NWC24_OK) {
        return err;
    }

    err = NWC24_ERR_NOT_FOUND;

    for (offset = 0x80; offset < header->mailDataOffset; offset += 0x80) {
        NWC24Err readErr;
        NWC24FSeek(&file, offset, NWC24_SEEK_BEG);
        readErr = NWC24FRead(entry, 0x80, &file);
        if (readErr != NWC24_OK) {
            err = readErr;
            break;
        }

        if (entry->id == 0) {
            continue;
        }

        entryOffsetToDelete++;

        if (entry->id == msgId) {
            if (flags != 0) {
                if ((entry->flags & 0x2) != 0) {
                    if (NWC24GetAppId() - 0x48410000 != 0x4541) {
                        err = NWC24_ERR_PROTECTED;
                        break;
                    }
                } else {
                    if ((entry->appId & 0xFFFFFF00) != (NWC24GetAppId() & 0xFFFFFF00)) {
                        if ((entry->flags & 0x8) != 0) {
                            if (NWC24GetAppId() - 0x48410000 == 0x4541) {
                                goto permission_ok;
                            }
                        }
                        err = NWC24_ERR_PROTECTED;
                        break;
                    }
                }
            }
        permission_ok:

            checkedCount = offset;
            err = NWC24_OK;
            continue;
        }

        if (oldestMsgId != 0) {
            if (oldestMsgId == entry->id) {
                cmp = 0;
            } else if (oldestMsgId > 900000 && entry->id < 100000) {
                cmp = -1;
            } else if (oldestMsgId < 100000 && entry->id > 900000) {
                cmp = 1;
            } else if (oldestMsgId > entry->id) {
                cmp = 1;
            } else {
                cmp = -1;
            }
            if (cmp <= 0) {
                continue;
            }
        }

        oldestMsgId = entry->id;
    }

    if (err == NWC24_ERR_NOT_FOUND) {
        if (header->msgCount != entryOffsetToDelete) {
            header->msgCount = entryOffsetToDelete;

            // TODO(Alex9303) Fakematch: (possibly) Missing inline function
            header3 = header;
            NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
            NWC24FWrite(header3, 0x80, &file);
        }
    }

    if (err != NWC24_OK) {
        NWC24FClose(&file);

        if (msgId == 0) {
            err = NWC24_ERR_INVALID_VALUE;
        }

        return err;
    }

    header->oldestMsgId = oldestMsgId;

    // TODO(Alex9303) Fakematch: (possibly) Missing inline function
    header2 = header;

    // TODO(Alex9303) Fakematch: (possibly) Missing inline function
    entry2 = (MBoxControlEntry*)(((char*)NWC24WorkP) + 0x1200);
    entry = entry2;
    NWC24FSeek(&file, checkedCount, NWC24_SEEK_BEG);
    NWC24FRead(entry, 0x80, &file);

    header2->msgCount--;
    header2->totalMsgSize -= entry->length;

    memset(entry, 0, 0x80);
    entry->appId = header2->nextFreeEntry;
    header2->nextFreeEntry = checkedCount;

    NWC24FSeek(&file, checkedCount, NWC24_SEEK_BEG);
    writeErr = NWC24FWrite(entry, 0x80, &file);

    mountErr = MountVFMBox(mboxType);
    switch (mountErr) {
        case NWC24_OK:
            pathWork = NWC24WorkP->pathWork;
            switch (mboxType) {
                case 0:
                    Mail_sprintf(pathWork, "@24:/mb/r%07d.msg", msgId);
                    break;
                case 1:
                    Mail_sprintf(pathWork, "/shared2/wc24/mbox/s%07d.msg", msgId);

                    break;
                default:
                    mountErr = NWC24_ERR_INVALID_VALUE;
                    goto check_result2;
            }
            mountErr = NWC24_OK;

        check_result2:
            switch (mountErr) {
                case NWC24_OK:
                    deleteErr = NWC24FDeleteVF(pathWork);
                    mountErr = UnmountVFMBox();
                    if (deleteErr != NWC24_OK) {
                        mountErr = deleteErr;
                    }
                    break;
            }
            break;
    }

    // TODO(Alex9303) Fakematch: Reusing arguments msgId/mboxType as error variables to match r23/r22
    msgId = mountErr;
    if (writeErr != NWC24_OK) {
        msgId = writeErr;
    }

    // TODO(Alex9303) Fakematch: (possibly) Missing inline function
    header2 = header;
    NWC24FSeek(&file, 0, NWC24_SEEK_BEG);

    mboxType = NWC24FWrite(header2, 0x80, &file);
    if (msgId != NWC24_OK) {
        mboxType = msgId;
    }

    err = NWC24FClose(&file);
    if (mboxType != NWC24_OK) {
        err = mboxType;
    }

    return err;
}

NWC24Err DuplicationCheck(MBoxControlHeader* header, const NWC24MsgObj* msg, NWC24File* file, s32 mboxType) {
    NWC24Err err;
    u32 offset;
    u32 checkedCount;
    u32 bestMsgId;
    u32 bestOffset;
    u32 oldestMsgId;
    MBoxControlEntry* entry;
    char* pathWork;
    char** pathWorkPtr;

    err = NWC24_OK;
    checkedCount = 0;
    bestMsgId = 0;
    bestOffset = 0;
    oldestMsgId = 0;

    pathWorkPtr = &pathWork;

    if (mboxType == 0) {
        return NWC24_OK;
    }

    entry = (MBoxControlEntry*)((char*)NWC24WorkP + 0x1200);

    for (offset = 0x80; offset < header->mailDataOffset; offset += 0x80) {
        int isDuplicate;
        int cmp;

        if (checkedCount >= header->msgCount) {
            break;
        }

        err = NWC24FSeek(file, offset, NWC24_SEEK_BEG);
        err = NWC24FRead(entry, 0x80, file);
        if (err != NWC24_OK) {
            break;
        }

        if (entry->id == 0) {
            continue;
        }

        checkedCount++;
        isDuplicate = 1;

        if (entry->id == msg->id) {
            isDuplicate = 0;
        }

        if ((entry->flags & msg->flags & 1) != 0) {
            if (entry->appId != msg->appId) {
                isDuplicate = 0;
            }
            if (entry->fromId != msg->fromId) {
                isDuplicate = 0;
            }
        }

        if (isDuplicate) {
            u32 msgTag = msg->tag & 0xFFFF;
            u32 msgCreationMs;

            if (msgTag != 0) {
                if ((entry->tag & 0xFFFF) == msgTag) {
                    bestMsgId = entry->id;
                    bestOffset = offset;
                    continue;
                }
            }

            msgCreationMs = ((const u32*)msg)[7];
            if (msgCreationMs != 0 && entry->nextFreeOrCreationMs == msgCreationMs && entry->flags == msg->flags && entry->length == msg->length && entry->UNK_0x10 == ((const u32*)msg)[4] && (s32)entry->createTime == (s32)((const u32*)msg)[10]) {
                bestMsgId = entry->id;
                bestOffset = offset;
                continue;
            }
        }

        if (oldestMsgId != 0) {
            if (oldestMsgId == entry->id) {
                cmp = 0;
            } else if (oldestMsgId > 900000 && entry->id < 100000) {
                cmp = -1;
            } else if (oldestMsgId < 100000 && entry->id > 900000) {
                cmp = 1;
            } else if (oldestMsgId > entry->id) {
                cmp = 1;
            } else {
                cmp = -1;
            }

            if (cmp <= 0) {
                continue;
            }
        }

        oldestMsgId = entry->id;
    }

    if (err != NWC24_OK) {
        return err;
    }

    header->oldestMsgId = oldestMsgId;

    if (bestMsgId != 0) {
        NWC24Err writeErr;
        NWC24Err result;

        entry = (MBoxControlEntry*)(((char*)NWC24WorkP) + 0x1200);
        pathWork = NWC24WorkP->WORK_0x1200;

        err = NWC24FSeek(file, bestOffset, NWC24_SEEK_BEG);
        err = NWC24FRead(*pathWorkPtr, 0x80, file);

        header->msgCount--;
        header->totalMsgSize -= entry->length;

        memset(entry, 0, 0x80);
        entry->appId = header->nextFreeEntry;
        header->nextFreeEntry = bestOffset;

        err = NWC24FSeek(file, bestOffset, NWC24_SEEK_BEG);
        writeErr = NWC24FWrite(entry, 0x80, file);

        err = MountVFMBox(mboxType);
        if (err != NWC24_OK) {
            result = err;
        } else {
            pathWork = NWC24WorkP->pathWork;

            switch (mboxType) {
                case 0:
                    Mail_sprintf(pathWork, "/wc24recv.mbx", bestMsgId);
                    break;

                case 1:
                    Mail_sprintf(pathWork, "/wc24send.mbx", bestMsgId);
                    break;

                default:
                    err = NWC24_ERR_INVALID_VALUE;
                    goto check_result;
            }

            err = NWC24_OK;
        check_result:
            if (err != NWC24_OK) {
                result = err;
            } else {
                NWC24Err deleteErr = NWC24FDeleteVF(pathWork);

                result = UnmountVFMBox();
                if (deleteErr != NWC24_OK) {
                    result = deleteErr;
                }
            }
        }

        if (writeErr != NWC24_OK) {
            result = writeErr;
        }

        return result;
    }

    return err;
}

NWC24Err GetCachedMBCHeader(s32 mboxType, MBoxControlHeader** headerOut) {
    NWC24Err err;
    const char* mboxDir;
    NWC24File file;
    MBoxControlHeader* header;
    NWC24Err result = NWC24_OK;
    char* pathWork;

    if (mboxType == 0) {
        *headerOut = (MBoxControlHeader*)NWC24WorkP->WORK_0x1100;
    } else if (mboxType == 1) {
        *headerOut = (MBoxControlHeader*)NWC24WorkP->WORK_0x1180;
    } else {
        *headerOut = 0;
        return NWC24_ERR_INVALID_VALUE;
    }

    if ((*headerOut)->magic != 0x57635466) {
        pathWork = NWC24WorkP->pathWork;
        mboxDir = NWC24GetMBoxDir();

        if (STD_strnlen(mboxDir, 0x40) + 14 > 0x100) {
            err = NWC24_ERR_NOMEM;
        } else {
            switch (mboxType) {
                case 0:
                    Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24send.ctl");
                    break;
                case 1:
                    Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24recv.ctl");
                    break;
                default:
                    err = NWC24_ERR_INVALID_VALUE;
                    goto check_result;
            }
            err = NWC24_OK;
        }
    check_result:
        if (err != NWC24_OK) {
            return err;
        }

        err = NWC24FOpen(&file, pathWork, 2);
        if (err != NWC24_OK) {
            return err;
        }

        header = *headerOut;
        NWC24FSeek(&file, 0, 0);
        err = NWC24FRead(header, 0x80, &file);
        if (err != NWC24_OK) {
            result = err;

        } else {
            result = NWC24_OK;
            if ((header)->magic != 0x57635466) {
                result = NWC24_ERR_BROKEN;
            }
        }
        err = NWC24FClose(&file);
        if (result == NWC24_OK) {
            if (err != NWC24_OK) {
                result = err;
            }
        }
    }

    if ((*headerOut)->version != 4) {
        result = NWC24_ERR_VER_MISMATCH;
    }
    return result;
}

NWC24Err AddMBCEntry(MBoxControlHeader* header, const NWC24MsgObj* msg, NWC24File* file) {
    s32 entryOffset = header->nextFreeEntry;
    MBoxControlEntry* entryBuffer;
    s32 nextEntryOffset;
    NWC24Err err;

    entryBuffer = (MBoxControlEntry*)NWC24WorkP->WORK_0x1200;

    if (entryOffset == 0) {
        return NWC24_ERR_FULL;
    }

    if ((u32)entryOffset >= header->mailDataOffset || ((entryOffset - 0x80) & 0x7F) != 0) {
        return NWC24_ERR_BROKEN;
    }

    NWC24FSeek(file, entryOffset, NWC24_SEEK_BEG);

    err = NWC24FRead(entryBuffer, sizeof(MBoxControlEntry), file);
    if (err != NWC24_OK) {
        return err;
    }

    nextEntryOffset = entryBuffer->appId;

    if ((u32)nextEntryOffset >= header->mailDataOffset || ((nextEntryOffset - 0x80) & 0x7F) != 0) {
        return NWC24_ERR_BROKEN;
    }

    header->nextFreeEntry = nextEntryOffset;
    CopyMsgObjToMBCFmt(msg, entryBuffer);

    NWC24FSeek(file, entryOffset, NWC24_SEEK_BEG);

    err = NWC24FWrite(entryBuffer, sizeof(MBoxControlEntry), file);
    if (err != NWC24_OK) {
        return err;
    }

    if (header->msgCount == 0) {
        header->oldestMsgId = msg->id;
    }

    header->msgCount++;
    header->totalMsgSize += msg->length;
    return NWC24_OK;
}

NWC24Err MountVFMBox(s32 mboxType) {
    s32 result;
    NWC24Err err;
    const char* mboxDir;
    char* pathWork;

    if (MountInfo.count != 0 && MountInfo.type != mboxType) {
        MountInfo.count = 1;
        UnmountVFMBox();
        return NWC24_ERR_FATAL;
    }

    if ((s32)(++MountInfo.count) > 1) {
        return NWC24_OK;
    }

    pathWork = NWC24WorkP->pathWork;
    mboxDir = NWC24GetMBoxDir();
    if (STD_strnlen(mboxDir, 0x40) + 14 > 0x100) {
        result = NWC24_ERR_NOMEM;
    } else {
        switch (mboxType) {
            case 0:
                Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24recv.mbx");
                break;

            case 1:
                Mail_sprintf(pathWork, "%s%s", mboxDir, "/wc24send.mbx");
                break;

            default:
                result = NWC24_ERR_INVALID_VALUE;
                goto check_result;
        }

        result = NWC24_OK;
    }

check_result:
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24_OK;
    err = NWC24MountVF("@24", pathWork);
    if (err != result) {
        return err;
    } else {
        err = result;
        MountInfo.type = mboxType;
    }

    return err;
}

NWC24Err CopyMsgObjToMBCFmt(const NWC24MsgObj* src, MBoxControlEntry* dst) {
    u32 packData30 = (((u32)src->DATA_0x30.ptr) & 0xFFFFF) | (src->DATA_0x30.size << 20);
    u32 packData38 = (((u32)src->DATA_0x38.ptr) & 0xFFFFF) | (src->DATA_0x38.size << 20);
    u32 packSubject = (((u32)src->subject.ptr) & 0xFFFFF) | (src->subject.size << 20);
    u32 packContent = (((u32)src->contentType.ptr) & 0xFFFFF) | (src->contentType.size << 20);
    u32 packTransfer = (((u32)src->transferEncoding.ptr) & 0xFFFFF) | (src->transferEncoding.size << 20);

    dst->id = src->id;
    dst->flags = src->flags;
    dst->length = src->length;
    dst->appId = src->appId;
    *(u32*)&dst->UNK_0x10 = src->UNK_0x10;
    dst->tag = src->tag;
    dst->ledPattern = src->ledPattern;
    dst->nextFreeOrCreationMs = *(const u32*)((const u8*)src + 0x1C);
    ((u32*)&dst->fromId)[0] = ((u32*)&src->fromId)[0];

    ((u32*)&dst->fromId)[1] = ((u32*)&src->fromId)[1];

    dst->createTime = src->createTime;
    dst->UNK_0x2C = src->WORD_0x2C;

    *(u8*)&dst->numTo = src->numTo;
    *(u8*)((u8*)dst + 0x31) = src->numAttached;
    *(u16*)((u8*)dst + 0x32) = src->groupId;

    dst->packedSubjectText = packData30;
    dst->packedTextSubjectSize = packData38;
    dst->packedSubjectTextSize = packSubject;
    dst->packedTextSizeContentType = packContent;
    dst->packedContentTypeTransferEnc = packTransfer;

    dst->textPtr = (u32)src->text.ptr;
    dst->textSize = src->text.size;
    dst->textOrigSize = *(const u32*)((const u8*)src + 0xE8);
    dst->UNK_0x74 = *(const u32*)((const u8*)src + 0xEC);

    dst->attached0Ptr = (u32)src->attached[0].ptr;
    dst->attached0Size = src->attached[0].size;
    dst->attached0OrigSize = src->attachedSize[0];
    dst->attached0_type = src->attachedType[0];

    dst->attached1Ptr = (u32)src->attached[1].ptr;
    dst->attached1Size = src->attached[1].size;
    dst->attached1OrigSize = src->attachedSize[1];
    dst->attached1_type = src->attachedType[1];

    return NWC24_OK;
}
