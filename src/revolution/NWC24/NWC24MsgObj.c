#include <RVLFaceLib.h>

#include <revolution/NWC24.h>
#include <revolution/NWC24/NWC24Internal.h>

#define MSG_YEAR_MIN 2000
#define MSG_YEAR_MAX 2035 // !!!

#define ALT_NAME_MAX 35
#define SMTP_LINE_MAX 1000

NWC24Err NWC24InitMsgObj(NWC24MsgObj* pMsg, NWC24MsgType type) {
    u32 i;
    NWC24iMsgObj* pMsgImpl;

    pMsgImpl = (NWC24iMsgObj*)pMsg;
    Mail_memset(pMsgImpl, 0, sizeof(NWC24iMsgObj));

    pMsgImpl->id = 0;
    pMsgImpl->flags = NWC24_MSGOBJ_INITIALIZED;
    pMsgImpl->appId = NWC24GetAppId();
    pMsgImpl->command = 0;
    pMsgImpl->tag = 0;
    pMsgImpl->groupId = NWC24GetGroupId();

    switch (type) {
    case NWC24_MSGTYPE_RVL_MENU_SHARED: {
        pMsgImpl->flags |= NWC24_MSGOBJ_FOR_RECIPIENT | NWC24_MSGOBJ_FOR_APP |
                           NWC24_MSGOBJ_FOR_MENU;
        break;
    }

    case NWC24_MSGTYPE_RVL: {
        pMsgImpl->flags |= NWC24_MSGOBJ_FOR_RECIPIENT | NWC24_MSGOBJ_FOR_APP;
        break;
    }

    case NWC24_MSGTYPE_RVL_MENU: {
        pMsgImpl->flags |= NWC24_MSGOBJ_FOR_RECIPIENT | NWC24_MSGOBJ_FOR_MENU;
        break;
    }

    case NWC24_MSGTYPE_RVL_HIDDEN: {
        pMsgImpl->flags |= NWC24_MSGOBJ_FOR_RECIPIENT;
        break;
    }

    case NWC24_MSGTYPE_PUBLIC: {
        pMsgImpl->flags |= NWC24_MSGOBJ_FOR_PUBLIC;
        break;
    }

    default: {
        return NWC24_ERR_INVALID_VALUE;
    }
    }

    pMsgImpl->createTime = 0;
    pMsgImpl->unk2C = 0;
    NWC24GetMyUserId(&pMsgImpl->from.id);
    pMsgImpl->numTo = 0;

    for (i = 0; i < NWC24i_MSG_RECIPIENT_MAX; i++) {
        if (type == NWC24_MSGTYPE_PUBLIC) {
            NWC24Data_Init(&pMsgImpl->to[i].data);
        } else {
            pMsgImpl->to[i].id = 0;
        }
    }

    NWC24Data_Init(&pMsgImpl->subject);
    NWC24Data_Init(&pMsgImpl->text);
    pMsgImpl->charset = NWC24_US_ASCII;
    pMsgImpl->encoding = NWC24_ENC_7BIT;
    pMsgImpl->numAttached = 0;

    for (i = 0; i < NWC24i_MSG_ATTACHMENT_MAX; i++) {
        NWC24Data_Init(&pMsgImpl->attached[i]);
        pMsgImpl->attachedSize[i] = 0;
        pMsgImpl->attachedType[i] = NWC24_TEXT_PLAIN;
    }

    NWC24Data_Init(&pMsgImpl->fromField);
    NWC24Data_Init(&pMsgImpl->toField);
    NWC24Data_Init(&pMsgImpl->contentType);
    NWC24Data_Init(&pMsgImpl->txEncoding);
    NWC24Data_Init(&pMsgImpl->user);
    NWC24Data_Init(&pMsgImpl->face);
    NWC24Data_Init(&pMsgImpl->alt);
    pMsgImpl->msgBoard = 0;

    return NWC24_OK;
}

NWC24Err NWC24SetMsgToId(NWC24MsgObj* pMsg, u64 id) {
    NWC24iMsgObj* pMsgImpl = (NWC24iMsgObj*)pMsg;

    if (!(pMsgImpl->flags & NWC24_MSGOBJ_INITIALIZED) ||
        (pMsgImpl->flags & NWC24_MSGOBJ_DELIVERING)) {

        return NWC24_ERR_PROTECTED;
    }

    if (!(pMsgImpl->flags & NWC24_MSGOBJ_FOR_RECIPIENT)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (pMsgImpl->numTo >= NWC24i_MSG_RECIPIENT_MAX) {
        return NWC24_ERR_FULL;
    }

    pMsgImpl->to[pMsgImpl->numTo].id = id;
    pMsgImpl->numTo++;

    return NWC24_OK;
}

NWC24Err NWC24SetMsgText(NWC24MsgObj* pMsg, const char* pText, u32 len,
                         NWC24Charset charset, NWC24Encoding encoding) {
    NWC24iMsgObj* pMsgImpl = (NWC24iMsgObj*)pMsg;

    if (!(pMsgImpl->flags & NWC24_MSGOBJ_INITIALIZED) ||
        (pMsgImpl->flags & NWC24_MSGOBJ_DELIVERING)) {

        return NWC24_ERR_PROTECTED;
    }

    if (NWC24GetCharsetStr(charset) == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (NWC24GetEncodingStr(encoding) == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (pText == NULL) {
        NWC24Data_Init(&pMsgImpl->text);
        return NWC24_OK;
    }

    if (pText[len] != '\0') {
        return NWC24_ERR_STRING_END;
    }

    // Lines are limited to at most 1000 characters
    if (encoding == NWC24_ENC_7BIT || encoding == NWC24_ENC_8BIT) {
        u32 lineLength;
        const char* pIt;

        lineLength = 0;

        for (pIt = pText; pIt < pText + len; pIt++) {
            if (pIt[0] == '\r' && pIt[1] == '\n') {
                lineLength = 0;
                pIt++;
            }
            // Include "\r\n" in line length
            else if (++lineLength > SMTP_LINE_MAX - 2) {
                return NWC24_ERR_FORMAT;
            }
        }
    }

    NWC24Data_SetDataP(&pMsgImpl->text, pText, len);
    pMsgImpl->charset = charset;
    pMsgImpl->encoding = encoding;

    return NWC24_OK;
}

NWC24Err NWC24SetMsgFaceData(NWC24MsgObj* pMsg, const RFLCharData* pData) {
    NWC24iMsgObj* pMsgImpl = (NWC24iMsgObj*)pMsg;

    if (!(pMsgImpl->flags & NWC24_MSGOBJ_INITIALIZED) ||
        (pMsgImpl->flags & NWC24_MSGOBJ_DELIVERING)) {

        return NWC24_ERR_PROTECTED;
    }

    if (pMsgImpl->face.size > 0) {
        return NWC24_ERR_FULL;
    }

    NWC24Data_SetDataP(&pMsgImpl->face, pData, sizeof(RFLCharData));
    return NWC24_OK;
}

NWC24Err NWC24SetMsgAltName(NWC24MsgObj* pMsg, const wchar_t* pName, u32 len) {
    NWC24iMsgObj* pMsgImpl = (NWC24iMsgObj*)pMsg;

    if (!(pMsgImpl->flags & NWC24_MSGOBJ_INITIALIZED) ||
        (pMsgImpl->flags & NWC24_MSGOBJ_DELIVERING)) {

        return NWC24_ERR_PROTECTED;
    }

    if (pMsgImpl->alt.size > 0) {
        return NWC24_ERR_FULL;
    }

    if (len > ALT_NAME_MAX) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (pName == NULL || len <= 0) {
        return NWC24_ERR_NULL;
    }

    NWC24Data_SetDataP(&pMsgImpl->alt, pName, len * sizeof(wchar_t));
    return NWC24_OK;
}

NWC24Err NWC24SetMsgMBNoReply(NWC24MsgObj* pMsg, BOOL enable) {
    NWC24iMsgObj* pMsgImpl = (NWC24iMsgObj*)pMsg;

    if (!(pMsgImpl->flags & NWC24_MSGOBJ_INITIALIZED) ||
        (pMsgImpl->flags & NWC24_MSGOBJ_DELIVERING)) {

        return NWC24_ERR_PROTECTED;
    }

    if (!(pMsgImpl->flags & NWC24_MSGOBJ_FOR_MENU)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (enable) {
        NWC24i_MSGOBJ_SET_MB_NOREPLY(pMsgImpl, TRUE);
    } else {
        NWC24i_MSGOBJ_SET_MB_NOREPLY(pMsgImpl, FALSE);
    }

    return NWC24_OK;
}

NWC24Err NWC24SetMsgMBRegDate(NWC24MsgObj* pMsg, u16 year, u8 month, u8 day) {
    NWC24iMsgObj* pMsgImpl;
    NWC24Err result;
    u16 regdate;

    pMsgImpl = (NWC24iMsgObj*)pMsg;

    if (!(pMsgImpl->flags & NWC24_MSGOBJ_INITIALIZED) ||
        (pMsgImpl->flags & NWC24_MSGOBJ_DELIVERING)) {

        return NWC24_ERR_PROTECTED;
    }

    if (!(pMsgImpl->flags & NWC24_MSGOBJ_FOR_MENU)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (year < MSG_YEAR_MIN || year > MSG_YEAR_MAX) {
        return NWC24_ERR_INVALID_VALUE;
    }

    result = NWC24iIsValidDate(year, month, day);
    if (result != NWC24_OK) {
        return result;
    }

    regdate = (year - MSG_YEAR_MIN) << 9 | month << 5 | day;
    NWC24i_MSGOBJ_SET_MB_REGDATE(pMsgImpl, regdate);

    return NWC24_OK;
}
