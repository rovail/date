#include "convert.h"
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

bool try_convert_to_int(const char* string, int* result)
{
    int value = 0;
    int sign = 1;
    int i = 0;

    while (isspace(string[i]))
        i++;

    if (string[i] == '-' || string[i] == '+')
    {
        if (string[i] == '-')
            sign = -1;
        i++;
    }

    for (; string[i] != '\0'; i++)
    {
        if (isdigit(string[i]))
        {
            value = value * 10 + (string[i] - '0');
        }
        else
        {
            break;
        }
    }

    while (isspace(string[i]))
        i++;

    if (string[i] != '\0')
        return false;

    *result = value * sign;
    return true;
}

bool try_convert_to_long(const char* string, long* result)
{
    long value = 0;
    int sign = 1;
    int i = 0;

    while (isspace(string[i]))
        i++;

    if (string[i] == '-' || string[i] == '+')
    {
        if (string[i] == '-')
            sign = -1;
        i++;
    }

    for (; string[i] != '\0'; i++)
    {
        if (isdigit(string[i]))
        {
            value = value * 10 + (string[i] - '0');
        }
        else
        {
            break;
        }
    }

    while (isspace(string[i]))
        i++;

    if (string[i] != '\0')
        return false;

    *result = value * sign;
    return true;
}

bool try_convert_to_double(const char* string, double* result)
{
    double value = 0.0;
    double fraction = 0.1;
    int sign = 1;
    int i = 0;

    while (string[i] == ' ')
        i++;

    if (string[i] == '-' || string[i] == '+')
    {
        if (string[i] == '-')
            sign = -1;
        i++;
    }

    while (string[i] >= '0' && string[i] <= '9')
    {
        value = value * 10 + (string[i] - '0');
        i++;
    }

    if (string[i] == '.')
    {
        i++;
        while (string[i] >= '0' && string[i] <= '9')
        {
            value += (string[i] - '0') * fraction;
            fraction *= 0.1;
            i++;
        }
    }

    while (string[i] == ' ')
        i++;

    if (string[i] == 'e' || string[i] == 'E')
    {
        i++;
        int exponent = 0;
        int exponentSign = 1;

        if (string[i] == '-' || string[i] == '+')
        {
            if (string[i] == '-')
                exponentSign = -1;
            i++;
        }

        while (string[i] >= '0' && string[i] <= '9')
        {
            exponent = exponent * 10 + (string[i] - '0');
            i++;
        }

        double multiplier = 1.0;
        for (int j = 0; j < exponent; j++)
            multiplier *= 10.0;

        value *= pow(multiplier, exponentSign);
    }

    while (string[i] != '\0')
    {
        if (string[i] != ' ')
            return false;
        i++;
    }

    *result = value * sign;
    return true;
}
