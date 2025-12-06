// src/errors.c
#include "errors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INIT_CAP 256

void init_error_list(ErrorList *e) {
    e->cap = INIT_CAP; e->size = 0; e->arr = malloc(sizeof(ErrorEntry)*e->cap);
}
void push_error(ErrorList *e, const char *desc, int line) {
    if (e->size >= e->cap) { e->cap *= 2; e->arr = realloc(e->arr, sizeof(ErrorEntry)*e->cap); }
    strncpy(e->arr[e->size].desc, desc, MAX_ERR_DESC-1);
    e->arr[e->size].desc[MAX_ERR_DESC-1]=0;
    e->arr[e->size].line = line;
    e->size++;
}
void free_error_list(ErrorList *e) {
    if (e->arr) free(e->arr);
    e->arr = NULL; e->size = 0; e->cap = 0;
}
