#ifndef EGG_UTIL_MSGRES_H
#define EGG_UTIL_MSGRES_H
#include "types_egg.h"
#include "eggAssert.h"

namespace EGG
{
    // Escape sequence (Official name = "Tag")
    const char cTagMark = 0x1A;
    const u32 cMsgSectionMagic[] = {'INF1', 'DAT1', 'STR1', 'MID1', 'FLW1', 'FLI1'};
    const u32 cShifts[]          = {0x00000020, 0x00000018, 0x00000010, 0x00000008, 0x00000000, 0x00000000};

    struct MaskUnk
    {
        u32 INT_0x0;
        u32 INT_0x4;
    };
    const MaskUnk cMasks[] = {{0xffffffff, 0x00000000}, {0xffffff00, 0x000000ff}, {0xffff0000, 0x0000ffff}, {0xff000000, 0x00ffffff}, {0x00000000, 0xffffffff}};

    struct MsgRes
    {
        struct MsgHeaderBlock
        {   u32 mMagicTop; // "MESG", at 0x0
            u32 mMagicBot; // "bmg1", at 0x4
            u32 mDataSize; // at 0x8
            u32 mNumBlocks; // at 0xC
            u8 mEncoding; // at 0x10
            u8 UNK_0x11[3];
            UNKWORD WORD_0x14;
            UNKWORD WORD_0x18;
            UNKWORD WORD_0x1C;
        };

        struct MsgInfoBlockEntry
        {
            u32 mDataBlkOfs; // at 0x0
            u32 mAttrib; // at 0x4
        };

        struct MsgInfoBlock
        {
            u32 mMagic; // at 0x0
            u32 mDataSize; // at 0x4
            u16 mNumEntries; // at 0x8
            u16 mItemSize; // at 0xA
            u16 SHORT_0xC;
            u8 UNK_0xE;
            u8 UNK_0xF;
            MsgInfoBlockEntry mMsgInfo[]; // at 0x10
        };

        struct MsgDataBlock
        {
            u32 mMagic; // at 0x0
            u32 mDataSize; // at 0x4
            wchar_t mStringPool[]; // at 0x8
        };

        struct MsgStrAttrBlock
        {
            u32 mMagic; // at 0x0
            u32 mDataSize; // at 0x4
            // TO-DO
        };

        struct MsgIdBlock
        {
            u32 mMagic; // at 0x0
            u32 mDataSize; // at 0x4
            u16 mNumEntries; // at 0x8
            u8 UNK_0xA;
            u8 UNK_0xB;
            u32 WORD_0xC;
            u32 mMsgIds[]; // at 0x10
        };

        struct MsgFlowChartBlock
        {
            u32 mMagic; // at 0x0
            u32 mDataSize; // at 0x4
            // TO-DO
        };

        struct MsgFlowLabelBlock
        {
            u32 mMagic; // at 0x0
            u32 mDataSize; // at 0x4
            // TO-DO
        };

        enum EDataBlkKind
        {
            BLOCK_MSGINFO,   /* INF1 */
            BLOCK_MSGDATA,   /* DAT1 */
            BLOCK_STRATTR,   /* STR1 */
            BLOCK_MSGID,     /* MID1 */
            BLOCK_FLOWCHART, /* FLW1 */
            BLOCK_FLOWLABEL, /* FLI1 */
            BLOCK_ILLEGAL
        };

        MsgHeaderBlock *mMsgHeader;          // "MESGbmg1", at 0x0
        MsgInfoBlock *mMsgInfoDataBlk;       // "INF1", at 0x4
        MsgDataBlock *mMsgDataBlk;           // "DAT1", at 0x8
        MsgStrAttrBlock *mMsgStrDataBlk;     // "STR1", at 0xC
        MsgIdBlock *mMsgIDDataBlk;           // "MID1", at 0x10
        MsgFlowChartBlock *mMsgFlowChartBlk; // "FLW1", at 0x14
        MsgFlowLabelBlock *mMsgFlowLabelBlk; // "FLI1", at 0x18

        // Unofficial symbol
        inline u32 getBlkSize(const void *dataBlkHeader)
        {
            #line 260
            EGG_ASSERT(dataBlkHeader);
            // Any block cast will do (except MsgHeaderBlock),
            // as they all have mDataSize at 0x4.
            return ((MsgInfoBlock *)dataBlkHeader)->mDataSize;
        }

        // Unofficial symbol
        inline u32 getDataBlkKind(const void *data)
        {
            #line 271
            EGG_ASSERT(data);
            // Any block cast will do, as they all have mMagic at 0x0.
            return ((MsgInfoBlock *)data)->mMagic;
        }

        MsgRes(const void *);
        virtual ~MsgRes();
        static void analyzeTag(u16, const wchar_t*, u8*, unsigned int*, void **);
        const wchar_t * getMsg(unsigned int, unsigned int);
        MsgInfoBlockEntry * getMsgEntry(unsigned int, unsigned int) __attribute__((never_inline));
        u32 getMsgID(u16); // inlined
        EDataBlkKind analyzeDataBlkKind(unsigned int); // inlined
        const void * extractMsgHeader(const void *); // inlined
        const void * extractMsgInfoDataBlk(const void *); // inlined
        const void * extractMsgDataBlk(const void *); // inlined
        const void * extractStrAttrDataBlk(const void *); // inlined
        const void * extractMsgIDDataBlk(const void *); // inlined
        const void * extractFlowChartInfoDataBlk(const void *); // inlined
        const void * extractFlowLabelInfoDataBlk(const void *); // inlined
    };
}

#endif