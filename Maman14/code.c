/* code.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#include "symbolTable.h"
#include "utils.h"

/* Define the opcodes */
typedef struct {
    char *opcode;
    int arg_num;
} op_code;

/* Define opcode mappings */
op_code OPCODES[] = {
    {"mov",  2},
    {"cmp",  2},
    {"add",  2},
    {"sub",  2},
    {"not",  1},
    {"clr",  1},
    {"lea",  2},
    {"inc",  1},
    {"dec",  1},
    {"jmp",  1},
    {"bne",  1},
    {"red",  1},
    {"prn",  1},
    {"jsr",  1},
    {"rts",  0},
    {"stop", 0}
};

/* Define pseudo-instructions */
char *INSTRUCTIONS[] = {".data", ".string", ".extern", ".entry"};

/* Helper function to get opcode index */
int get_opcode_index(const char *instruction) {
    int i;
    for (i = 0; i < sizeof(OPCODES) / sizeof(OPCODES[0]); i++) {
        if (strcmp(instruction, OPCODES[i].opcode) == 0) {
            return i;
        }
    }
    return -1;  /* Not found */
}

/* Helper function to check if a string is a pseudo-instruction */
int is_pseudo_instruction(const char *instruction) {
    int i;
    for (i = 0; i < sizeof(INSTRUCTIONS) / sizeof(INSTRUCTIONS[0]); i++) {
        if (strcmp(instruction, INSTRUCTIONS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/* Function to generate machine code based on the instruction and operands */
void generate_machine_code(const char *instruction, const char *operands) {
    int opcode_index = get_opcode_index(instruction);
    char *operand1 = strtok((char *)operands, ",");
    char *operand2 = strtok(NULL, ",");

    /* Handle standard instructions */
    if (opcode_index != -1) {
        printf("Generated opcode: %d\n", opcode_index);

        /* Further processing of operands */


        if (operand1) {
            printf("Operand 1: %s\n", operand1);
            /* Add logic to resolve operand1 (register, memory, etc.) */
        }

        if (operand2) {
            printf("Operand 2: %s\n", operand2);
            /* Add logic to resolve operand2 (register, memory, etc.) */
        }
        return;
    }

    /* Handle pseudo-instructions and other specific cases */
    if (is_pseudo_instruction(instruction)) {
        printf("Handling pseudo-instruction: %s with operands: %s\n", instruction, operands);
        /* Add logic to handle pseudo-instructions (.data, .string, .extern, .entry) */
        return;
    }

    if (strcmp(instruction, "jmp") == 0 || strcmp(instruction, "stop") == 0) {
        printf("Handling special instruction: %s\n", instruction);
        /* Add logic to handle special instructions (jmp, stop) */
        return;
    }

    /* If the instruction is still not recognized, report an error */
    fprintf(stderr, "Error: Unknown instruction '%s'.\n", instruction);
}
