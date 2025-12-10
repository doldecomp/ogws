#ifndef RP_KERNEL_STRING_UTILITY_H
#define RP_KERNEL_STRING_UTILITY_H
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief String utility functions
 */
class RPSysStringUtility {
public:
    /**
     * @brief Decimal point fill type
     */
    enum FillType {
        FillType_HalfWidth, //!< Use half-width characters
        FillType_FullWidth, //!< Use full-width characters
    };

public:
    /**
     * @brief Tests whether the specified integral value is a singular noun
     *
     * @param x Integral value
     */
    static bool IsSingular(s32 x);

    /**
     * @brief Tests whether the specified decimal value is a singular noun
     *
     * @param x Decimal value
     */
    static bool IsSingular(f32 x);

    /**
     * @brief Converts the specified integer to a half-width string
     *
     * @param x Integer value
     * @param[out] pBuffer String buffer
     * @param maxLen Buffer length
     * @param plusSign Whether to include signage for positive values
     */
    static void GetStringHalfSizeNumber(s32 x, wchar_t* pBuffer, u32 maxLen,
                                        bool plusSign = false);

    /**
     * @brief Converts the specified integer to a full-width string
     *
     * @param x Integer value
     * @param[out] pBuffer String buffer
     * @param maxLen Buffer length
     * @param plusSign Whether to include signage for positive values
     */
    static void GetStringFullSizeNumber(s32 x, wchar_t* pBuffer, u32 maxLen,
                                        bool plusSign = false);

    /**
     * @brief Converts the specified decimal to a half-width string
     *
     * @param x Decimal value
     * @param width Value string width
     * @param precision Value string precision
     * @param[out] pBuffer String buffer
     * @param maxLen Buffer length
     * @param plusSign Whether to include signage for positive values
     * @param fillType Decimal point fill type
     */
    static void GetStringHalfSizeNumber(f32 x, s32 width, s32 precision,
                                        wchar_t* pBuffer, u32 maxLen,
                                        bool plusSign, FillType fillType);

    /**
     * @brief Converts half-width characters in the specified string to
     * full-width characters
     *
     * @param[in,out] pStr Input string
     */
    static void ChangeToFullSize(wchar_t* pStr);

    /**
     * @brief Converts the specified date to a half-width string
     *
     * @param year Year
     * @param month Month
     * @param day Day
     * @param[out] pBuffer String buffer
     * @param maxLen Buffer length
     * @param yearSize Number of digits to use when expressing the year
     */
    static void GetStringHalfSizeDate(u32 year, u32 month, u32 day,
                                      wchar_t* pBuffer, u32 maxLen,
                                      s32 yearSize = 4);

    /**
     * @brief Converts the specified time to a half-width string
     *
     * @param hour Hour
     * @param min Minute
     * @param[out] pBuffer String buffer
     */
    static void GetStringHalfSizeTime(u32 hour, u32 min, wchar_t* pBuffer);

    /**
     * @brief Parses a float value from the specified string
     * @details This function supports strings using commas as the decimal
     *
     * @param pStr Input string
     */
    static f32 GetFloat(const wchar_t* pStr);

    /**
     * @brief Changes decimal points in the specified string to match the locale
     *
     * @param pStr Input string
     */
    static void ChangePoint(wchar_t* pStr);

    /**
     * @brief Swaps decimal points in the specified string between half and full
     * width
     *
     * @param pStr Input string
     */
    static void ChangePointHalfFull(wchar_t* pStr);
};

//! @}

#endif
