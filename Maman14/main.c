#include <stdio.h>
#include <stdlib.h>
#include "firstPass.h"
#include "secondPass.h"
#include "symbolTable.h"

/* Declare the pre_assembler function */
void pre_assembler(const char *input_filename);

int main() {
    FILE *inputFile; /* Declare the file pointer at the beginning of the function */

    /* Run the pre-assembler to expand macros and create .am file */
    printf("Running Pre-Assembler...\n");
    pre_assembler("example.as");

    /* Attempt to open the generated .am file for the next passes */
    inputFile = fopen("example.am", "r"); /* Open the file after all declarations */
    if (!inputFile) {
        fprintf(stderr, "Error: Unable to open input file example.am.\n");
        return 1;
    }

    printf("Successfully opened example.am for processing.\n");

    /* Run the first pass to build the symbol table and prepare for the second pass */
    printf("Running First Pass...\n");
    first_pass(inputFile);

    /* Rewind the file to the beginning for the second pass */
    rewind(inputFile);

    /* Run the second pass to generate machine code and handle final output */
    printf("\nRunning Second Pass...\n");
    second_pass(inputFile);

    /* Clean up and free the symbol table */
    free_symbol_table();

    /* Close the input file */
    fclose(inputFile);
    printf("Processing completed and file closed.\n");
    return 0;
}
