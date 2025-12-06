// include/errors.h
#ifndef ERRORS_H
#define ERRORS_H

#define MAX_ERR_DESC 512

typedef struct {
    char desc[MAX_ERR_DESC];
    int line;
} ErrorEntry;

typedef struct {
    ErrorEntry *arr;
    int size;
    int cap;
} ErrorList;

void init_error_list(ErrorList *e);
void push_error(ErrorList *e, const char *desc, int line);
void free_error_list(ErrorList *e);

#endif // ERRORS_H
