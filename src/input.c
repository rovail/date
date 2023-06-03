#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include "input.h"
#include "convert.h"
#include "log.h"

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
        {
            log_message(LOG_DEBUG, "Invalid input: %s", response);
            printf("%s\n", error_msg);
        }
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
        {
            log_message(LOG_DEBUG, "Invalid input: %s", input);
            printf("%s\n", error_msg);
        }
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
        {
            log_message(LOG_DEBUG, "Invalid input: %s", input);
            printf("%s\n", error_msg);
        }
    }
}

char* ask_string(const char* msg, const char* error_msg)
{
    char input[100];
    char* result = malloc(100 * sizeof(char));

    while (true)
    {
        printf("%s ", msg);
        fgets(input, sizeof(input), stdin);

        size_t len = strlen(input);
        if (len > 0 && (input[len - 1] == '\n' || input[len - 1] == '\r'))
            input[len - 1] = '\0';

        if (strlen(input) > 0)
        {
            strcpy(result, input);
            return result;
        }
        else
        {
            log_message(LOG_DEBUG, "Invalid input: %s", input);
            printf("%s\n", error_msg);
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    free(result);
    return NULL;
}