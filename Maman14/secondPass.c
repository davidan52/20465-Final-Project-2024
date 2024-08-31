/* second_pass.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondPass.h"
#include "symbolTable.h"
#include "code.h"
#include "parser.h"
#include "utils.h"
#include "global.h"

/* Main function for the second pass */
void second_pass(FILE *inputFile) {
    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;

    /* Rewind the file to the beginning */
    rewind(inputFile);

    /* Read the file line by line */
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        lineNumber++;

        /* Trim newline character */
        trim_newline(line);

        /* Process the line: generate machine code and handle symbols */
        parse_line_second_pass(line, lineNumber);
    }

    /* Finalize the second pass (write machine code to output files) */
}

/* Function to parse a line during the second pass */
void parse_line_second_pass(char *line, int lineNumber) {
    char *label;
    char *instruction = NULL;
    char *operands = NULL;

    /* Check if the line is empty or a comment */
    if (is_empty_or_comment(line)) {
        return;
    }

    /* Extract label if present but ignore it during the second pass */
    label = extract_label(line);
    if (label) {
        free(label);
    }

    /* Parse instruction and operands */
    parse_instruction(line, &instruction, &operands);

    /* Trim any extra whitespace around instruction and operands */
    if (instruction) {
        trim_whitespace(instruction);  /* Ensure instruction is correctly formatted */
    }
    if (operands) {
        trim_whitespace(operands);  /* Ensure operands are correctly formatted */
    }

    if (instruction) {
        /* Generate machine code for the instruction */
        generate_machine_code(instruction, operands);
        free(instruction);
        if (operands) {
            free(operands);
        }
    }
}
