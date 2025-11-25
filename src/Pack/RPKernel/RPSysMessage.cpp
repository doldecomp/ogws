#include <Pack/RPKernel.h>

/**
 * @brief Constructor
 *
 * @param pBinary Binary file data
 * @param pHeap Heap to use for allocations
 */
RPSysMessage::RPSysMessage(const void* pBinary, EGG::Heap* /* pHeap */)
    : EGG::MsgRes(pBinary) {}

/**
 * @brief Destructor
 */
RPSysMessage::~RPSysMessage() {}

/**
 * @brief Gets the text for the specified message
 *
 * @param group Group ID
 * @param idx Message index
 */
const wchar_t* RPSysMessage::GetMsg(u32 group, u32 idx) {
    return getMsg(group, idx);
}

/**
 * @brief Gets the info block for the specified message
 *
 * @param group Group ID
 * @param idx Message index
 */
const RPSysMessage::Entry* RPSysMessage::GetMsgEntry(u32 group, u32 idx) {
    return static_cast<const Entry*>(getMsgEntry(group, idx));
}

/**
 * @brief Gets the attributes for the specified message
 *
 * @param group Group ID
 * @param idx Message index
 */
u32 RPSysMessage::GetAttribute(u32 group, u32 idx) {
    return GetMsgEntry(group, idx)->mAttribute;
}

/**
 * @brief Gets the scale of the specified message
 * @details The decimal scale is obtained by dividing this value by 100.
 *
 * @param group Group ID
 * @param idx Message index
 */
u16 RPSysMessage::GetScale(u32 group, u32 idx) {
    return GetMsgEntry(group, idx)->scale;
}

/**
 * @brief Gets the character spacing of the specified message
 *
 * @param group Group ID
 * @param idx Message index
 */
u8 RPSysMessage::GetCharSpace(u32 group, u32 idx) {
    return GetMsgEntry(group, idx)->charSpace;
}
