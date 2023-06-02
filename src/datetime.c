#include "datetime.h"
#include "input.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

bool date_is_valid(DateTime dateTime)
{
    if (dateTime.year < 0 || dateTime.month < 1 || dateTime.month > 12 || dateTime.day < 1)
    {
        errno = EINVAL;
        return false;
    }

    if (dateTime.hour < 0 || dateTime.hour >= 24)
    {
        errno = EINVAL;
        return false;
    }

    if (dateTime.minute < 0 || dateTime.minute >= 60)
    {
        errno = EINVAL;
        return false;
    }

    if (dateTime.second < 0 || dateTime.second >= 60)
    {
        errno = EINVAL;
        return false;
    }

    if (dateTime.millisecond < 0 || dateTime.millisecond >= 1000)
    {
        errno = EINVAL;
        return false;
    }

    int days_in_month;
    switch (dateTime.month)
    {
        case 2:
            if ((dateTime.year % 4 == 0 && dateTime.year % 100 != 0) || dateTime.year % 400 == 0)
                days_in_month = 29;
            else
                days_in_month = 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days_in_month = 30;
            break;
        default:
            days_in_month = 31;
    }

    if (dateTime.day > days_in_month)
    {
        errno = EINVAL;
        return false;
    }

    return true;
}

WeekDay get_weekday(DateTime dateTime)
{
    if (!date_is_valid(dateTime))
    {
        errno = EINVAL;
        return -1;
    }

    struct tm tm_date = {
            .tm_year = dateTime.year - 1900,
            .tm_mon = dateTime.month - 1,
            .tm_mday = dateTime.day
    };

    time_t timestamp = mktime(&tm_date);

    struct tm* tm_result = localtime(&timestamp);
    return tm_result->tm_wday;
}

char* get_month(DateTime dateTime)
{
    if (!date_is_valid(dateTime))
    {
        errno = EINVAL;
        return NULL;
    }

    static const char* months[] = {
            "INVALID",
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
    };

    return (char*)months[dateTime.month];
}

char* get_weekday_str(WeekDay weekDay)
{
    if (weekDay < SUNDAY || weekDay > SATURDAY)
    {
        errno = EINVAL;
        return NULL;
    }

    static const char* weekdays[] = {
            "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };

    return (char*)weekdays[weekDay];
}

char* get_datetime_str(DateTime dateTime)
{
    const char* months[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    const char* weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    
    const int MAX_DATETIME_STR_LENGTH = 50;
    char* datetime_str = malloc(MAX_DATETIME_STR_LENGTH);

    snprintf(datetime_str, MAX_DATETIME_STR_LENGTH, "%s, %02d, %s, %04d %02d:%02d:%02d.%03.0f",
             weekdays[get_weekday(dateTime)],
             dateTime.day, months[dateTime.month - 1],
             dateTime.year, dateTime.hour, dateTime.minute, dateTime.second, dateTime.millisecond);
    return datetime_str;
}