#include <revolution/NWC24.h>

const u8 DAYS_OF_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 0, 0, 0, 0};
const u16 DAYS_OF_YEAR[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

s32 ConvertDateToDays(u16 year, u16 month, u16 day);
void ConvertDaysToDate(u16 *year, u8 *month, u8 *day, s32 days);

inline BOOL IsLeapYear(u16 year) {
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) != 0);
}

NWC24Err NWC24iDateToMinutes(s32 *outMinutes, const NWC24iDate *date) {
    s32 days;
    s32 minutes;
    u8 seconds;

    days = ConvertDateToDays(date->year, date->month, date->day);

    if (days == -1) {
        return NWC24_ERR_FAILED;
    }

    seconds = date->sec;
    if (date->hour > 23 || seconds > 59) {
        minutes = -1;
    } else {
        minutes = seconds + (date->hour * 60);
    }

    if (minutes == -1 || date->min > 60) {
        return NWC24_ERR_FAILED;
    }

    *outMinutes = days * (24 * 60) + minutes;
    return NWC24_OK;
}

NWC24Err NWC24iEpochSecondsToDate(NWC24iDate *date, s64 timestamp) {
    s64 adjusted = -0x7c558180U;
    s32 minutes;
    u32 days;

    if (0 > (timestamp + adjusted)) {
        timestamp = -adjusted;
    }

    timestamp += adjusted;
    date->min = (u8)(timestamp % 60);
    minutes = timestamp / 60;
    if (minutes < 0) {
        minutes = 0;
    }

    days = minutes / (24 * 60);
    minutes %= (24 * 60);
    date->hour = (u8)(minutes / 60);
    date->sec = (u8)(minutes % 60);
    ConvertDaysToDate(&date->year, &date->month, &date->day, days);
    return NWC24_OK;
}

NWC24Err NWC24iDateToOSCalendarTime(OSCalendarTime *time, const NWC24iDate *date) {
    s32 daysSinceEpoch;

    time->year = date->year;
    time->month = date->month - 1;
    time->mday = date->day;
    time->hour = date->hour;
    // TODO(Alex9303) Why are minutes and seconds swapped here? Is this a decompilation error or is it actually swapped in the original code?
    time->min = date->sec;  // Swapped?
    time->sec = date->min;  // Swapped?
    time->msec = 0;
    time->usec = 0;
    time->yday = (DAYS_OF_YEAR[time->month] + date->day) - 1;

    if (IsLeapYear(date->year) && date->month > 2) {
        time->yday++;
    }

    daysSinceEpoch = ConvertDateToDays(date->year, date->month, date->day);
    time->wday = (daysSinceEpoch + 1) % 7;
    return NWC24_OK;
}

NWC24Err NWC24iIsValidDate(u16 year, u8 month, u8 day) {
    s32 days = ConvertDateToDays(year, month, day);
    s32 result = NWC24_OK;

    if (days == -1) {
        result = NWC24_ERR_INVALID_VALUE;
    }

    return result;
}

s32 ConvertDateToDays(u16 year, u16 month, u16 day) {
    s32 dayOfYear;
    s32 yearsSince1900;
    s32 days;
    s32 leapDays;
    s32 gregorianCorrection;

    if (year < 1900 || month < 1 || month > 12) {
        return -1;
    }

    if (month == 2 && IsLeapYear(year)) {
        if (day < 1 || day > 29) {
            return -1;
        }
    } else {
        if (day < 1 || (u16)DAYS_OF_MONTH[month - 1] < day) {
            return -1;
        }
    }

    dayOfYear = day - 1;
    dayOfYear += DAYS_OF_YEAR[month - 1];

    if (month >= 3 && IsLeapYear(year)) {
        dayOfYear++;
    }

    yearsSince1900 = year - 1900;

    leapDays = (yearsSince1900 - 1) / 4 - (yearsSince1900 - 1) / 100;
    gregorianCorrection = (yearsSince1900 + 299) / 400;

    days = yearsSince1900 * 365 + dayOfYear;
    days += leapDays + gregorianCorrection;

    return days;
}

void ConvertDaysToDate(u16 *year, u8 *month, u8 *day, s32 days) {
    s32 remaining;

    *year = 1900;
    *month = 1;
    *day = 1;

    if (days < 0) {
        return;
    }

    while (1) {
        remaining = days;
        days -= IsLeapYear(*year) ? 366 : 365;

        if (days < 0) {
            days = remaining;
            break;
        }

        (*year)++;
    }

    while (1) {
        remaining = days;

        if (*month == 2 && IsLeapYear(*year)) {
            days -= 29;
        } else {
            days -= DAYS_OF_MONTH[*month - 1];
        }

        if (days < 0) {
            break;
        }

        (*month)++;
    }

    *day += remaining;
}
