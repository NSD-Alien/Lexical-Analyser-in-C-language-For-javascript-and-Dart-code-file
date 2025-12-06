// src/utils.c
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INIT_CAP 8  // initial capacity for StringList

//------------------------------------------------------
// STRING LIST
//------------------------------------------------------

void init_string_list(StringList *list) {
    list->cap = INIT_CAP;
    list->size = 0;
    list->items = malloc(sizeof(char*) * list->cap);
}

void push_string_list(StringList *list, const char *str) {
    if (list->size >= list->cap) {
        list->cap *= 2;
        list->items = realloc(list->items, sizeof(char*) * list->cap);
    }
    list->items[list->size++] = strdup(str);
}

int string_list_contains(StringList *list, const char *str) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->items[i], str) == 0)
            return 1;
    }
    return 0;
}

void free_string_list(StringList *list) {
    for (int i = 0; i < list->size; i++){
        free(list->items[i]);
    }
    free(list->items);
    list->items = NULL;
    list->size = 0;
    list->cap = 0;
}


//------------------------------------------------------
// IDENTIFIER HELPERS
//------------------------------------------------------

int is_identifier_start(char c) {
    return (isalpha((unsigned char)c) || c == '_' || c == '$');
}

int is_identifier_char(char c) {
    return (isalnum((unsigned char)c) || c == '_' || c == '$');
}


//------------------------------------------------------
// KEYWORD CHECK
//------------------------------------------------------

static const char *keywords[] = {
    "var","let","const","function","if","else","while","return",
    "final","class","void","import","library",
    NULL
};

int is_keyword(const char *s) {
    for (int i = 0; keywords[i]; i++) {
        if (strcmp(s, keywords[i]) == 0)
            return 1;
    }
    return 0;
}


//------------------------------------------------------
// LEVENSHTEIN DISTANCE
//------------------------------------------------------

int levenshtein(const char *s, const char *t) {
    int ls = (int)strlen(s);
    int lt = (int)strlen(t);

    int rows = ls + 1;
    int cols = lt + 1;

    int *d = malloc(rows * cols * sizeof(int));
    if (!d) return -1;

    for (int i = 0; i <= ls; i++)
        d[i * cols + 0] = i;
    for (int j = 0; j <= lt; j++)
        d[j] = j;

    for (int i = 1; i <= ls; i++) {
        for (int j = 1; j <= lt; j++) {
            int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
            int del = d[(i - 1) * cols + j] + 1;
            int ins = d[i * cols + (j - 1)] + 1;
            int sub = d[(i - 1) * cols + (j - 1)] + cost;

            int m = del;
            if (ins < m) m = ins;
            if (sub < m) m = sub;

            d[i * cols + j] = m;
        }
    }

    int result = d[ls * cols + lt];
    free(d);
    return result;
}


//------------------------------------------------------
// SAFER MISSPELLED KEYWORD CHECK
//------------------------------------------------------

int looks_like_keyword_misspell(const char *s, const char **kwlist) {
    int len = (int)strlen(s);

    if (len < 3)
        return 0;

    if (is_keyword(s))
        return 0;

    for (int i = 0; kwlist[i]; i++) {
        int d = levenshtein(s, kwlist[i]);
        if (d == 1)
            return 1;
    }

    return 0;
}
