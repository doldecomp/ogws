#pragma pool_data on
#pragma ipa file
#pragma use_lmw_stmw on
#pragma opt_strength_reduction off
#include "eggMsgRes.h"
#include "eggAssert.h"

namespace EGG
{
    /*
        This can't really be matched until analyzeDataBlkKind can be auto inlined.
    */
    MsgRes::MsgRes(const void *data)
    {
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

        // Skip over header
        void *current = (void *)((u32)data + sizeof(MsgHeaderBlock));
        // Extract all sections ("blocks")
        u32 numBlocks = mMsgHeader->mNumBlocks;
        for (int i = 0; i < numBlocks; i++)
        {
            // BMG file size > current block ptr
            EGG_ASSERT(( u32 )data + mMsgHeader->mDataSize > ( u32 )current);

            u32 kind = getDataBlkKind(current);
            const void *block = current;
            switch(analyzeDataBlkKind(kind))
            {
                case BLOCK_MSGID:
                    block = extractMsgIDDataBlk(current);
                    break;
                case BLOCK_MSGDATA:
                    block = extractMsgDataBlk(current);
                    break;
                case BLOCK_MSGINFO:
                    block = extractMsgInfoDataBlk(current);
                    break;
                case BLOCK_STRATTR:
                    block = extractStrAttrDataBlk(current);
                    break;
                case BLOCK_FLOWLABEL:
                    block = extractFlowLabelInfoDataBlk(current);
                    break;
                case BLOCK_FLOWCHART:
                    block = extractFlowChartInfoDataBlk(current);
                    break;
                default:
                    #line 125
                    EGG_ASSERT_MSG(false, "Illegal data block.");
                    block = NULL;
                    break;
            }

            // Skip pointer to end of current block.
            u32 blkSize = getBlkSize(block);
            current = (void *)((u32)current + blkSize);
        }
    }

    MsgRes::~MsgRes()
    {

    }

    void MsgRes::analyzeTag(u16 code, const wchar_t *tag, u8 *tagLength,
        unsigned int *tagID, void **param)
    {
        #line 159
        EGG_ASSERT(tag);
        EGG_ASSERT(tagLength);
        EGG_ASSERT(tagID);
        EGG_ASSERT(param);
        EGG_ASSERT(cTagMark == code);

        *tagLength = *tag - 2;
        *tagID = *(u32 *)tag & 0x00FFFFFF;
        
        if (*tagLength > 4)
        {
            *param = (wchar_t *)tag + 2;
        }
        else
        {
            *param = NULL;
        }
    }

    const wchar_t * MsgRes::getMsg(unsigned int r4, unsigned int r5)
    {
        #line 189
        EGG_ASSERT(mMsgDataBlk);

        MsgInfoBlockEntry *pEntry = getMsgEntry(r4, r5);
        EGG_ASSERT_MSG(pEntry, "Not found message %d, %d.", r4, r5);

        return (wchar_t *)((u32)mMsgDataBlk->mStringPool + pEntry->mDataBlkOfs);
    }

    const void * MsgRes::extractMsgHeader(const void *data)
    {
        #line 223
        EGG_ASSERT(data);
        mMsgHeader = (MsgHeaderBlock *)data;
        return data;
    }

    const void * MsgRes::extractMsgInfoDataBlk(const void *data)
    {
        #line 251
        EGG_ASSERT(data);
        mMsgInfoDataBlk = (MsgInfoBlock *)data;
        return data;
    }

    const void * MsgRes::extractMsgDataBlk(const void *data)
    {
        #line 277
        EGG_ASSERT(data);
        mMsgDataBlk = (MsgDataBlock *)data;
        return data;
    }   

    const void * MsgRes::extractStrAttrDataBlk(const void *data)
    {
        #line 298
        EGG_ASSERT(data);
        mMsgStrDataBlk = (MsgStrAttrBlock *)data;
        return data;
    }

    const void * MsgRes::extractMsgIDDataBlk(const void *data)
    {
        #line 309
        EGG_ASSERT(data);
        mMsgIDDataBlk = (MsgIdBlock *)data;
        return data;
    }

    const void * MsgRes::extractFlowChartInfoDataBlk(const void *data)
    {
        #line 334
        EGG_ASSERT(data);
        mMsgFlowChartBlk = (MsgFlowChartBlock *)data;
        return data;
    }

    const void * MsgRes::extractFlowLabelInfoDataBlk(const void *data)
    {
        #line 345
        EGG_ASSERT(data);
        mMsgFlowLabelBlk = (MsgFlowLabelBlock *)data;
        return data;
    }

    /*
        cMsgSectionMagic needs to be pooled for this code to match (and also stay under inline_auto_max),
        however it also needs to be in .rodata.

        There must be something else at play here because pool_data doesn't touch const data,
        only global/static.
    */
    MsgRes::EDataBlkKind MsgRes::analyzeDataBlkKind(unsigned int kind)
    {
        if (kind == cMsgSectionMagic[BLOCK_MSGINFO]) return BLOCK_MSGINFO;
        else if (kind == cMsgSectionMagic[BLOCK_MSGDATA]) return BLOCK_MSGDATA;
        else if (kind == cMsgSectionMagic[BLOCK_STRATTR]) return BLOCK_STRATTR;
        else if (kind == cMsgSectionMagic[BLOCK_MSGID]) return BLOCK_MSGID;
        else if (kind == cMsgSectionMagic[BLOCK_FLOWCHART]) return BLOCK_FLOWCHART;
        else if (kind == cMsgSectionMagic[BLOCK_FLOWLABEL]) return BLOCK_FLOWLABEL;
        else
        {
            #line 366
            EGG_ASSERT_MSG(false, "Illegal data block.");
            return BLOCK_ILLEGAL;
        }
    }

    /*
        Masks aren't being loaded properly.
        The first one uses lwzx rather than lwz 0(r3).

        This is probably because I haven't gotten the const data pooling to work yet.
    */
    MsgRes::MsgInfoBlockEntry * MsgRes::getMsgEntry(unsigned int r4 , unsigned int r5)
    {
        #line 380
        EGG_ASSERT(mMsgInfoDataBlk);
        EGG_ASSERT(mMsgIDDataBlk);

        MsgIdBlock *pMidBlk = mMsgIDDataBlk;
        u32 shift = cShifts[pMidBlk->UNK_0xB];
        u32 mask = cMasks[pMidBlk->UNK_0xB].INT_0x0;
        u32 mask2 = cMasks[pMidBlk->UNK_0xB].INT_0x4;
        for (u16 i = 0; i < mMsgIDDataBlk->mNumEntries; i++)
        {
            u32 msgId = getMsgID(i);
            if (r4 == (msgId & mask) >> (32 - shift) && r5 == (msgId & mask2))
            {
                #line 402
                EGG_ASSERT(mMsgInfoDataBlk->mNumEntries > i);

                return (MsgInfoBlockEntry *)((u32)mMsgInfoDataBlk->mMsgInfo + (i * mMsgInfoDataBlk->mItemSize));
            }
        }

        return NULL;
    }

    u32 MsgRes::getMsgID(u16 i)
    {
        #line 425
        EGG_ASSERT(mMsgIDDataBlk);
        return mMsgIDDataBlk->mMsgIds[i];
    }
}
