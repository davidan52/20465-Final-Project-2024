#ifndef LABRATORY_C_FINAL_PROJECT_GLOBALS_H
#define LABRATORY_C_FINAL_PROJECT_GLOBALS_H

/* The File contains all the global values in the program */

#define MAX_MACRO_NAME 31
#define MAX_MACRO_CONTENT 1024
#define MAX_LINE_LENGTH 256
#define MAX_MACROS 100
#define INITIAL_SIZE 100

/* Declare the supported registers */
extern const char *REGISTERS[];
extern const int REG_COUNT;

/* Function prototype for checking if a string is a register */
int is_register(const char *operand);

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

#endif /* LABRATORY_C_FINAL_PROJECT_GLOBALS_H */
