#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include "log.h"
#include "input.h"
#include "convert.h"

YESNO ask_yes_no(const char* msg, const char* error_msg)
{
    char response[10];

    while (true)
    {
        printf("%s ", msg);
        fgets(response, sizeof(response), stdin);

        if (response[0] == 'y' || response[0] == 'Y')
            return YES;
        else if (response[0] == 'n' || response[0] == 'N')
            return NO;
        else
            printf("%s\n", error_msg);
    }
}

int ask_int(const char* msg, const char* error_msg)
{
    char input[100];

    while (true)
    {
        printf("%s ", msg);
        fgets(input, sizeof(input), stdin);

        int value;
        if (try_convert_to_int(input, &value))
            return value;
        else
            printf("%s\n", error_msg);
    }
}

double ask_double(const char* msg, const char* error_msg)
{
    char input[100];

    while (true)
    {
        printf("%s ", msg);
        fgets(input, sizeof(input), stdin);

        size_t len = strlen(input);
        if (len > 0 && (input[len - 1] == '\n' || input[len - 1] == '\r'))
            input[len - 1] = '\0';

        double value;
        if (try_convert_to_double(input, &value))
            return value;
        else
            printf("%s\n", error_msg);
    }
}

char* ask_string(const char* msg, const char* error_msg)
{
    char* input = malloc(100 * sizeof(char));

    while (true)
    {
        printf("%s ", msg);
        fgets(input, sizeof(input), stdin);

        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] = '\0';

        if (strlen(input) > 0)
            return input;
        else
            printf("%s\n", error_msg);
    }
}