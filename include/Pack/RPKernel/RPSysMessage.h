#ifndef RP_KERNEL_MESSAGE_H
#define RP_KERNEL_MESSAGE_H
#include <Pack/types_pack.h>

#include <egg/util.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief MsgRes wrapper for extra message info data
 */
class RPSysMessage : public EGG::MsgRes {
public:
    /**
     * @brief Message info extension
     */
    struct Entry : EGG::MsgRes::MessageInfoDataBlock::Entry {
        //! Text scale
        u16 scale; // at 0x8
        //! Space between characters
        s8 charSpace; // at 0xA
    };

public:
    /**
     * @brief Constructor
     *
     * @param pBinary Binary file data
     * @param pHeap Heap to use for allocations
     */
    RPSysMessage(const void* pBinary, EGG::Heap* pHeap);

    /**
     * @brief Destructor
     */
    virtual ~RPSysMessage(); // at 0x8

    /**
     * @brief Gets the text for the specified message
     *
     * @param group Group ID
     * @param idx Message index
     */
    const wchar_t* GetMsg(u32 group, u32 idx);

    /**
     * @brief Gets the info block for the specified message
     *
     * @param group Group ID
     * @param idx Message index
     */
    const Entry* GetMsgEntry(u32 group, u32 idx);

    /**
     * @brief Gets the attributes for the specified message
     *
     * @param group Group ID
     * @param idx Message index
     */
    u32 GetAttribute(u32 group, u32 idx);

    /**
     * @brief Gets the scale of the specified message
     * @details The decimal scale is obtained by dividing this value by 100.
     *
     * @param group Group ID
     * @param idx Message index
     */
    u16 GetScale(u32 group, u32 idx);

    /**
     * @brief Gets the character spacing of the specified message
     *
     * @param group Group ID
     * @param idx Message index
     */
    u8 GetCharSpace(u32 group, u32 idx);
};

//! @}

#endif
