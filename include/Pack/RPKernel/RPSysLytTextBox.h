#ifndef RP_KERNEL_LYT_TEXT_BOX_H
#define RP_KERNEL_LYT_TEXT_BOX_H
#include <Pack/types_pack.h>

#include <nw4r/lyt.h>

#include <cstdarg>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysMessage;

/**
 * @brief NW4R layout textbox extension
 */
class RPSysLytTextBox : public nw4r::lyt::TextBox {
public:
    /**
     * @brief Sets a formatted string to the textbox
     *
     * @param pFmt Format string
     * @param argc Number of format arguments
     * @param ... Format arguments
     */
    void setText(const wchar_t* pFmt, int argc, ...);

    /**
     * @brief Sets a formatted string to the textbox
     *
     * @param pFmt Format string
     * @param argc Number of format arguments
     * @param argv Format arguments
     */
    void setText(const wchar_t* pFmt, int argc, va_list argv);

    /**
     * @brief Sets a formatted message to the textbox
     *
     * @param pMessage Message holder
     * @param group Group ID
     * @param idx Message index
     * @param argc Number of format arguments
     * @param ... Format arguments
     */
    void setMessage(RPSysMessage* pMessage, u32 group, u32 idx, int argc, ...);

    /**
     * @brief Sets a formatted message to the textbox
     *
     * @param pMessage Message holder
     * @param group Group ID
     * @param idx Message index
     * @param argc Number of format arguments
     * @param argv Format arguments
     */
    void setMessage(RPSysMessage* pMessage, u32 group, u32 idx, int argc,
                    va_list argv);

    /**
     * @brief Sets the horizontal scale of the font
     *
     * @param scale New horizontal scale
     */
    void setScaleX(f32 scale);

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
    void setMessage(RPSysMessage* pMessage, u32 group, u32 idx,
                    const wchar_t* pText);

    /**
     * @brief Copies the front color from the specified textbox
     *
     * @param rOther Textbox to copy from
     */
    void copyFontColor(const RPSysLytTextBox& rOther);

private:
    //! Size of the text work buffer
    static const int TEXT_BUFFER_SIZE = 512;

private:
    //! Work buffer for string formatting
    static wchar_t sTextBuffer[TEXT_BUFFER_SIZE];
};

//! @}

#endif
