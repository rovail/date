#ifndef LB4_CONVERT_H
#define LB4_CONVERT_H

#include <stdbool.h>

bool try_convert_to_int(const char* string, int* result);
bool try_convert_to_long(const char* string, long* result);
bool try_convert_to_double(const char* string, double* result);

#endif