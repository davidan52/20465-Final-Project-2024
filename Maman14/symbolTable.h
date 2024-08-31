/* symbol_table.h */
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "global.h"  /* Include global.h if needed for common constants */

/* Define symbol types */
typedef enum {
    CODE,
    DATA,
    EXTERNAL
} SymbolType;

/* Define a struct to represent a symbol */
typedef struct {
    char *label;       /* Label name of the symbol */
    int address;       /* Address of the symbol */
    SymbolType type;   /* Type of the symbol (CODE, DATA, EXTERNAL) */
} Symbol;

/* Initialize the symbol table */
void init_symbol_table();

/* Add a symbol to the table */
void add_symbol(const char *label, int address, SymbolType type);

/* Find a symbol in the table */
Symbol *find_symbol(const char *label);

/* Free the symbol table */
void free_symbol_table();

#endif /* SYMBOL_TABLE_H */
