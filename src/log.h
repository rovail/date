#ifndef LOG_H
#define LOG_H

typedef enum {
    DEBUG,
    INFO,
    ERROR
} LogLevel;

void log_message(LogLevel level, const char* format, ...);
void log_init(const char* filename, LogLevel level);
void log_close();

#endif