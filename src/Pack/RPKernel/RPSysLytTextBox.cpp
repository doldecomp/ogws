#include "Pack/RPKernel/RPSysLytTextBox.h"

#include "Pack/RPKernel/RPSysMessage.h"
#include <Pack/RPKernel.h>

#include <revolution/GX.h>

/**
 * @brief Work buffer for string formatting
 */
wchar_t RPSysLytTextBox::sTextBuffer[TEXT_BUFFER_SIZE];

/**
 * @brief Sets a formatted string to the textbox
 *
 * @param pFmt Format string
 * @param argc Number of format arguments
 * @param ... Format arguments
 */
void RPSysLytTextBox::setText(const wchar_t* pFmt, int argc, ...) {
    std::va_list list;
    va_start(list, pFmt);

    setText(pFmt, argc, list);

    va_end(list);
}

/**
 * @brief Sets a formatted string to the textbox
 *
 * @param pFmt Format string
 * @param argc Number of format arguments
 * @param argv Format arguments
 */
void RPSysLytTextBox::setText(const wchar_t* pFmt, int argc, va_list argv) {
    int written = 0;

    RP_GET_INSTANCE(RPSysTagProcessor)
        ->PreProcessEx(pFmt, sTextBuffer, TEXT_BUFFER_SIZE, &written, argc,
                       argv);

    SetString(sTextBuffer, 0, written);
}

/**
 * @brief Sets a formatted message to the textbox
 *
 * @param pMessage Message holder
 * @param group Group ID
 * @param idx Message index
 * @param argc Number of format arguments
 * @param ... Format arguments
 */
void RPSysLytTextBox::setMessage(RPSysMessage* pMessage, u32 group, u32 idx,
                                 int argc, ...) {
    std::va_list list;
    va_start(list, argc);

    setMessage(pMessage, group, idx, argc, list);

    va_end(list);
}

/**
 * @brief Sets a formatted message to the textbox
 *
 * @param pMessage Message holder
 * @param group Group ID
 * @param idx Message index
 * @param argc Number of format arguments
 * @param argv Format arguments
 */
void RPSysLytTextBox::setMessage(RPSysMessage* pMessage, u32 group, u32 idx,
                                 int argc, va_list argv) {

    setText(pMessage->GetMsg(group, idx), argc, argv);

    s8 charSpace = pMessage->GetCharSpace(group, idx);
    SetCharSpace(charSpace);

    f32 scale = pMessage->GetScale(group, idx) * (1.0f / 100.0f);
    setScaleX(scale);
}

/**
 * @brief Sets the horizontal scale of the font
 *
 * @param scale New horizontal scale
 */
void RPSysLytTextBox::setScaleX(f32 scale) {
    nw4r::lyt::Size fontSize;

    fontSize = GetFontSize();
    fontSize.width = GetFont()->GetWidth() * scale;

    SetFontSize(fontSize);
}

/**
 * @brief Sets a string to the textbox
 * @details This function also applies the attributes from the specified
 * message.
 *
 * @param pMessage Message holder
 * @param group Group ID
 * @param idx Message index
 * @param pText New text
 */
void RPSysLytTextBox::setMessage(RPSysMessage* pMessage, u32 group, u32 idx,
                                 const wchar_t* pText) {

    setText(pText, 0);

    s8 charSpace = pMessage->GetCharSpace(group, idx);
    SetCharSpace(charSpace);

    f32 scale = pMessage->GetScale(group, idx) * (1.0f / 100.0f);
    nw4r::lyt::Size fontSize = GetFontSize();
    fontSize.width = GetFont()->GetWidth() * scale;
    SetFontSize(fontSize);
}

/**
 * @brief Copies the front color from the specified textbox
 *
 * @param rOther Textbox to copy from
 */
void RPSysLytTextBox::copyFontColor(const RPSysLytTextBox& rOther) {
    nw4r::lyt::Material* pDst = mpMaterial;

    for (int i = 0; i < nw4r::lyt::TEVCOLOR_MAX; i++) {
        pDst->SetTevColor(i, rOther.mpMaterial->GetTevColor(i));
    }

    for (int i = 0; i < nw4r::lyt::TEXTCOLOR_MAX; i++) {
        mTextColors[i] = rOther.mTextColors[i];
    }
}
