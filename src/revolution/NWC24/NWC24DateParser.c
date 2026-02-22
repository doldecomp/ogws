#include <revolution/NWC24.h>

const u8 DAYS_OF_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 0, 0, 0, 0};
const u16 DAYS_OF_YEAR[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

NWC24Err NWC24iDateToMinutes(s32 *outMinutes, const NWC24Date *date);
NWC24Err NWC24iEpochSecondsToDate(NWC24Date *date, s64 timestamp);
NWC24Err NWC24iDateToOSCalendarTime(OSCalendarTime *time, const NWC24Date *date);
NWC24Err NWC24iIsValidDate(u16 year, u8 month, u8 day);
static BOOL IsLeapYear(u16 year);
s32 ConvertDateToDays(u16 year, u16 month, u16 day);
void ConvertDaysToDate(u16 *year, u8 *month, u8 *day, s32 days);
static s32 ConvertTimeToMinutes(u8 hour, u8 sec);
static s32 ConvertDaysToMinutes(s32 days);
static s32 ConvertMinutesToDays(s32 minutes);

NWC24Err NWC24iDateToMinutes(s32 *outMinutes, const NWC24Date *date) {
    s32 days;
    s32 minutes;

    days = ConvertDateToDays(date->year, date->month, date->day);

    if (days == -1) {
        return NWC24_ERR_FAILED;
    }

    minutes = ConvertTimeToMinutes(date->hour, date->min);
    if (minutes == -1 || date->sec > 60) {
        return NWC24_ERR_FAILED;
    }

    *outMinutes = ConvertDaysToMinutes(days) + minutes;
    return NWC24_OK;
}

NWC24Err NWC24iEpochSecondsToDate(NWC24Date *date, s64 timestamp) {
    s64 adjusted = -0x7c558180U;
    s32 minutes;
    u32 days;

    if (0 > (timestamp + adjusted)) {
        timestamp = -adjusted;
    }

    timestamp += adjusted;
    date->sec = (u8)(timestamp % 60);
    minutes = timestamp / 60;
    if (minutes < 0) {
        minutes = 0;
    }

    days = ConvertMinutesToDays(minutes);
    minutes %= (24 * 60);

    date->hour = (u8)(minutes / 60);
    date->min = (u8)(minutes % 60);
    ConvertDaysToDate(&date->year, &date->month, &date->day, days);
    return NWC24_OK;
}

NWC24Err NWC24iDateToOSCalendarTime(OSCalendarTime *time, const NWC24Date *date) {
    s32 daysSinceEpoch;

    time->year = date->year;
    time->month = date->month - 1;
    time->mday = date->day;
    time->hour = date->hour;
    time->min = date->min;
    time->sec = date->sec;
    time->msec = 0;
    time->usec = 0;
    time->yday = (DAYS_OF_YEAR[time->month] + date->day) - 1;

    if (IsLeapYear(date->year) && date->month > 2) {
        time->yday++;
    }

    daysSinceEpoch = ConvertDateToDays(date->year, date->month, date->day);
    // Possibly NWC24iGetDayOfWeek(daysSinceEpoch)?
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

static BOOL IsLeapYear(u16 year) {
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) != 0);
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

static s32 ConvertTimeToMinutes(u8 hour, u8 sec) {
    if (hour > 23 || sec > 59) {
        return -1;
    }
    return (sec + (hour * 60));
}

static s32 ConvertDaysToMinutes(s32 days) {
    return days * (24 * 60);
}

static s32 ConvertMinutesToDays(s32 minutes) {
    return minutes / (24 * 60);
}
