#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "log.h"

FILE* log_file;
LogLevel log_level;

void log_init(const char* filename, LogLevel level)
{
    log_file = fopen(filename, "w");
    if (log_file == NULL)
    {
        fprintf(stderr, "Failed to open log file: %s\n", filename);
        return;
    }
    log_level = level;
}

void log_message(LogLevel level, const char* format, ...)
{
    if (level < log_level)
        return;

    va_list args;
    va_start(args, format);

    switch (level)
    {
        case DEBUG:
            fprintf(log_file, "[DEBUG] ");
            vfprintf(log_file, format, args);
            fprintf(log_file, "\n");
            break;
        case INFO:
            fprintf(log_file, "[INFO] ");
            vfprintf(log_file, format, args);
            fprintf(log_file, "\n");
            break;
        case ERROR:
            fprintf(log_file, "[ERROR] ");
            vfprintf(log_file, format, args);
            fprintf(log_file, "\n");
            break;
    }

    va_end(args);
    fflush(log_file);
}

void log_close()
{
    if (log_file != NULL)
        fclose(log_file);
}