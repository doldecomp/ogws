#include <revolution/NWC24.h>

// The number of seconds between 01/01/1900 and 01/01/1970
#define EPOCH_BASE 2208988800

#define SEC_MAX 60
#define MIN_MAX 60
#define HOUR_MAX 24

#define DAY_MIN 1

#define MONTH_MIN 1
#define MONTH_MAX 12

#define YEAR_MIN 1900

#define WEEK_DAY_MIN 1
#define WEEK_DAY_MAX 7

#define YEAR_DAY_MIN 1
#define YEAR_DAY_MAX 365

// Length of each month
static const u8 DAYS_OF_MONTH[MONTH_MAX] = {31, 28, 31, 30, 31, 30,
                                            31, 31, 30, 31, 30, 31};
// End of each month
static const u16 DAYS_OF_YEAR[MONTH_MAX] = {0,   31,  59,  90,  120, 151,
                                            181, 212, 243, 273, 304, 334};

// Forward declarations
static BOOL IsLeapYear(u16 year);
static s32 ConvertDateToDays(u16 year, u8 month, u8 day);
static void ConvertDaysToDate(u16* pYear, u8* pMonth, u8* pDay, s32 days);
static s32 ConvertTimeToMinutes(u8 hour, u8 min);
static s32 ConvertDaysToMinutes(s32 days);
static void ConvertMinutesToDays(s32* pDays, u8* pHour, u8* pMin, s32 minutes);

NWC24Err NWC24iDateToMinutes(s32* pMinutes, const NWC24Date* pDate) {
    s32 days;
    s32 minutes;

    days = ConvertDateToDays(pDate->year, pDate->month, pDate->day);
    if (days == -1) {
        return NWC24_ERR_FAILED;
    }

    minutes = ConvertTimeToMinutes(pDate->hour, pDate->min);
    if (minutes == -1 || pDate->sec > SEC_MAX) {
        return NWC24_ERR_FAILED;
    }

    *pMinutes = ConvertDaysToMinutes(days) + minutes;
    return NWC24_OK;
}

s32 NWC24iGetDayOfWeek(u16 year, u8 month, u8 day) {
    s32 days = ConvertDateToDays(year, month, day);
    return (days + DAY_MIN) % WEEK_DAY_MAX;
}

NWC24Err NWC24iEpochSecondsToDate(NWC24Date* pDate, s64 timestamp) {
    s32 minutes;
    s32 days;

    if (timestamp + EPOCH_BASE < 0) {
        timestamp = -EPOCH_BASE;
    }

    pDate->sec = (timestamp + EPOCH_BASE) % MIN_MAX;
    minutes = (timestamp + EPOCH_BASE) / MIN_MAX;

    ConvertMinutesToDays(&days, &pDate->hour, &pDate->min, minutes);
    ConvertDaysToDate(&pDate->year, &pDate->month, &pDate->day, days);

    return NWC24_OK;
}

NWC24Err NWC24iDateToOSCalendarTime(OSCalendarTime* pOSTime,
                                    const NWC24Date* pDate) {

    pOSTime->year = pDate->year;
    pOSTime->month = pDate->month - 1;
    pOSTime->mday = pDate->day;
    pOSTime->hour = pDate->hour;
    pOSTime->min = pDate->min;
    pOSTime->sec = pDate->sec;
    pOSTime->msec = 0;
    pOSTime->usec = 0;
    pOSTime->yday = (DAYS_OF_YEAR[pOSTime->month] + pDate->day) - YEAR_DAY_MIN;

    // Leap year adds an extra day (February 29th)
    if (IsLeapYear(pDate->year) && pDate->month > 2) {
        pOSTime->yday++;
    }

    pOSTime->wday = NWC24iGetDayOfWeek(pDate->year, pDate->month, pDate->day);

    return NWC24_OK;
}

NWC24Err NWC24iIsValidDate(u16 year, u8 month, u8 day) {
    s32 days = ConvertDateToDays(year, month, day);
    NWC24Err result = NWC24_OK;

    if (days == -1) {
        result = NWC24_ERR_INVALID_VALUE;
    }

    return result;
}

static BOOL IsLeapYear(u16 year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static s32 ConvertDateToDays(u16 year, u8 month, u8 day) {
    s32 dayOfYear;
    s32 yearsSince1900;
    s32 days;
    s32 leapDays;
    s32 gregorianCorrection;

    if (year < YEAR_MIN || month < MONTH_MIN || month > MONTH_MAX) {
        return -1;
    }

    // Leap year adds an extra day (February 29th)
    if (month == 2 && IsLeapYear(year)) {
        if (day < DAY_MIN || day > 29) {
            return -1;
        }
    } else if (day < DAY_MIN || DAYS_OF_MONTH[month - MONTH_MIN] < day) {
        return -1;
    }

    dayOfYear = day - 1;
    dayOfYear += DAYS_OF_YEAR[month - 1];

    // Leap year adds an extra day (February 29th)
    if (month >= 3 && IsLeapYear(year)) {
        dayOfYear++;
    }

    yearsSince1900 = year - YEAR_MIN;
    leapDays = (yearsSince1900 - 1) / 4 - (yearsSince1900 - 1) / 100;

    // Relative to YEAR_MIN=1900
    gregorianCorrection = (yearsSince1900 + 299) / 400;

    days = yearsSince1900 * YEAR_DAY_MAX + dayOfYear;
    days += leapDays + gregorianCorrection;

    return days;
}

static void ConvertDaysToDate(u16* pYear, u8* pMonth, u8* pDay, s32 days) {
    s32 backup;

    *pYear = YEAR_MIN;
    *pMonth = MONTH_MIN;
    *pDay = DAY_MIN;

    if (days < 0) {
        return;
    }

    while (TRUE) {
        backup = days;

        days -= IsLeapYear(*pYear) ? YEAR_DAY_MAX + 1 : YEAR_DAY_MAX;

        if (days < 0) {
            days = backup;
            break;
        }

        (*pYear)++;
    }

    while (TRUE) {
        backup = days;

        // Leap year adds an extra day (February 29th)
        if (*pMonth == 2 && IsLeapYear(*pYear)) {
            days -= 29;
        } else {
            days -= DAYS_OF_MONTH[*pMonth - DAY_MIN];
        }

        if (days < 0) {
            days = backup;
            break;
        }

        (*pMonth)++;
    }

    *pDay += days;
}

static s32 ConvertTimeToMinutes(u8 hour, u8 min) {
    // Hour/minute are zero indexed
    if (hour > HOUR_MAX - 1 || min > MIN_MAX - 1) {
        return -1;
    }

    return hour * MIN_MAX + min;
}

static s32 ConvertDaysToMinutes(s32 days) {
    return days * HOUR_MAX * MIN_MAX;
}

static void ConvertMinutesToDays(s32* pDays, u8* pHour, u8* pMin, s32 minutes) {
    if (minutes < 0) {
        minutes = 0;
    }

    *pDays = minutes / (MIN_MAX * HOUR_MAX);
    minutes %= (MIN_MAX * HOUR_MAX);

    *pHour = minutes / MIN_MAX;
    *pMin = minutes % MIN_MAX;
}
