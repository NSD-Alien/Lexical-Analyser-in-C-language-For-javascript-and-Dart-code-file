#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <stdio.h>
#include "utils.h"

#define MAX_TOKEN_LEN 256

typedef struct {
    char token[MAX_TOKEN_LEN];
    char attr[MAX_TOKEN_LEN];
} SymbolEntry;

typedef struct {
    SymbolEntry *arr;
    int size;
    int cap;
} SymbolTable;

void init_symbol_table(SymbolTable *t);
void add_symbol(SymbolTable *t, const char *token, const char *attr);
void free_symbol_table(SymbolTable *t);

#endif // SYMBOLS_H
