#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "convert.h"
#include "input.h"
#include "datetime.h"
#include "log.h"

int main()
{
    log_init("log.txt", INFO);
    log_message(INFO, "Program started");

    while (true)
    {
        int year = ask_int("Enter Year: ", "Invalid year");
        int month = ask_int("Enter Month: ", "Invalid month");
        int day = ask_int("Enter Day: ", "Invalid day");
        int hour = ask_int("Enter Hour: ", "Invalid hour");
        int minute = ask_int("Enter Minute: ", "Invalid minute");
        int second = ask_int("Enter Second: ", "Invalid second");
        double millisecond = ask_double("Enter Millisecond: ", "Invalid millisecond");

        DateTime dateTime;
        dateTime.year = year;
        dateTime.month = month;
        dateTime.day = day;
        dateTime.hour = hour;
        dateTime.minute = minute;
        dateTime.second = second;
        dateTime.millisecond = millisecond;

        bool is_valid = date_is_valid(dateTime);

        log_message(DEBUG, "Date input: %04d-%02d-%02d %02d:%02d:%02d.%03.0f, Valid: %s",
                    dateTime.year, dateTime.month, dateTime.day,
                    dateTime.hour, dateTime.minute, dateTime.second, dateTime.millisecond,
                    is_valid ? "true" : "false");

        printf("Is Date Valid: %s\n", is_valid ? "true" : "false");
        log_message(INFO, "Date validity: %s", is_valid ? "true" : "false");

        if (is_valid)
        {
            char* datetime_str = get_datetime_str(dateTime);
            if (datetime_str != NULL)
            {
                printf("Formatted Date: %s\n", datetime_str);
                log_message(INFO, "Formatted Date: %s", datetime_str);
                free(datetime_str);
            }
            else
            {
                printf("Error: Unable to format date.\n");
                log_message(ERROR, "Failed to format date");
            }
        }

        YESNO continue_input = ask_yes_no("Do you want to enter new date and time? (y/n): ",
                                          "Invalid input. Please enter 'y' or 'n'.");
        if (continue_input == NO)
        {
            break;
        }
    }

    log_message(INFO, "Program ended");
    log_close();

    return 0;
}