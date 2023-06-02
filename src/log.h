#ifndef LOG_H
#define LOG_H

typedef enum {
    DEBUG,
    INFO,
    ERROR
} LogLevel;

void log_message(LogLevel level, const char* format, ...);
bool log_init(const char* filename, LogLevel level);
void log_close();
void get_current_datetime_str(char* datetime_str);

#endif