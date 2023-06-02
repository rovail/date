#ifndef LB4_INPUT_H
#define LB4_INPUT_H

typedef enum {
    NO,
    YES
} YESNO;

YESNO ask_yes_no(const char* msg, const char* error_msg);
int ask_int(const char* msg, const char* error_msg);
double ask_double(const char* msg, const char* error_msg);
char* ask_string(const char* msg, const char* error_msg);

#endif
