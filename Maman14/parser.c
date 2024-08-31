/* parser.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "utils.h"
#include "global.h" /* Include global header */

/* Check if the line is empty or a comment */
int is_empty_or_comment(const char *line) {
    /* Skip leading whitespace */
    while (*line && isspace(*line)) {
        line++;
    }
    /* Check if the line is a comment (starting with ';') or empty */
    return (*line == ';' || *line == '\0');
}

/* Extract a label from the line if present */
char *extract_label(char *line) {
    char *labelEnd = strchr(line, ':');
    if (labelEnd != NULL) {
        int labelLength = labelEnd - line;
        char *label = (char *)malloc(labelLength + 1);
        if (label) {
            strncpy(label, line, labelLength);
            label[labelLength] = '\0';
        }
        /* Move line pointer past the label and colon */
        memmove(line, labelEnd + 1, strlen(labelEnd + 1) + 1);
        return label;
    }
    return NULL;
}

/* Parse instruction and operands from the line */
void parse_instruction(char *line, char **instruction, char **operands) {
    char *spacePos;

    /* Trim leading whitespace */
    while (*line && isspace(*line)) {
        line++;
    }

    /* Find the first space to split the instruction from the operands */
    spacePos = strchr(line, ' ');
    if (spacePos) {
        *spacePos = '\0'; /* Split the string */

        /* Allocate memory for instruction and copy it */
        *instruction = (char *)malloc(strlen(line) + 1);
        if (*instruction) {
            strcpy(*instruction, line);
        }

        /* Allocate memory for operands and copy them */
        *operands = (char *)malloc(strlen(spacePos + 1) + 1);
        if (*operands) {
            strcpy(*operands, spacePos + 1);
            trim_whitespace(*operands); /* Trim any extra whitespace */
        }
    } else {
        /* If no space, the line is just an instruction */
        *instruction = (char *)malloc(strlen(line) + 1);
        if (*instruction) {
            strcpy(*instruction, line);
        }
        *operands = NULL;
    }

    /* Trim any extra whitespace from the instruction */
    if (*instruction) {
        trim_whitespace(*instruction);
    }

    /* Check if operands contain registers */
    if (*operands && is_register(*operands)) {
        printf("Register detected: %s\n", *operands); /* Debug or log register detection */
    }
}
