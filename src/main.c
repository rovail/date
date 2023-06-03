#include <stdio.h>
#include <malloc.h>
#include "convert.h"
#include "input.h"
#include "datetime.h"
#include "log.h"

int main()
{
    set_log_level(LOG_DEBUG);
    set_log_file("log.txt");
    
    log_message(LOG_INFO, "Program started");

    while (true)
    {
        log_message(LOG_DEBUG, "Requesting user input");
        
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

        log_message(LOG_INFO,"Received user input: %d-%02d-%02d %02d:%02d:%02d.%03f",
                  dateTime.year, dateTime.month, dateTime.day,
                  dateTime.hour, dateTime.minute, dateTime.second,
                  dateTime.millisecond);

        bool valid = date_is_valid(dateTime);
        printf("Is Date Valid: %s\n", valid ? "true" : "false");
        log_message(LOG_DEBUG, "Date validity: %s", valid ? "true" : "false");

        if (valid)
        {
            log_message(LOG_INFO, "Date is valid: %d-%d-%d %02d:%02d:%02d.%03f", dateTime.year, dateTime.month, dateTime.day,
                 dateTime.hour, dateTime.minute, dateTime.second, dateTime.millisecond);
            char* datetime_str = get_datetime_str(dateTime);
            if (datetime_str != NULL) 
            {
                log_message(LOG_INFO, "Formatted Date: %s", datetime_str);
                printf("Formatted Date: %s\n", datetime_str);
                free(datetime_str);
                datetime_str = NULL;
            }
            else 
            {
                log_message(LOG_ERROR, "Unable to format date.");
                printf("Error: Unable to format date.\n");
            }
        }
        else
        {
            log_message(LOG_ERROR, "Invalid date: %d-%d-%d %02d:%02d:%02d.%03f", dateTime.year, dateTime.month, dateTime.day,
                      dateTime.hour, dateTime.minute, dateTime.second, dateTime.millisecond);
            printf("Error: Invalid date entered.\n");
        }

        YESNO continue_input = ask_yes_no("Do you want to enter a new date and time? (y/n): ",
                                          "Invalid input. Please enter 'y' or 'n'.");
        if (continue_input == NO)
        {
            log_message(LOG_INFO, "Program ended");
            break;
        }
    }

    log_close_file();
    return 0;
}