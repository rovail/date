#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "log.h"

static FILE* log_file = NULL;
static LogLevel log_level = LOG_INFO;

void set_log_level(LogLevel level)
{
    log_level = level;
}

void set_log_file(const char* file_name)
{
    if (log_file != NULL)
        fclose(log_file);

    log_file = fopen(file_name, "w");
}

void log_message(LogLevel level, const char* format, ...)
{
    if (level < log_level)
        return;

    time_t raw_time;
    struct tm* time_info;
    char time_buffer[20];

    time(&raw_time);
    time_info = localtime(&raw_time);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", time_info);

    va_list args;
    va_start(args, format);

    if (log_file != NULL)
    {
        fprintf(log_file, "[%s] ", time_buffer);
        vfprintf(log_file, format, args);
        fprintf(log_file, "\n");
        fflush(log_file);
    }

    va_end(args);
}

void log_close_file() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}
