/* symbol_table.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "global.h"

/* Define the initial size of the symbol table */


/* Symbol table array and its size */
static Symbol *symbolTable = NULL;
static int symbolCount = 0;
static int symbolCapacity = 0;

/* Function to initialize the symbol table */
void init_symbol_table() {
    symbolCapacity = INITIAL_SIZE;
    symbolTable = (Symbol *)malloc(symbolCapacity * sizeof(Symbol));
    if (!symbolTable) {
        fprintf(stderr, "Error: Unable to allocate memory for the symbol table.\n");
        exit(EXIT_FAILURE);
    }
}

/* Function to add a symbol to the table */
void add_symbol(const char *label, int address, SymbolType type) {
    char *label_copy; /* Declare variable for label copy */

    /* Check if we need to expand the symbol table */
    if (symbolCount >= symbolCapacity) {
        symbolCapacity *= 2;
        symbolTable = (Symbol *)realloc(symbolTable, symbolCapacity * sizeof(Symbol));
        if (!symbolTable) {
            fprintf(stderr, "Error: Unable to expand the symbol table.\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Allocate memory for the label and copy it manually */
    label_copy = (char *)malloc(strlen(label) + 1);
    if (!label_copy) {
        fprintf(stderr, "Error: Unable to allocate memory for label.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(label_copy, label);

    /* Add the new symbol to the table */
    symbolTable[symbolCount].label = label_copy;
    symbolTable[symbolCount].address = address;
    symbolTable[symbolCount].type = type;
    symbolCount++;
}

/* Function to find a symbol in the table */
Symbol *find_symbol(const char *label) {
    int i;
    for (i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].label, label) == 0) {
            return &symbolTable[i];
        }
    }
    return NULL;
}

/* Function to free the symbol table */
void free_symbol_table() {
    int i;
    for (i = 0; i < symbolCount; i++) {
        free(symbolTable[i].label);
    }
    free(symbolTable);
}
