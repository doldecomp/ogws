#ifndef RP_KERNEL_TEXT_WRITER_H
#define RP_KERNEL_TEXT_WRITER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <nw4r/ut.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Screen text writer
 */
class RPSysTextWriter : public nw4r::ut::TextWriter {
    RP_SINGLETON_DECL(RPSysTextWriter);

public:
    /**
     * @brief Resets all text settings
     */
    void Reset();

    /**
     * @brief Prints formatted text to the screen at the specified coordinates
     * @details Coordinates use a left-upper origin
     */
    void Printf(f32 x, f32 y, const char* pMsg, ...);

    /**
     * @brief Prints formatted text to the screen at the specified coordinates
     * @details Coordinates use a center-canvas origin
     */
    void PrintfZeroCenter(f32 x, f32 y, const char* pMsg, ...);

    /**
     * @brief Sets up a GX context for rendering
     */
    void Begin();
    /**
     * @brief Ends the rendering context
     */
    void End();

private:
    //! Whether we are inside a rendering context
    BOOL mIsInBegin; // at 0x68
};

//! @}

#endif
