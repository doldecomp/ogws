// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/prim.h>
#include <egg/util.h>

namespace EGG {

const u32 MsgRes::cDataBlkKindCodeSet[DATABLK_MAX] = {
    FOURCC('I', 'N', 'F', '1'), // DATABLK_MSGINFO
    FOURCC('D', 'A', 'T', '1'), // DATABLK_MSGDATA
    FOURCC('S', 'T', 'R', '1'), // DATABLK_STRATTR
    FOURCC('M', 'I', 'D', '1'), // DATABLK_MSGID
    FOURCC('F', 'L', 'W', '1'), // DATABLK_FLOWCHART
    FOURCC('F', 'L', 'I', '1')  // DATABLK_FLOWLABEL
};

const u32 MsgRes::cMainMsgIdBitNumSet[cFormSupplementMax] = {
    32, 24, 16, 8, 0,
};

const MsgRes::MsgIDMask MsgRes::cMsgIdMaskSet[cFormSupplementMax] = {
    {0xFFFFFFFF, 0x00000000}, {0xFFFFFF00, 0x000000FF},
    {0xFFFF0000, 0x0000FFFF}, {0xFF000000, 0x00FFFFFF},
    {0x00000000, 0xFFFFFFFF},
};

MsgRes::MsgRes(const void* data) {
#line 53
    EGG_ASSERT(data);

    mMsgHeader = NULL;
    mMsgInfoDataBlk = NULL;
    mMsgDataBlk = NULL;
    mMsgStrDataBlk = NULL;
    mMsgIDDataBlk = NULL;
    mMsgFlowChartBlk = NULL;
    mMsgFlowLabelBlk = NULL;

    extractMsgHeader(data);

    const void* current = static_cast<const u8*>(data) + sizeof(MessageHeader);
    u32 numBlocks = mMsgHeader->mNumBlocks;

    for (int i = 0; i < numBlocks; i++) {
#line 77
        EGG_ASSERT(( u32 )data + mMsgHeader->mDataSize > ( u32 )current);

        EDataBlkKind kind = analyzeDataBlkKind(getDataBlkKind(current));
        const DataBlock* pDataBlk = NULL;

        switch (kind) {
        case DATABLK_MSGINFO: {
            extractMsgInfoDataBlk(current);
            pDataBlk = static_cast<const MessageInfoDataBlock*>(current);
            break;
        }

        case DATABLK_MSGDATA: {
            extractMsgDataBlk(current);
            pDataBlk = static_cast<const MessageDataBlock*>(current);
            break;
        }

        case DATABLK_STRATTR: {
            extractStrAttrDataBlk(current);
            pDataBlk = static_cast<const StringAttributeDataBlock*>(current);
            break;
        }

        case DATABLK_MSGID: {
            extractMsgIDDataBlk(current);
            pDataBlk = static_cast<const MessageIDDataBlock*>(current);
            break;
        }

        case DATABLK_FLOWCHART: {
            extractFlowChartInfoDataBlk(current);
            pDataBlk = static_cast<const FlowChartInfoDataBlock*>(current);
            break;
        }

        case DATABLK_FLOWLABEL: {
            extractFlowLabelInfoDataBlk(current);
            pDataBlk = static_cast<const FlowLabelInfoDataBlock*>(current);
            break;
        }

        default: {
#line 125
            EGG_ASSERT_MSG(false, "Illegal data block.\n");
            break;
        }
        }

        current = static_cast<const u8*>(current) + getDataBlkSize(pDataBlk);
    }
}

MsgRes::~MsgRes() {}

void MsgRes::analyzeTag(u16 code, const wchar_t* tag, u8* tagLength, u32* tagID,
                        void** param) {
#line 159
    EGG_ASSERT(tag);
    EGG_ASSERT(tagLength);
    EGG_ASSERT(tagID);
    EGG_ASSERT(param);

#line 164
    EGG_ASSERT(cTagMark == code);

    *tagLength = *reinterpret_cast<const u8*>(tag) - 2;
    *tagID = *reinterpret_cast<const u32*>(tag) & 0x00FFFFFF;

    if (*tagLength > 4) {
        *param = const_cast<wchar_t*>(tag + 2);
    } else {
        *param = NULL;
    }
}

const wchar_t* MsgRes::getMsg(u32 group, u32 idx) {
#line 189
    EGG_ASSERT(mMsgDataBlk);

    const MessageInfoDataBlock::Entry* pEntry = getMsgEntry(group, idx);
#line 193
    EGG_ASSERT_MSG(pEntry != NULL, "Not found message %d, %d.\n", group, idx);

    return reinterpret_cast<const wchar_t*>(
        reinterpret_cast<const u8*>(mMsgDataBlk->mContent) +
        pEntry->mDataOffset);
}

void MsgRes::extractMsgHeader(const void* data) {
#line 223
    EGG_ASSERT(data);
    mMsgHeader = static_cast<const MessageHeader*>(data);
}

void MsgRes::extractMsgInfoDataBlk(const void* data) {
#line 251
    EGG_ASSERT(data);
    mMsgInfoDataBlk = static_cast<const MessageInfoDataBlock*>(data);
}

void MsgRes::extractMsgDataBlk(const void* data) {
#line 277
    EGG_ASSERT(data);
    mMsgDataBlk = static_cast<const MessageDataBlock*>(data);
}

void MsgRes::extractStrAttrDataBlk(const void* data) {
#line 298
    EGG_ASSERT(data);
    mMsgStrDataBlk = static_cast<const StringAttributeDataBlock*>(data);
}

void MsgRes::extractMsgIDDataBlk(const void* data) {
#line 309
    EGG_ASSERT(data);
    mMsgIDDataBlk = static_cast<const MessageIDDataBlock*>(data);
}

void MsgRes::extractFlowChartInfoDataBlk(const void* data) {
#line 334
    EGG_ASSERT(data);
    mMsgFlowChartBlk = static_cast<const FlowChartInfoDataBlock*>(data);
}

void MsgRes::extractFlowLabelInfoDataBlk(const void* data) {
#line 345
    EGG_ASSERT(data);
    mMsgFlowLabelBlk = static_cast<const FlowLabelInfoDataBlock*>(data);
}

MsgRes::EDataBlkKind MsgRes::analyzeDataBlkKind(u32 kind) {
    for (int i = 0; i < DATABLK_MAX; i++) {
        if (kind == cDataBlkKindCodeSet[i]) {
            return static_cast<EDataBlkKind>(i);
        }
    }

#line 366
    EGG_ASSERT_MSG(false, "Illegal data block.\n");
    return DATABLK_MAX;
}

const MsgRes::MessageInfoDataBlock::Entry* MsgRes::getMsgEntry(u32 group,
                                                               u32 idx) {
#line 380
    EGG_ASSERT(mMsgInfoDataBlk);
    EGG_ASSERT(mMsgIDDataBlk);

    u32 idBitNum = 32 - cMainMsgIdBitNumSet[mMsgIDDataBlk->mFormSupplement];
    const MsgIDMask& rMask = cMsgIdMaskSet[mMsgIDDataBlk->mFormSupplement];

    for (u16 i = 0; i < mMsgIDDataBlk->mNumEntries; i++) {
        u32 msgId = getMsgID(i);

        if (group == (msgId & rMask.groupMask) >> idBitNum &&
            idx == (msgId & rMask.indexMask)) {

#line 402
            EGG_ASSERT(mMsgInfoDataBlk->mNumEntries > i);

            return reinterpret_cast<const MessageInfoDataBlock::Entry*>(
                reinterpret_cast<const u8*>(mMsgInfoDataBlk->mContent) +
                mMsgInfoDataBlk->mEntrySize * i);
        }
    }

    return NULL;
}

u32 MsgRes::getMsgID(u16 idx) {
#line 425
    EGG_ASSERT(mMsgIDDataBlk);
    return mMsgIDDataBlk->mContent[idx];
}

} // namespace EGG
