/* utils.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

/* Function to trim leading and trailing whitespace from a string */
char *trim_whitespace(char *str) {
    char *end;

    /* Trim leading spaces */
    while (isspace((unsigned char)*str)) str++;

    /* If the string is all spaces, return an empty string */
    if (*str == 0)
        return str;

    /* Trim trailing spaces */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    /* Write new null terminator */
    *(end + 1) = '\0';

    return str;
}

/* Function to remove newline characters from a string */
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/* Function to print an error message and exit */
void error_exit(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}
