#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* Include for isspace function */
#include "utils.h" /* Include utils for trim_whitespace function */

/* Define a simple macro structure */
typedef struct {
    char name[31];
    char content[1024];
} Macro;

/* Function to process the input file and create .am file */
void pre_assembler(const char *input_filename) {
    char output_filename[256];
    FILE *input_file;
    FILE *output_file;
    char line[256];
    Macro macros[100];  /* Array to store macros */
    int macro_count = 0;
    int in_macro = 0;  /* Flag to indicate inside macro definition */
    char current_macro[31];
    char macro_content[1024] = "";
    int i;
    int expanded = 0;
    char *dot_position;

    /* Open the input file */
    input_file = fopen(input_filename, "r");
    if (!input_file) {
        fprintf(stderr, "Error: Unable to open input file %s.\n", input_filename);
        exit(EXIT_FAILURE);
    }

    /* Create the output file name with `.am` extension */
    dot_position = strchr(input_filename, '.');
    if (dot_position) {
        size_t prefix_length = dot_position - input_filename;
        strncpy(output_filename, input_filename, prefix_length);
        output_filename[prefix_length] = '\0';
    } else {
        strcpy(output_filename, input_filename);
    }
    strcat(output_filename, ".am");

    /* Open the output file */
    output_file = fopen(output_filename, "w");
    if (!output_file) {
        fprintf(stderr, "Error: Unable to create output file %s.\n", output_filename);
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    /* Read the input file line by line */
    while (fgets(line, sizeof(line), input_file)) {
        char *trimmed_line = trim_whitespace(line); /* Use trim_whitespace from utils.h */

        /* Skip comments and empty lines */
        if (trimmed_line[0] == ';' || trimmed_line[0] == '\0') {
            continue;
        }

        /* Check if inside a macro definition */
        if (in_macro) {
            if (strstr(trimmed_line, "endm")) {
                in_macro = 0;
                strcpy(macros[macro_count].name, current_macro);
                strcpy(macros[macro_count].content, macro_content);
                macro_count++;
                macro_content[0] = '\0';  /* Clear macro content */
            } else {
                strcat(macro_content, trimmed_line);
                strcat(macro_content, "\n");
            }
            continue;
        }

        /* Detect macro start */
        if (strstr(trimmed_line, "macro")) {
            in_macro = 1;
            sscanf(trimmed_line, "macro %s", current_macro);
            continue;
        }

        /* Expand macros */
        expanded = 0;  /* Reset expanded flag */
        for (i = 0; i < macro_count; i++) {
            if (strstr(trimmed_line, macros[i].name)) {
                fputs(macros[i].content, output_file);
                expanded = 1;
                break;
            }
        }

        /* Write line to output if not a macro */
        if (!expanded) {
            fputs(trimmed_line, output_file);
            fputc('\n', output_file);
        }
    }

    /* Close the files */
    fclose(input_file);
    fclose(output_file);

    printf("Pre-assembly completed. Output written to %s\n", output_filename);
}
