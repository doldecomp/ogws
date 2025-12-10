#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <cstdlib>
#include <cwchar>

/**
 * @brief Tests whether the specified integral value is a singular noun
 *
 * @param x Integral value
 */
bool RPSysStringUtility::IsSingular(s32 x) {
    RPSysProjectLocal::EArea locale =
        RP_GET_INSTANCE(RPSysProjectLocal)->getLocale();

    if (locale == RPSysProjectLocal::EArea_France) {
        if (x < 2 && x > -2) {
            return true;
        }

        return false;
    }

    if (x == 1 || x == -1) {
        return true;
    }

    return false;
}

/**
 * @brief Tests whether the specified decimal value is a singular noun
 *
 * @param x Decimal value
 */
bool RPSysStringUtility::IsSingular(f32 x) {
    RPSysProjectLocal::EArea locale =
        RP_GET_INSTANCE(RPSysProjectLocal)->getLocale();

    if (locale == RPSysProjectLocal::EArea_France) {
        if (2.0f > x && -2.0f < x) {
            return true;
        }

        return false;
    }

    if (x == 1.0f || x == -1.0f) {
        return true;
    }

    return false;
}

/**
 * @brief Converts the specified integer to a half-width string
 *
 * @param x Integer value
 * @param[out] pBuffer String buffer
 * @param maxLen Buffer length
 * @param plusSign Whether to include signage for positive values
 */
void RPSysStringUtility::GetStringHalfSizeNumber(s32 x, wchar_t* pBuffer,
                                                 u32 maxLen, bool plusSign) {
    s32 skip = 0;

    if (plusSign && x == 0) {
        skip = 1;
        *pBuffer = L'±';
    } else if (plusSign && x > 0) {
        skip = 1;
        *pBuffer = L'+';
    }

    std::swprintf(pBuffer + skip, maxLen - skip, L"%d", x);
}

/**
 * @brief Converts the specified integer to a full-width string
 *
 * @param x Integer value
 * @param[out] pBuffer String buffer
 * @param maxLen Buffer length
 * @param plusSign Whether to include signage for positive values
 */
void RPSysStringUtility::GetStringFullSizeNumber(s32 x, wchar_t* pBuffer,
                                                 u32 maxLen, bool plusSign) {
    GetStringHalfSizeNumber(x, pBuffer, maxLen, plusSign);
    ChangeToFullSize(pBuffer);
}

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
void RPSysStringUtility::GetStringHalfSizeNumber(f32 x, s32 width,
                                                 s32 precision,
                                                 wchar_t* pBuffer, u32 maxLen,
                                                 bool plusSign,
                                                 FillType fillType) {
    wchar_t fmt[16];
    std::swprintf(fmt, ARRAY_SIZE(fmt), L"%%%d.%df", width, precision);

    s32 skip = 0;

    if (plusSign && x == 0.0f) {
        skip = 1;
        *pBuffer = L'±';
    } else if (plusSign && 0.0f < x) {
        skip = 1;
        *pBuffer = L'+';
    }

    std::swprintf(pBuffer + skip, maxLen - skip, fmt, x);
    ChangePoint(pBuffer);

    if (fillType != FillType_HalfWidth) {
        ChangePointHalfFull(pBuffer);
    }
}

/**
 * @brief Converts half-width characters in the specified string to
 * full-width characters
 *
 * @param pStr Input string
 */
void RPSysStringUtility::ChangeToFullSize(wchar_t* pStr) {
    u32 len = std::wcslen(pStr);

    for (u32 i = 0; i < len; i++) {
        if (pStr[i] == L' ') {
            pStr[i] = 0x3000 /* ideographic space */;
        } else if (pStr[i] >= L'!' && pStr[i] <= L'~') {
            pStr[i] += 0xFEE0;
        }
    }
}

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
void RPSysStringUtility::GetStringHalfSizeDate(u32 year, u32 month, u32 day,
                                               wchar_t* pBuffer,
                                               u32 /* maxLen */, s32 yearSize) {
    RPSysProjectLocal::EArea locale =
        RP_GET_INSTANCE(RPSysProjectLocal)->getLocale();

    s32 index = 0;

    // Date string indices
    enum { T1 = 0, SEP1 = 2, T2 = 3, SEP2 = 5, T3 = 6, SEP3 = 8 };

    switch (locale) {
    // YY/MM/DD
    case RPSysProjectLocal::EArea_Japan: {
        pBuffer[yearSize + SEP1 - SEP1] = L'/';
        pBuffer[yearSize + SEP2 - SEP1] = L'/';
        break;
    }

    // DD/MM/YY
    case RPSysProjectLocal::EArea_Germany: {
        pBuffer[SEP1] = L'.';
        pBuffer[SEP2] = L'.';
        break;
    }

    // MM/DD/YY
    default: {
        pBuffer[SEP1] = L'/';
        pBuffer[SEP2] = L'/';
        break;
    }
    }

    switch (locale) {
    // YY/MM/DD
    case RPSysProjectLocal::EArea_Japan: {
        index = T1;
        break;
    }

    // MM/DD/YY or DD/MM/YY
    default: {
        index = T3;
        break;
    }
    }

    if (yearSize == 4) {
        s32 yearIdx = index;
        pBuffer[yearIdx] = L'0' + year / 1000;
        pBuffer[++yearIdx] = L'0' + (year % 1000) / 100;

        index += 2;
    }

    pBuffer[index] = L'0' + (year % 100) / 10;
    pBuffer[++index] = L'0' + year % 10;

    switch (locale) {
    // YY/MM/DD
    case RPSysProjectLocal::EArea_Japan: {
        index = yearSize + 1;
        break;
    }

    // MM/DD/YY
    case RPSysProjectLocal::EArea_USA: {
        index = T1;
        break;
    }

    // DD/MM/YY
    default: {
        index = T2;
        break;
    }
    }

    pBuffer[index] = L'0' + month / 10;
    pBuffer[++index] = L'0' + month % 10;

    switch (locale) {
    // YY/MM/DD
    case RPSysProjectLocal::EArea_Japan: {
        index = yearSize + T3 - SEP1;
        break;
    }

    // MM/DD/YY
    case RPSysProjectLocal::EArea_USA: {
        index = T2;
        break;
    }

    // DD/MM/YY
    default: {
        index = T1;
        break;
    }
    }

    pBuffer[index] = L'0' + day / 10;
    pBuffer[++index] = L'0' + day % 10;

    pBuffer[yearSize + T3 - T1] = L'\0';
}

/**
 * @brief Converts the specified time to a half-width string
 *
 * @param hour Hour
 * @param min Minute
 * @param[out] pBuffer String buffer
 */
void RPSysStringUtility::GetStringHalfSizeTime(u32 hour, u32 min,
                                               wchar_t* pBuffer) {
    RPSysProjectLocal::EArea locale =
        RP_GET_INSTANCE(RPSysProjectLocal)->getLocale();

    // Time string indices
    enum { HH = 0, HSEP = 2, MM = 3, MSEP = 5, PER = 6, END = 10 };

    // Only US builds append the AM/PM period
    pBuffer[MSEP] = L'\0';
    pBuffer[HSEP] = L':';

    if (locale == RPSysProjectLocal::EArea_USA) {
        pBuffer[MSEP] = L' ';
        pBuffer[END] = L'\0';

        if (hour > 11) {
            pBuffer[PER + 0] = L'p';
            pBuffer[PER + 1] = L'.';
            pBuffer[PER + 2] = L'm';
            pBuffer[PER + 3] = L'.';

            hour %= 12;

            if (hour == 0) {
                hour = 12;
            }
        } else {
            pBuffer[PER + 0] = L'a';
            pBuffer[PER + 1] = L'.';
            pBuffer[PER + 2] = L'm';
            pBuffer[PER + 3] = L'.';
        }
    }

    if (hour / 10 == 0) {
        pBuffer[HH + 0] = L' ';
    } else {
        pBuffer[HH + 0] = L'0' + hour / 10;
    }
    pBuffer[HH + 1] = L'0' + hour % 10;

    pBuffer[MM + 0] = L'0' + min / 10;
    pBuffer[MM + 1] = L'0' + min % 10;
}

/**
 * @brief Parses a float value from the specified string
 * @details This function supports strings using commas as the decimal
 *
 * @param pStr Input string
 */
f32 RPSysStringUtility::GetFloat(const wchar_t* pStr) {
    char work[128];
    u32 i;

    for (i = 0; pStr[i] != L'\0'; i++) {
        if (pStr[i] == L',') {
            work[i] = '.';
        } else {
            work[i] = static_cast<char>(pStr[i]);
        }
    }

    work[i] = '\0';
    return static_cast<f32>(std::atof(work));
}

/**
 * @brief Changes decimal points in the specified string to match the locale
 *
 * @param pStr Input string
 */
void RPSysStringUtility::ChangePoint(wchar_t* pStr) {
    RPSysProjectLocal::EArea locale =
        RP_GET_INSTANCE(RPSysProjectLocal)->getLocale();

    if (locale == RPSysProjectLocal::EArea_Japan ||
        locale == RPSysProjectLocal::EArea_USA ||
        locale == RPSysProjectLocal::EArea_England) {
        return;
    }

    u32 len = std::wcslen(pStr);

    for (u32 i = 0; i < len; i++) {
        if (pStr[i] == L'.') {
            pStr[i] = L',';
            break;
        } else if (pStr[i] == L'．' /* full-width period */) {
            pStr[i] = L'，' /* full-width comma */;
            break;
        }
    }
}

/**
 * @brief Swaps decimal points in the specified string between half and full
 * width
 *
 * @param pStr Input string
 */
void RPSysStringUtility::ChangePointHalfFull(wchar_t* pStr) {
    u32 len = std::wcslen(pStr);

    for (u32 i = 0; i < len; i++) {
        switch (pStr[i]) {
        default: {
            break;
        }

        case L'.': {
            pStr[i] = L'．'; /* full-width period */
            break;
        }

        case L'．' /* full-width period */: {
            pStr[i] = L'.';
            break;
        }

        case L',': {
            // @bug Should be a full-width character
            pStr[i] = L',';
            break;
        }

        case L'，' /* full-width comma */: {
            pStr[i] = L',';
            break;
        }
        }
    }
}
