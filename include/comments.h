#ifndef COMMENTS_H
#define COMMENTS_H

#include <stdio.h>
#include "utils.h"

void extract_comments_from_line(const char *line, StringList *comments, FILE *f, int *lineno);

#endif // COMMENTS_H
