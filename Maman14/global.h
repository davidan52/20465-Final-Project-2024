/*  global.h */
#ifndef LABRATORY_C_FINAL_PROJECT_GLOBALS_H
#define LABRATORY_C_FINAL_PROJECT_GLOBALS_H
/* The File contains all the global values in the program */

/* Maximum length of a label in command line */
#define MAX_LABEL_LENGTH 31

/* Maximum length of a single command line */
#define MAX_LINE_LENGTH 81

/* Default IC value */
#define IC_INIT_VALUE 100

/* Arbitrary very big number for line length */
#define BIG_NUMBER_CONST 1000

/* Number of opcodes in the assembler */
#define OPCODES_COUNT 16

/* Number of registers available */
#define REG_COUNT 8

/* Length of a machine code word */
#define WORD_LEN 12

/* Number of bits for ARE (Absolute, Relocatable, External) */
#define ARE_BITS 2

/* Value for relocatable symbol */
#define RELOCATABLE_VALUE 2

/* Value for external symbol */
#define EXTERNAL_VALUE 1

/* Number of instruction types (e.g., .data, .string, etc.) */
#define INSTRUCTIONS_COUNT 4

/* Maximum value for 6-bit numbers */
#define SIX_BITS_MAX 63

/* Number of bits in a sextet */
#define SIX_BITS 6

/* Number of sextets in a word */
#define NUM_SEXTETES 2

/* Maximum numeric value based on word length */
#define MAX_NUM ((1 << (WORD_LEN-1)) - 1)

/* Minimum numeric value based on word length */
#define MIN_NUM (-(1 << (WORD_LEN-1)))

/* Structure to track location information for error reporting */
typedef struct location {
    char *file_name;  /*  Name of the source file  */
    int line_num;     /*  Line number in the source file  */
} location;

/* Structure to define a line in the assembler */
typedef struct line_data {
    char *file_name;  /*  File name for error reporting */
    short number;     /*  Line number for tracking  */
    char *data;       /*  Content of the line  */
} line_data;

#endif /*  LABRATORY_C_FINAL_PROJECT_GLOBALS_H */
