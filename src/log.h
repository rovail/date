#ifndef LOG_H
#define LOG_H

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_ERROR
} LogLevel;

void set_log_level(LogLevel level);
void log_message(LogLevel level, const char* format, ...);
void set_log_file(const char* file_name);
void log_close_file();;

#endif