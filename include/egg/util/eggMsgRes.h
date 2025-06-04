#ifndef EGG_UTIL_MSG_RES_H
#define EGG_UTIL_MSG_RES_H
#include <egg/types_egg.h>

#include <egg/prim.h>

namespace EGG {

class MsgRes {
protected:
    enum EDataBlkKind {
        DATABLK_MSGINFO,
        DATABLK_MSGDATA,
        DATABLK_STRATTR,
        DATABLK_MSGID,
        DATABLK_FLOWCHART,
        DATABLK_FLOWLABEL,
        DATABLK_MAX
    };

    struct DataBlockHeader {
        u32 mSignature; // at 0x0
        u32 mType;      // at 0x4
        u32 mDataSize;  // at 0x8
        u32 mNumBlocks; // at 0xC
    };

    struct DataBlock {
        u32 mKind;     // at 0x0
        u32 mDataSize; // at 0x4
    };

    struct MessageHeader : DataBlockHeader {
        enum EEncoding {
            ENCODING_1BYTE,
            ENCODING_2BYTE,
            ENCODING_SJIS,
            ENCODING_UTF8,
        };

        u8 mEncoding; // at 0x10
        char UNK_0x11[0x20 - 0x11];
    };

    struct MessageInfoDataBlock : DataBlock {
        struct Entry {
            u32 mDataOffset; // at 0x0
            u32 mAttribute;  // at 0x4
        };

        u16 mNumEntries;   // at 0x8
        u16 mEntrySize;    // at 0xA
        u16 mGroupID;      // at 0xC
        Entry mContent[1]; // at 0x10
    };

    struct MessageDataBlock : DataBlock {
        wchar_t mContent[1]; // at 0x8
    };

    struct StringAttributeDataBlock : DataBlock {};

    struct MessageIDDataBlock : DataBlock {
        u16 mNumEntries;    // at 0x8
        u8 mForm;           // at 0xA
        u8 mFormSupplement; // at 0xB
        char UNK_0xC[0x10 - 0xC];
        u32 mContent[]; // at 0x10
    };

    struct FlowChartInfoDataBlock : DataBlock {};

    struct FlowLabelInfoDataBlock : DataBlock {};

    static const u16 cTagMark = '\x1A';
    static const u32 cDataBlkKindCodeSet[DATABLK_MAX];

    static const u32 cFormSupplementMax = 5;
    struct MsgIDMask {
        u32 groupMask; // at 0x0
        u32 indexMask; // at 0x4
    };
    static const u32 cMainMsgIdBitNumSet[cFormSupplementMax];
    static const MsgIDMask cMsgIdMaskSet[cFormSupplementMax];

private:
    const MessageHeader* mMsgHeader;                // at 0x0
    const MessageInfoDataBlock* mMsgInfoDataBlk;    // at 0x4
    const MessageDataBlock* mMsgDataBlk;            // at 0x8
    const StringAttributeDataBlock* mMsgStrDataBlk; // at 0xC
    const MessageIDDataBlock* mMsgIDDataBlk;        // at 0x10
    const FlowChartInfoDataBlock* mMsgFlowChartBlk; // at 0x14
    const FlowLabelInfoDataBlock* mMsgFlowLabelBlk; // at 0x18

public:
    MsgRes(const void* pData);
    virtual ~MsgRes(); // at 0x8

    const wchar_t* getMsg(u32 group, u32 idx);

    static void analyzeTag(u16 code, const wchar_t* pTag, u8* pTagLength,
                           u32* pTagID, void** ppParam);

protected:
    const MessageInfoDataBlock::Entry* getMsgEntry(u32 group, u32 idx);
    u32 getMsgID(u16 idx);

private:
    u32 getDataBlkKind(const void* data) {
#line 271
        EGG_ASSERT(data);
        return static_cast<const DataBlock*>(data)->mKind;
    }

    u32 getDataBlkSize(const void* dataBlkHeader) {
#line 260
        EGG_ASSERT(dataBlkHeader);
        return static_cast<const DataBlock*>(dataBlkHeader)->mDataSize;
    }

    void extractMsgHeader(const void* pData);
    void extractMsgInfoDataBlk(const void* pData);
    void extractMsgDataBlk(const void* pData);
    void extractStrAttrDataBlk(const void* pData);
    void extractMsgIDDataBlk(const void* pData);
    void extractFlowChartInfoDataBlk(const void* pData);
    void extractFlowLabelInfoDataBlk(const void* pData);

    EDataBlkKind analyzeDataBlkKind(u32 kind);
};

} // namespace EGG

#endif
