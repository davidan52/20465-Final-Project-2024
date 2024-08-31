#include <stdio.h>   /* Include to ensure functions like sprintf are recognized */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"  /* Include utils.h to use trim_whitespace */
#include "global.h"


/* Define a simple macro structure */
typedef struct {
    char name[MAX_MACRO_NAME];
    char content[MAX_MACRO_CONTENT];
} Macro;

/* Function to create a duplicate of a string (replacement for strdup) */
char *my_strdup(const char *s) {
    char *d = malloc(strlen(s) + 1);   /* Allocate memory */
    if (d == NULL) return NULL;        /* Handle memory allocation failure */
    strcpy(d, s);                      /* Copy the string */
    return d;
}

/* Function to process the input file and create .am file */
void pre_assembler(const char *input_filename) {
    char output_filename[256];
    FILE *input_file, *output_file;
    Macro macros[MAX_MACROS];
    int macro_count = 0, in_macro = 0;
    int expanded = 0; /* Declare expanded at the start of the function */
    int i; /* Declare the loop variable outside of the for loop */
    char current_macro[MAX_MACRO_NAME];
    char macro_content[MAX_MACRO_CONTENT] = "";
    char line[MAX_LINE_LENGTH];

    /* Create output filename by replacing extension with ".am" */
    char *temp_filename = my_strdup(input_filename);
    char *dot_position = strchr(temp_filename, '.');
    if (dot_position) *dot_position = '\0';  /* Remove extension */
    sprintf(output_filename, "%s.am", temp_filename);  /* Use sprintf instead of snprintf */
    free(temp_filename);

    input_file = fopen(input_filename, "r");
    output_file = fopen(output_filename, "w");

    if (!input_file || !output_file) {
        fprintf(stderr, "Error: Unable to open input or output file.\n");
        exit(EXIT_FAILURE);
    }

    /* Read the input file line by line */
    while (fgets(line, sizeof(line), input_file)) {
        char *trimmed_line = trim_whitespace(line);  /* Use the function from utils.h */

        /* Check if inside a macro definition */
        if (in_macro) {
            if (strstr(trimmed_line, "endm")) {
                in_macro = 0;
                strcpy(macros[macro_count].name, current_macro);
                strcpy(macros[macro_count].content, macro_content);
                macro_count++;
                macro_content[0] = '\0';
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
        expanded = 0;  /* Reset expanded for each line */
        for (i = 0; i < macro_count; i++) {
            if (strcmp(trimmed_line, macros[i].name) == 0) {
                fputs(macros[i].content, output_file);
                expanded = 1;
                break;
            }
        }

        /* Write line to output if not a macro */
        if (!expanded && trimmed_line[0] != ';' && strlen(trimmed_line) > 0) {
            fputs(trimmed_line, output_file);
            fputc('\n', output_file);
        }
    }

    /* Close the files */
    fclose(input_file);
    fclose(output_file);

    printf("Pre-assembly completed. Output written to %s\n", output_filename);
}
