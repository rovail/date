#include "datetime.h"
#include "input.h"
#include "log.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>

bool date_is_valid(DateTime dateTime)
{
    if (dateTime.year < 0 || dateTime.month < 1 || dateTime.month > 12 || dateTime.day < 1 || dateTime.day > 31 ||
        dateTime.hour < 0 || dateTime.hour >= 24 || dateTime.minute < 0 || dateTime.minute >= 60 ||
        dateTime.second < 0 || dateTime.second >= 60 || dateTime.millisecond < 0 || dateTime.millisecond >= 1000)
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
    if (!date_is_valid(dateTime))
    {
        errno = EINVAL;
        return NULL;
    }

    char* weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    char datetime_str[150];
    snprintf(datetime_str, sizeof(datetime_str), "%s, %02d, %s, %d, %02d:%02d:%02d.%03f",
            weekdays[get_weekday(dateTime)],
            dateTime.day,
            months[dateTime.month - 1],
            dateTime.year,
            dateTime.hour,
            dateTime.minute,
            dateTime.second,
            dateTime.millisecond);

    char* result = malloc(strlen(datetime_str) + 1);
    if (result == NULL)
    {
        return NULL;
    }

    strcpy(result, datetime_str);
    return result;
}