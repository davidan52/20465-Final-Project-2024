/* first_pass.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "firstPass.h"
#include "symbolTable.h"
#include "parser.h"
#include "utils.h"
#include "global.h"

/* Main function for the first pass */
void first_pass(FILE *inputFile) {
    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;

    /* Initialize the symbol table */
    init_symbol_table();

    /* Read the file line by line */
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        lineNumber++;

        /* Trim newline character */
        trim_newline(line);

        /* Parse the line: check for labels, instructions, and operands */
        parse_line_first_pass(line, lineNumber);
    }

    /* Finalize the first pass (additional processing if needed) 
       Could include error checks or other table adjustments */
}

/* Function to parse a line during the first pass */
void parse_line_first_pass(char *line, int lineNumber) {
    char *label;
    char *instruction = NULL;
    char *operands = NULL;

    /* Check if the line is empty or a comment */
    if (is_empty_or_comment(line)) {
        return;
    }

    /* Extract the label if it exists */
    label = extract_label(line);
    if (label != NULL) {
        /* Add the label to the symbol table with a dummy address (to be updated later) */
        add_symbol(label, 0, CODE);
        free(label);
    }

    /* Parse instruction and operands from the line */
    parse_instruction(line, &instruction, &operands);

    if (instruction) {
        /* Process instruction and operands (logic to be added in the second pass) */
        printf("Instruction: %s, Operands: %s\n", instruction, operands ? operands : "None");
        free(instruction);
        if (operands) {
            free(operands);
        }
    }
}
