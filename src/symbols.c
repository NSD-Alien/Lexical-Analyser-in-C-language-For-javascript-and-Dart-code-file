#include "symbols.h"
#include <stdlib.h>
#include <string.h>

#define INIT_CAP 256

void init_symbol_table(SymbolTable *t) {
    t->cap = INIT_CAP; t->size = 0;
    t->arr = malloc(sizeof(SymbolEntry)*t->cap);
}

void add_symbol(SymbolTable *t, const char *token, const char *attr) {
    for (int i=0;i<t->size;i++){
        if (strcmp(t->arr[i].token, token)==0 && strcmp(t->arr[i].attr, attr)==0) return;
    }
    if (t->size >= t->cap) {
        t->cap *= 2;
        t->arr = realloc(t->arr, sizeof(SymbolEntry)*t->cap);
    }
    strncpy(t->arr[t->size].token, token, MAX_TOKEN_LEN-1);
    t->arr[t->size].token[MAX_TOKEN_LEN-1]=0;
    strncpy(t->arr[t->size].attr, attr, MAX_TOKEN_LEN-1);
    t->arr[t->size].attr[MAX_TOKEN_LEN-1]=0;
    t->size++;
}

void free_symbol_table(SymbolTable *t) {
    if (t->arr) free(t->arr);
    t->arr = NULL; t->size = 0; t->cap = 0;
}
