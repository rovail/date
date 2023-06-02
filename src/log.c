#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "log.h"

#define LOG_FILE_PATH "log.txt"

LogLevel log_level;
FILE* log_file = NULL;

bool log_init(const char* filename, LogLevel level)
{
    log_file = fopen(filename, "a");
    if (log_file == NULL)
    {
        printf("Error: Failed to open log file '%s'\n", filename);
        return false;
    }
    log_level = level;

    return true;
}

void log_message(LogLevel level, const char* format, ...)
{
    FILE* log_file = fopen(LOG_FILE_PATH, "a");
    if (log_file == NULL)
    {
        printf("Failed to open log file.\n");
        return;
    }

    const char* level_str;
    switch (level)
    {
        case INFO:
            level_str = "INFO";
            break;
        case DEBUG:
            level_str = "DEBUG";
            break;
        case ERROR:
            level_str = "ERROR";
            break;
        default:
            level_str = "UNKNOWN";
            break;
    }

    va_list args;
    va_start(args, format);

    char datetime_str[50];
    get_current_datetime_str(datetime_str);

    fprintf(log_file, "[%s: %s] ", level_str, datetime_str);
    vfprintf(log_file, format, args);
    fprintf(log_file, "\n");

    va_end(args);

    fclose(log_file);
}

void get_current_datetime_str(char* datetime_str)
{
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(datetime_str, 50, "%A, %d, %b, %Y %H:%M:%S", tm_info);
}

void log_close()
{
    if (log_file != NULL)
        fclose(log_file);
}