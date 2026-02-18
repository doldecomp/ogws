#include <revolution/NWC24.h>

extern char MultiPartDivider[40];
static const char* LoopBackEnable = (const char[]){0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
static char* MonthStr[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

extern NWC24Work* NWC24WorkP;

extern void* m_pFile;
extern const char* ContentTypeA;
extern const char* ContentTxEncA;
extern const char* ContentDispA;
extern const char* ContentTypeTP;
extern const char* ContentTxEncT;

int Mail_sprintf(char *buffer, const char *format, ...);

NWC24Err NWC24CommitMsgInternal(NWC24MsgObj* msg, s32 flagLocal);
NWC24Err WriteBase64Data(const void* data, u32 size, u32* bytesWritten);
NWC24Err WriteQPData(const void* data, u32 size, u32* bytesWritten);
NWC24Err CheckMsgBoxSpace(NWC24MsgObj* msg, u32 requiredSize);
NWC24Err WriteSMTP_MAILFROM(NWC24MsgObj* msg);
NWC24Err WriteSMTP_RCPTTO(NWC24MsgObj* msg);
NWC24Err WriteFromField(NWC24MsgObj* msg);
NWC24Err WriteToField(NWC24MsgObj* msg);
NWC24Err WriteDateField(NWC24MsgObj* msg);
NWC24Err WriteXWiiAppIdField(NWC24MsgObj* msg);
NWC24Err WriteXWiiFaceField(NWC24MsgObj* msg);
NWC24Err WriteXWiiAltNameField(NWC24MsgObj* msg);
NWC24Err WriteMIMEAttachHeader(NWC24MsgObj* msg, u32 attachIndex);
NWC24Err WriteContentTypeField(NWC24MsgObj* msg);
NWC24Err WritePlainText(NWC24MsgObj* msg);
NWC24Err CheckMsgObject(const NWC24MsgObj* msg);

NWC24Err NWC24FClose(NWC24File* file);
NWC24Err NWC24FWrite(const void* src, s32 size, NWC24File* file);
NWC24Err NWC24GetMyUserId(u64* idOut);
NWC24Err NWC24iMBoxAddMsgObj(s32 mboxType, NWC24MsgObj* msg);
NWC24Err NWC24iMBoxCancelMsg(NWC24File* file, s32 mboxType, u32 msgId);
NWC24Err NWC24iMBoxCloseMsg(NWC24File* file);
NWC24Err NWC24iMBoxFlushHeader(s32 mboxType);
NWC24Err NWC24iMBoxOpenNewMsg(s32 mboxType, NWC24File* file, u32* msgId);
NWC24Err NWC24iSetNewMsgArrived(u32 flags);
const char* NWC24GetAccountDomain(void);
u32 STD_strnlen(const char* str, u32 maxLen);
void NWC24Data_Init(NWC24Data* data);

NWC24Err NWC24CommitMsg(NWC24MsgObj *msg) {
    s32 flagLocal;
    u32 flags;
    u64 myUserId;
    u64 targetUserId;

    flagLocal = 0;

    if (NWC24IsMsgLibOpened() == 0 && NWC24IsMsgLibOpenedByTool() == 0) {
        return -9;
    }

    flags = msg->flags;

    if ((flags & 0x100) == 0 || (flags & 0x200) != 0) {
        return -7;
    }

    if (LoopBackEnable != 0 && (flags & 0x1) != 0) {
        NWC24GetMyUserId(&myUserId);
        if (msg->numTo == 1) {
            targetUserId = msg->toIds[0];
            if ((targetUserId ^ myUserId) == 0) {
                flagLocal = 1;
            }
        }
    }

    return NWC24CommitMsgInternal(msg, flagLocal);
}

static inline NWC24Err WriteDataCommand(NWC24MsgObj* msg) {
    NWC24Err result;
    char* stringWork = NWC24WorkP->stringWork;
    Mail_strcpy(stringWork, "DATA\r\n");
    result = NWC24FWrite(stringWork, Mail_strlen(stringWork), m_pFile);
    if (result == NWC24_OK) {
        msg->length += 6;
    }
    return result;
}

static inline NWC24Err WriteMessageIdField(NWC24MsgObj* msg) {
    u64 myUserId;
    char stackBuffer[32];
    NWC24Err result;
    u32 writeSize;
    char* stringWork = NWC24WorkP->stringWork;
    const char* domain = NWC24GetAccountDomain();
    NWC24GetMyUserId(&myUserId);
    Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_strcpy(stringWork, "Message-ID: <");
    Mail_memset(stackBuffer, 0, 32);
    Mail_sprintf(stackBuffer, "%08x%08x%08x%08x", msg->id, (u32)(myUserId >> 32), (u32)myUserId, msg->createTime);
    Mail_strcat(stringWork, stackBuffer);
    Mail_strcat(stringWork, domain);
    Mail_strcat(stringWork, ">\r\n");
    writeSize = Mail_strlen(stringWork);
    result = NWC24FWrite(stringWork, writeSize, m_pFile);
    if (result == NWC24_OK) {
        msg->length += writeSize;
    }
    return result;
}

static inline NWC24Err WriteSubjectField(NWC24MsgObj* msg) {
    char* stringWork = NWC24WorkP->stringWork;
    NWC24Err result;
    u32 writeSize;
    if (msg->subject.size == 0) {
        result = NWC24_ERR_NULL;
    } else {
        Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
        Mail_strcpy(stringWork, "Subject: ");
        Mail_strncat(stringWork, (const char*)msg->subject.ptr, 1021);
        Mail_strncat(stringWork, "\r\n", NWC24_WORK_BUFFER_SIZE);
        writeSize = STD_strnlen(stringWork, NWC24_WORK_BUFFER_SIZE);
        result = NWC24FWrite(stringWork, writeSize, m_pFile);
        if (result == NWC24_OK) {
            msg->length += writeSize;
        }
    }
    return result;
}

static inline NWC24Err WriteXWiiLedField(NWC24MsgObj* msg) {
    NWC24Err result;
    u32 writeSize;
    if (msg->ledPattern == 0) {
        return NWC24_OK;
    } else {
        char* stringWork = NWC24WorkP->stringWork;
        Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
        Mail_sprintf(stringWork, "X-Wii-Led: %08x\r\n", msg->ledPattern);
        writeSize = Mail_strlen(stringWork);
        result = NWC24FWrite(stringWork, writeSize, m_pFile);
        if (result == NWC24_OK) {
            msg->length += writeSize;
        }
    }
    return result;
}

static inline NWC24Err WriteXWiiTagField(NWC24MsgObj* msg) {
    NWC24Err result;
    u32 writeSize;
    if (msg->tag == 0) {
        return NWC24_OK;
    } else {
        char* stringWork = NWC24WorkP->stringWork;
        Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
        Mail_sprintf(stringWork, "X-Wii-Tag: %08x\r\n", msg->tag);
        writeSize = Mail_strlen(stringWork);
        result = NWC24FWrite(stringWork, writeSize, m_pFile);
        if (result == NWC24_OK) {
            msg->length += writeSize;
        }
    }
    return result;
}

static inline NWC24Err WriteXWiiAltField(NWC24MsgObj* msg) {
    NWC24Err result;
    u32 writeSize;
    if (!(msg->flags & 0x2000)) {
        return NWC24_OK;
    } else {
        char* stringWork = NWC24WorkP->stringWork;
        Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
        Mail_sprintf(stringWork, "X-Wii-Alt: %08x\r\n", (u32)msg->altMeta.size);
        writeSize = Mail_strlen(stringWork);
        result = NWC24FWrite(stringWork, writeSize, m_pFile);
        if (result == NWC24_OK) {
            msg->length += writeSize;
        }
    }
    return result;
}

static inline NWC24Err WriteXWiiMBParameterField(NWC24MsgObj* msg) {
    NWC24Err result;
    if (!(msg->mb.raw & 0x80000000)) {
        return NWC24_OK;
    } else {
        char* stringWork = NWC24WorkP->stringWork;
        Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
        Mail_strcpy(stringWork, "X-Wii-MB-Parameter:\r\n");
        result = NWC24FWrite(stringWork, 21, m_pFile);
        if (result == NWC24_OK) {
            msg->length += 21;
        }
    }
    return result;
}

static inline NWC24Err WriteXWiiMBRegDateField(NWC24MsgObj* msg) {
    u32 writeSize;
    NWC24Err result;
    u32 regdate = msg->mb.regdate;
    if (regdate == 0) {
        return NWC24_OK;
    } else {
        char* stringWork = NWC24WorkP->stringWork;
        Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
        Mail_sprintf(stringWork, "X-Wii-MB-RegDate: %04x\r\n", regdate);
        writeSize = STD_strnlen(stringWork, NWC24_WORK_BUFFER_SIZE);
        result = NWC24FWrite(stringWork, writeSize, m_pFile);
        if (result == NWC24_OK) {
            msg->length += writeSize;
        }
    }
    return result;
}

static inline NWC24Err WriteXWiiMBDelayField(NWC24MsgObj* msg) {
    NWC24Err result;
    u32 writeSize;
    u32 delay = msg->mb.raw & 0x00FF0000;
    if (delay == 0) {
        return NWC24_OK;
    } else {
        char* stringWork = NWC24WorkP->stringWork;
        Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
        Mail_sprintf(stringWork, "X-Wii-MB-Delay: %02x\r\n", delay >> 16);
        writeSize = STD_strnlen(stringWork, NWC24_WORK_BUFFER_SIZE);
        result = NWC24FWrite(stringWork, writeSize, m_pFile);
        if (result == NWC24_OK) {
            msg->length += writeSize;
        }
    }
    return result;
}

static inline NWC24Err WriteCustomHeader(NWC24MsgObj* msg) {
    NWC24Err result;
    if (msg->DATA_0xD0.size == 0) {
        return NWC24_OK;
    } else {
        result = NWC24FWrite(msg->DATA_0xD0.ptr, msg->DATA_0xD0.size, m_pFile);
        if (result == NWC24_OK) {
            msg->length += msg->DATA_0xD0.size;
        }
    }
    return result;
}

static inline NWC24Err WriteMimeHeader(NWC24MsgObj* msg) {
    char* stringWork = NWC24WorkP->stringWork;
    NWC24Err result;
    u32 writeSize;
    Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_strcpy(stringWork, "MIME-Version: 1.0\r\n");
    if (msg->flags & 0x10000) {
        Mail_strcat(stringWork, "Content-Type: multipart/mixed; boundary=\"");
        Mail_strcat(stringWork, MultiPartDivider);
        Mail_strcat(stringWork, "\"\r\n");
    }
    writeSize = Mail_strlen(stringWork);
    result = NWC24FWrite(stringWork, writeSize, m_pFile);
    if (result == NWC24_OK) {
        msg->length += writeSize;
    }
    return result;
}

static inline NWC24Err WriteMimeBoundary(NWC24MsgObj* msg) {
    char* stringWork = NWC24WorkP->stringWork;
    NWC24Err result;
    u32 writeSize;
    Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_sprintf(stringWork, "\r\n--%s", MultiPartDivider);
    Mail_strcat(stringWork, "\r\n");
    writeSize = Mail_strlen(stringWork);
    result = NWC24FWrite(stringWork, writeSize, m_pFile);
    if (result == NWC24_OK) {
        msg->length += writeSize;
    }
    return result;
}

static inline NWC24Err WritePlainTextWrapper(NWC24MsgObj* msg) {
    NWC24Err result;
    result = WritePlainText(msg);
    if (result == NWC24_ERR_NULL) {
        return NWC24_OK;
    }
    return result;
}

static inline NWC24Err WriteAttachedBase64(NWC24MsgObj* msg, s32 i) {
    NWC24Err result;
    u32 writeSize;
    result = WriteBase64Data(msg->attached[i].ptr, msg->attached[i].size, &writeSize);
    if (result == NWC24_OK) {
        msg->length += writeSize;
    }
    return result;
}

static inline NWC24Err WriteMimeBoundaryEnd(NWC24MsgObj* msg) {
    char* stringWork = NWC24WorkP->stringWork;
    NWC24Err result;
    u32 writeSize;
    Mail_memset(stringWork, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_sprintf(stringWork, "\r\n--%s", MultiPartDivider);
    Mail_strcat(stringWork, "--\r\n");
    writeSize = Mail_strlen(stringWork);
    result = NWC24FWrite(stringWork, writeSize, m_pFile);
    if (result == NWC24_OK) {
        msg->length += writeSize;
    }
    return result;
}

NWC24Err NWC24CommitMsgInternal(NWC24MsgObj* msg, s32 mboxType) {
    NWC24File file;
    s32 i = 0;
    u32 msgId;
    NWC24Data data1;
    NWC24Data data2;
    NWC24Data attachedData[2];
    NWC24Err result;
    NWC24Err err;

    NWC24Data_Init(&data1);
    NWC24Data_Init(&data2);

    for (i = 0; i < 2; i++) {
        NWC24Data_Init(&attachedData[i]);
    }

    NWC24iSetErrorCode(NWC24_OK);
    err = CheckMsgObject(msg);
    if (err != NWC24_OK) {
        goto exit_error;
    }
    err = CheckMsgBoxSpace(msg, mboxType);
    if (err != NWC24_OK) {
        goto exit_error;
    }
    result = NWC24iMBoxOpenNewMsg(mboxType, &file, &msgId);
    if (result != NWC24_OK) {
        err = result;
        goto error_break;
    }
    msg->id = msgId;
    msg->length = 0;
    m_pFile = &file;

    if (mboxType == 0) {
        result = WriteSMTP_MAILFROM(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }
        result = WriteSMTP_RCPTTO(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }
        result = WriteDataCommand(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }
    }

    result = WriteDateField(msg);
    if (result != NWC24_OK) {
        NWC24FClose(&file);
        err = result;
        goto error_break;
    }
    result = WriteFromField(msg);
    if (result != NWC24_OK) {
        NWC24FClose(&file);
        err = result;
        goto error_break;
    }
    result = WriteToField(msg);
    if (result != NWC24_OK) {
        NWC24FClose(&file);
        err = result;
        goto error_break;
    }

    result = WriteMessageIdField(msg);
    if (result != NWC24_OK) {
        NWC24FClose(&file);
        err = result;
        goto error_break;
    }

    data1.ptr = (void*)(msg->length + 9);
    result = WriteSubjectField(msg);
    if (result == NWC24_OK) {
        data1.size = (msg->length - ((u32)data1.ptr)) - 2;
    } else if (result == NWC24_ERR_NULL) {
        result = NWC24_OK;
        data1.ptr = 0;
    }
    if (result != NWC24_OK) {
        NWC24FClose(&file);
        err = result;
        goto error_break;
    }

    if (msg->flags & 1) {
        result = WriteXWiiAppIdField(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }

        result = WriteXWiiLedField(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }

        result = WriteXWiiTagField(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }

        result = WriteXWiiAltField(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }

        result = WriteXWiiAltNameField(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }

        result = WriteXWiiFaceField(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }

        if (msg->mb.raw != 0) {
            result = WriteXWiiMBParameterField(msg);
            if (result != NWC24_OK) {
                NWC24FClose(&file);
                err = result;
                goto error_break;
            }

            result = WriteXWiiMBRegDateField(msg);
            if (result != NWC24_OK) {
                NWC24FClose(&file);
                err = result;
                goto error_break;
            }

            result = WriteXWiiMBDelayField(msg);
            if (result != NWC24_OK) {
                NWC24FClose(&file);
                err = result;
                goto error_break;
            }
        }
    }

    result = WriteCustomHeader(msg);
    if (result != NWC24_OK) {
        NWC24FClose(&file);
        err = result;
        goto error_break;
    }

    Mail_memset(MultiPartDivider, 0, 40);
    // TODO(Alex9303) Replace string with correct string
    Mail_sprintf(MultiPartDivider, "----_%08x%08x__________", msg->createTime, msg->id);

    result = WriteMimeHeader(msg);
    if (result != NWC24_OK) {
        NWC24FClose(&file);
        err = result;
        goto error_break;
    }

    if (msg->flags & 0x10000ULL) {
        msg->UNK_0x10 = msg->length;
        result = WriteMimeBoundary(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }
    }

    result = WriteContentTypeField(msg);
    if (result != NWC24_OK) {
        NWC24FClose(&file);
        err = result;
        goto error_break;
    }
    if (!(msg->flags & 0x10000)) {
        msg->UNK_0x10 = msg->length;
    }
    data2.ptr = (void*)msg->length;
    result = WritePlainTextWrapper(msg);
    if (result != NWC24_OK) {
        NWC24FClose(&file);
        err = result;
        goto error_break;
    }
    data2.size = msg->length - ((u32)data2.ptr);

    for (i = 0; i < ((u32)msg->numAttached); i++) {
        result = WriteMimeBoundary(msg);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }

        result = WriteMIMEAttachHeader(msg, i);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }

        attachedData[i].ptr = (void*)msg->length;
        result = WriteAttachedBase64(msg, i);
        if (result != NWC24_OK) {
            NWC24FClose(&file);
            err = result;
            goto error_break;
        }

        attachedData[i].size = msg->length - ((u32)attachedData[i].ptr);

        if (i == (msg->numAttached - 1)) {
            result = WriteMimeBoundaryEnd(msg);
            if (result != NWC24_OK) {
                NWC24FClose(&file);
                err = result;
                goto error_break;
            }
        }
    }

error_break:
    if (err == NWC24_OK) {
        NWC24iMBoxCloseMsg(&file);
    } else {
        NWC24iMBoxCancelMsg(&file, mboxType, msgId);
        NWC24iMBoxFlushHeader(mboxType);
        goto exit_error;
    }

    msg->subject = data1;
    msg->text = data2;
    msg->attached[0] = attachedData[0];
    msg->attached[1] = *(attachedData + 1);
    msg->flags |= 0x200;

    if (mboxType == 1) {
        msg->flags |= 0x20;
    } else if (mboxType == 0) {
        msg->flags |= 0x10;
    }

    result = NWC24iMBoxAddMsgObj(mboxType, msg);
    if (err != NWC24_OK) {
        result = err;
    }
    err = result;

    if (mboxType == 1) {
        int arrivedFlags = 1;
        if (msg->flags & 8) {
            arrivedFlags |= 2;
        }
        NWC24iSetNewMsgArrived(arrivedFlags);
    }

exit_error:
    if ((((((err == (NWC24_ERR_FULL)) || ((err <= (NWC24_ERR_FILE_OPEN)) && (err >= (NWC24_ERR_FILE_OTHER)))) || (err == (NWC24_ERR_NAND_CORRUPT))) || (err == (NWC24_ERR_FILE_EXISTS))) || (err == (NWC24_ERR_INTERNAL_VF))) || (err == (NWC24_ERR_FILE_BROKEN))) {
        NWC24iSetErrorCode((NWC24Err)((err - 0x20000) + 21772));
    }

    return err;
}

NWC24Err CheckMsgObject(const NWC24MsgObj* msg) {
    const char* subject;

    u8 numTo = msg->numTo;
    if (numTo == 0) {
        return NWC24_ERR_NULL;
    }
    if (numTo > NWC24_MSG_RECIPIENT_MAX) {
        return NWC24_ERR_INVALID_VALUE;
    }

    subject = (const char*)msg->subject.ptr;
    if (subject != NULL) {
        const char* p = subject;

        while (*p != '\0') {
            if ((p[0] == '\r' && p[1] != '\n')) {
                return NWC24_ERR_FORMAT;
            }

            if (p[0] == '\n' && p[1] != ' ') {
                return NWC24_ERR_FORMAT;
            }

            p++;
        }
    }

    if (msg->numAttached > NWC24_MSG_ATTACHMENT_MAX) {
        return NWC24_ERR_INVALID_VALUE;
    }

    return NWC24_OK;
}

NWC24Err CheckMsgBoxSpace(NWC24MsgObj* msg, u32 requiredSize) {
    u32 textSize;
    u32 totalSize = 0;
    int i;
    NWC24Err result;
    NWC24Err err;

    for (i = 0; i < (int)msg->numAttached; i++) {
        totalSize += ((((msg->attachedSize[i] * 4) + 2) / 3) + ((msg->attachedSize[i] / 57) * 2)) + 4;
    }

    switch (msg->encoding) {
        case NWC24_ENC_7BIT:
        case NWC24_ENC_8BIT:
            textSize = msg->text.size;
            break;

        case NWC24_ENC_BASE64:
            textSize = ((((msg->text.size * 4) + 2) / 3) + ((msg->text.size / 57) * 2)) + 4;
            break;

        case NWC24_ENC_QUOTED_PRINTABLE:
            textSize = (msg->text.size * 4) / 3;
            break;

        default:
            textSize = 0;
            break;
    }

    totalSize += textSize;

    if (totalSize >= 0x31c00) {
        return -8;
    }

    err = NWC24iMBoxCheck(requiredSize, totalSize + NWC24_WORK_BUFFER_SIZE);

    result = 0;
    if (err != 0) {
        result = err;
    }

    return result;
}

NWC24Err SynthesizeAddrStr(NWC24AddrId* id_pair, u32 flags, char* out_buffer, int buffer_size, u32* out_length) {
    s32 domain_len;
    char id_str[20];
    NWC24Err result = 0;
    const char* domain;

    if ((flags & 1) != 0) {
        domain = NWC24GetAccountDomain();
        domain_len = Mail_strlen(domain);

        if (domain_len <= 0) {
            result = NWC24_ERR_CONFIG;
            goto cleanup;
        }

        if ((domain_len + 0x12) >= buffer_size) {
            result = NWC24_ERR_NOMEM;
            goto cleanup;
        }

        NWC24iConvIdToStr(id_pair->id, id_str);
        domain_len = Mail_sprintf(out_buffer, "%c%s%s", 0x77, id_str, domain);

        if (domain_len == 0) {
            result = NWC24_ERR_FATAL;
            goto cleanup;
        }

        *out_length = domain_len;

    } else if ((flags & 2) != 0) {
        if ((id_pair->data.size + 3) >= buffer_size) {
            result = NWC24_ERR_NOMEM;
            goto cleanup;
        }

        domain_len = Mail_sprintf(out_buffer, "%s", id_pair->data.ptr);

        if (domain_len == 0) {
            result = NWC24_ERR_FATAL;
            goto cleanup;
        }

        *out_length = domain_len;

    } else {
        result = NWC24_ERR_INVALID_VALUE;
    }

cleanup:
    return result;
}

NWC24Err WriteSMTP_MAILFROM(NWC24MsgObj* msg) {
    NWC24Err err;
    char* workp;
    u32 addrType;
    u32 addrLen;
    int totalLen;

    workp = NWC24WorkP->stringWork;

    Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_strncat(workp, "MAIL FROM:<", 0x3fe);

    workp += 11;

    addrType = 1;
    if (msg->flags & 0x100000ULL) {
        addrType = 2;
    }

    err = SynthesizeAddrStr((NWC24AddrId*)&msg->fromId, addrType, workp, 0x3fe, &addrLen);
    if (err != NWC24_OK) {
        return err;
    }

    workp += addrLen;
    *workp++ = '\r';
    *workp++ = '\n';

    totalLen = addrLen + 13;

    if ((0x3fe - totalLen) <= 0) {
        return NWC24_ERR_NOMEM;
    }

    if (err == NWC24_OK) {
        err = NWC24FWrite(NWC24WorkP->stringWork, totalLen, m_pFile);
        if (err == NWC24_OK) {
            msg->length += totalLen;
        }
    }

    return err;
}

NWC24Err WriteSMTP_RCPTTO(NWC24MsgObj* msg) {
    char* workp;
    u32 i;
    u32 totalLen;
    int remainSize;
    NWC24Err err;

    workp = NWC24WorkP->stringWork;
    totalLen = 0;
    err = NWC24_OK;

    Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
    remainSize = 0x3fe;

    for (i = 0; i < msg->numTo; i++) {
        u32 addrLen;

        Mail_strncat(workp, "RCPT TO:<", remainSize);
        workp += 9;

        err = SynthesizeAddrStr((NWC24AddrId*)&msg->toIds[i], msg->flags, workp, remainSize, &addrLen);
        if (err != NWC24_OK) {
            break;
        }

        workp += addrLen;
        *workp++ = '\r';
        *workp++ = '\n';

        remainSize -= (addrLen + 11);
        totalLen += (addrLen + 11);

        if (remainSize <= 0) {
            err = NWC24_ERR_NOMEM;
            break;
        }
    }

    if (err == NWC24_OK) {
        err = NWC24FWrite(NWC24WorkP->stringWork, totalLen, m_pFile);
        if (err == NWC24_OK) {
            msg->length += totalLen;
        }
    }

    return err;
}

NWC24Err WriteFromField(NWC24MsgObj* msg) {
    char* workp;
    u32 addrType;
    u32 addrLen;
    NWC24Err err;
    int totalLen;

    workp = NWC24WorkP->stringWork;

    Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_strncat(workp, "From: ", 0x3fe);

    workp += 6;
    msg->DATA_0x30.ptr = (void*)(msg->length + 6);

    addrType = 1;
    if (msg->flags & 0x100000ULL) {
        addrType = 2;
    }

    err = SynthesizeAddrStr((NWC24AddrId*)&msg->fromId, addrType, workp, 0x3fe, &addrLen);
    if (err != NWC24_OK) {
        return err;
    }

    workp += addrLen;
    *workp++ = '\r';
    *workp++ = '\n';

    totalLen = addrLen + 8;

    if (0x3fe - totalLen <= 0) {
        return NWC24_ERR_NOMEM;
    }

    if (err == NWC24_OK) {
        err = NWC24FWrite(NWC24WorkP->stringWork, totalLen, m_pFile);
        if (err == NWC24_OK) {
            msg->length += totalLen;
            msg->DATA_0x30.size = ((int)(msg->length - (u32)msg->DATA_0x30.ptr)) - 2;
        }
    }

    return err;
}

NWC24Err WriteToField(NWC24MsgObj* msg) {
    NWC24AddrId* toId;
    char* workp;
    int i;
    int totalLen;
    int remainSize;
    u32 len;
    NWC24Err err;

    workp = NWC24WorkP->stringWork;
    err = NWC24_OK;

    Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_strncat(workp, "To: ", NWC24_WORK_BUFFER_SIZE);

    workp += 4;
    toId = (NWC24AddrId*)&msg->toIds[0];
    i = 0;
    totalLen = 4;
    remainSize = 0x3FC;

    *(u32*)&msg->DATA_0x38.ptr = msg->length + 4;

    while (i < msg->numTo) {
        err = SynthesizeAddrStr(toId, msg->flags, workp, remainSize, &len);
        if (err != NWC24_OK) {
            break;
        }

        remainSize -= len;
        workp += len;
        totalLen += len;

        if (remainSize <= 4) {
            err = -11;
            break;
        }

        if (i < msg->numTo - 1) {
            *workp++ = ',';
            *workp++ = '\r';
            *workp++ = '\n';
            *workp++ = ' ';
            totalLen += 4;
            remainSize -= 4;
        }

        toId++;
        i++;
    }

    *workp++ = '\r';
    *workp++ = '\n';
    totalLen += 2;

    if (err == NWC24_OK) {
        err = NWC24FWrite(NWC24WorkP, totalLen, m_pFile);
        if (err == NWC24_OK) {
            msg->length += totalLen;
            msg->DATA_0x38.size = ((int) (msg->length - (*((u32 *) (&msg->DATA_0x38.ptr))))) - 2;
        }
    }

    return err;
}

NWC24Err WriteDateField(NWC24MsgObj* msg) {
    char* workp;
    NWC24Date date;
    u32 len;
    NWC24Err err;
    NWC24Calendar cal;

    NWC24Date_Init(&date);
    NETGetUniversalCalendar((u8*)&cal);

    date.year  = cal.year;
    date.month = cal.month + 1;
    date.day   = cal.day;
    date.hour  = cal.hour;
    date.min   = cal.min;
    date.sec   = cal.sec;

    if (date.month > 12) {
        return NWC24_ERR_FORMAT;
    }

    workp = NWC24WorkP->stringWork;
    Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);

    len = Mail_sprintf(workp, "Date: %02d %s %d %02d:%02d:%02d +0000\r\n", date.day, MonthStr[date.month - 1], date.year, date.hour, date.min, date.sec);

    NWC24iDateToMinutes(&msg->createTime, &date);
    len = Mail_strlen(workp);

    err = NWC24FWrite(workp, len, m_pFile);
    if (err == NWC24_OK) {
        msg->length += len;
    }

    return err;
}

NWC24Err WriteXWiiAppIdField(NWC24MsgObj* msg) {
    char* workp = NWC24WorkP->stringWork;
    char tempbuf[16];
    u32 flags = 0;
    u32 len;

    Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_strcpy(workp, "X-Wii-AppId: ");

    if (NWC24IsMsgLibOpenedByTool() == 0) {
        if (NWC24GetAppId() != 0x48414541) {
            msg->appId = NWC24GetAppId();
        }
    }

    if (msg->flags & 0x4) {
        flags |= 1;
    }
    if (msg->flags & 0x8) {
        flags |= 2;
    }

    Mail_memset(tempbuf, 0, 0x10);
    Mail_sprintf(tempbuf, "%d-%08x-%04x", flags, msg->appId, msg->groupId);
    Mail_strcat(workp, tempbuf);

    len = Mail_strlen(workp);
    if (NWC24FWrite(workp, len, m_pFile) == NWC24_OK) {
        msg->length += len;
    }
}

NWC24Err WriteXWiiFaceField(NWC24MsgObj* msg) {
    char* workp;
    const u8* dataPtr;
    u32 currentOffset = 0;
    NWC24Err err = NWC24_OK;
    u32 encodedLen;
    s32 remainSize;
    s32 chunkSize;

    if (msg->face.size == 0) {
        return NWC24_OK;
    }

    workp = NWC24WorkP->stringWork;

    Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_strcpy(workp, "X-Wii-Face:");
    currentOffset = 10;
    dataPtr = (const u8*)msg->face.ptr;
    remainSize = msg->face.size;

    while (remainSize > 0) {
        workp[currentOffset++] = ' ';
        chunkSize = remainSize;
        if (remainSize > 42) {
            chunkSize = 42;
        }

        err = NWC24Base64Encode((char*)dataPtr, chunkSize, workp + currentOffset, 76, &encodedLen);

        dataPtr += chunkSize;
        remainSize -= chunkSize;
        currentOffset += encodedLen;

        workp[currentOffset++] = '\r';
        workp[currentOffset++] = '\n';
    }

    err = NWC24FWrite(workp, currentOffset, m_pFile);
    if (err == NWC24_OK) {
        msg->length += currentOffset;
    }

    return err;
}

NWC24Err WriteXWiiAltNameField(NWC24MsgObj* msg) {
    char* workp;
    const u8* dataPtr;
    u32 currentOffset = 0;
    NWC24Err err = NWC24_OK;
    u32 encodedLen;
    s32 remainSize;
    s32 chunkSize;

    if (msg->alt.size == 0) {
        return NWC24_OK;
    }

    workp = NWC24WorkP->stringWork;

    Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
    Mail_strcpy(workp, "X-Wii-AltName:");
    currentOffset = 14;
    dataPtr = (const u8*)msg->alt.ptr;
    remainSize = msg->alt.size;

    while (remainSize > 0) {
        workp[currentOffset++] = ' ';
        chunkSize = remainSize;
        if (remainSize > 42) {
            chunkSize = 42;
        }

        err = NWC24Base64Encode((char*)dataPtr, chunkSize, workp + currentOffset, 76, &encodedLen);

        dataPtr += chunkSize;
        remainSize -= chunkSize;
        currentOffset += encodedLen;

        workp[currentOffset++] = '\r';
        workp[currentOffset++] = '\n';
    }

    err = NWC24FWrite(workp, currentOffset, m_pFile);
    if (err == NWC24_OK) {
        msg->length += currentOffset;
    }

    return err;
}

NWC24Err WriteMIMEAttachHeader(NWC24MsgObj* msg, u32 attachIndex) {
    char* workp;
    const char* mimeTypeStr;
    const char* mimeSuffix;
    s32 written;
    s32 totalWritten = 0;
    NWC24Err err;

    Mail_memset(NWC24WorkP->stringWork, 0, NWC24_WORK_BUFFER_SIZE);
    workp = NWC24WorkP->stringWork;

    mimeTypeStr = NWC24GetMIMETypeStr(msg->attachedType[attachIndex]);
    mimeSuffix = NWC24iGetMIMETypeSuffix(msg->attachedType[attachIndex]);

    written = Mail_strlen(ContentTypeA) + Mail_strlen(ContentTxEncA) + Mail_strlen(ContentDispA) + Mail_strlen(mimeTypeStr) + 4;

    if (written >= NWC24_WORK_BUFFER_SIZE) {
        return NWC24_ERR_NOMEM;
    }

    written = Mail_sprintf(workp, ContentTypeA, mimeTypeStr, (char)('a' + attachIndex), msg->id, mimeSuffix);;
    if (written <= 0) {
        return NWC24_ERR_FAILED;
    }
    workp += written;
    totalWritten += written;

    written = Mail_sprintf(workp, ContentTxEncA);
    if (written <= 0) {
        return NWC24_ERR_FAILED;
    }
    workp += written;
    totalWritten += written;

    written = Mail_sprintf(workp, ContentDispA, (char)('a' + attachIndex), msg->id, mimeSuffix);
    if (written <= 0) {
        return NWC24_ERR_FAILED;
    }
    workp += written;
    totalWritten += written;

    err = NWC24FWrite(NWC24WorkP->stringWork, totalWritten, m_pFile);
    if (err == NWC24_OK) {
        msg->length += totalWritten;
    }

    return err;
}

NWC24Err WriteContentTypeField(NWC24MsgObj* msg) {
    char* work = NWC24WorkP->stringWork;
    const char* charset;
    const char* encoding;
    u32 total = 0;
    NWC24Err err = NWC24_OK;

    Mail_memset(work, 0, NWC24_WORK_BUFFER_SIZE);

    charset = NWC24GetCharsetStr(msg->charset);
    if (charset != NULL) {
        int clen = 0;

        Mail_sprintf(work, ContentTypeTP, charset);

        msg->contentType.ptr = (void*)(msg->length + 0x22);

        clen = Mail_strlen(charset);
        msg->contentType.size = clen + 1;

        clen = Mail_strlen(work);
        total += clen;
        work += clen;
    }

    encoding = NWC24GetEncodingStr(msg->encoding);
    if (encoding != NULL) {
        int elen = 0;

        Mail_sprintf(work, ContentTxEncT, encoding);

        msg->transferEncoding.ptr = (void*)(msg->length + total + 0x1b);

        elen = Mail_strlen(encoding);
        msg->transferEncoding.size = elen + 1;

        elen = Mail_strlen(work);
        total += elen;
    }

    if (total == 0) {
        err = NWC24_OK;
    } else {
        err = NWC24FWrite(NWC24WorkP->stringWork, total, m_pFile);
        if (err == NWC24_OK) {
            msg->length += total;
        }
    }

    return err;
}

NWC24Err WritePlainText(NWC24MsgObj* msg) {
    NWC24Err err = NWC24_OK;
    u32 bytesWritten;

    if (msg->text.size == 0) {
        return NWC24_ERR_NULL;
    }

    switch (msg->encoding) {
        case NWC24_ENC_7BIT:
        case NWC24_ENC_8BIT:
            err = NWC24FWrite(msg->text.ptr, msg->text.size, m_pFile);
            bytesWritten = msg->text.size;
            break;
        case NWC24_ENC_BASE64:
            err = WriteBase64Data(msg->text.ptr, msg->text.size, &bytesWritten);
            break;
        case NWC24_ENC_QUOTED_PRINTABLE:
            err = WriteQPData(msg->text.ptr, msg->text.size, &bytesWritten);
            break;
        default:
            err = NWC24_ERR_INVALID_VALUE;
            break;
    }

    if (err == NWC24_OK) {
        msg->altMeta.ptr = (const void *)msg->text.size;
        msg->length += bytesWritten;
    }

    return err;
}

NWC24Err WriteBase64Data(const void* data, u32 size, u32* bytesWritten) {
    char* workp = NWC24WorkP->stringWork;
    const u8* dataPtr = (const u8*)data;
    int remainSize = size;
    int totalWritten = 0;
    NWC24Err err = NWC24_OK;
    u32 encodedLen;

    while (remainSize >= 57) {
        Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
        err = NWC24Base64Encode((char*)dataPtr, 57, workp, 76, &encodedLen);
        if (err != NWC24_OK) {
            break;
        }

        workp[encodedLen++] = '\r';
        workp[encodedLen++] = '\n';
        workp[encodedLen] = '\0';

        err = NWC24FWrite(workp, encodedLen, m_pFile);
        if (err != NWC24_OK) {
            break;
        }

        dataPtr += 57;
        remainSize -= 57;
        totalWritten += encodedLen;
    }

    if (err == NWC24_OK) {
        Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
        err = NWC24Base64Encode((char*)dataPtr, remainSize, workp, 76, &encodedLen);
        if (err == NWC24_OK) {
            workp[encodedLen++] = '\r';
            workp[encodedLen++] = '\n';
            workp[encodedLen++] = '\r';
            workp[encodedLen++] = '\n';
            workp[encodedLen] = '\0';

            err = NWC24FWrite(workp, encodedLen, m_pFile);
            if (err == NWC24_OK) {
                totalWritten += encodedLen;
            }
        }
    }

    *bytesWritten = totalWritten;
    return err;
}

NWC24Err WriteQPData(const void* data, u32 size, u32* bytesWritten) {
    char* workp = NWC24WorkP->stringWork;
    const u8* dataPtr = (const u8*)data;
    int remainSize = size;
    int totalWritten = 0;
    NWC24Err err = NWC24_OK;

    while (remainSize > 0) {
        u32 consumed;
        u32 written;

        if (totalWritten > 0) {
            Mail_memcpy(workp, "=\r\n", 3);
            err = NWC24FWrite(workp, 3, m_pFile);
            if (err != NWC24_OK) {
                break;
            }
            totalWritten += 3;
        }

        Mail_memset(workp, 0, NWC24_WORK_BUFFER_SIZE);
        err = NWC24EncodeQuotedPrintable((u8*)workp, NWC24_WORK_BUFFER_SIZE, &written, (u8*)dataPtr, remainSize, &consumed);
        
        if (err != NWC24_OK) {
            if (err != NWC24_ERR_OVERFLOW) {
                break;
            }
        }
        
        err = NWC24FWrite(workp, written, m_pFile);
        if (err != NWC24_OK) {
            break;
        }

        dataPtr += consumed;
        remainSize -= consumed;
        totalWritten += written;
    }

    *bytesWritten = totalWritten;
    return err;
}
