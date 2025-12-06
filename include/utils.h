#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

typedef struct {
    char **items;   // dynamic array of strings
    int size;       // number of stored strings
    int cap;        // capacity
} StringList;

void init_string_list(StringList *list);
void push_string_list(StringList *list, const char *str);
int string_list_contains(StringList *list, const char *str);
void free_string_list(StringList *list);

int levenshtein(const char *s, const char *t);

#endif // UTILS_H
