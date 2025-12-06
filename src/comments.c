#include "comments.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
   extract_comments_from_line:
   - Detect single-line comments using "//"
   - Detect multi-line comments using markers like [start] and [end] to avoid C comment syntax
   - Store all extracted comments into a StringList
   - Update line number when reading multi-line comments
*/

void extract_comments_from_line(const char *line, StringList *comments, FILE *f, int *lineno) {

    const char *sl = strstr(line, "//");  // single-line comment start
    const char *ml = strstr(line, "/*");  // multi-line comment start

    // Case 1: single-line comment occurs before multi-line comment
    if (sl && (!ml || sl < ml)) {
        push_string_list(comments, sl);
        return;
    }

    // Case 2: multi-line comment found
    if (ml) {
        const char *end = strstr(ml + 2, "*/");

        // Multi-line comment ends on the same line
        if (end) {
            int len = (int)(end - ml) + 2;  // include "*/"
            char *buf = malloc(len + 1);
            if (!buf) return;

            strncpy(buf, ml, len);
            buf[len] = '\0';

            push_string_list(comments, buf);
            free(buf);
            return;
        }

        // Multi-line comment spans multiple lines
        size_t cap = 4096;
        char *acc = malloc(cap);
        if (!acc) return;

        acc[0] = '\0';
        strncat(acc, ml, strlen(ml));

        char more[1024];

        while (fgets(more, sizeof(more), f)) {
            (*lineno)++;

            // Expand buffer if needed
            if (strlen(acc) + strlen(more) + 2 > cap) {
                cap *= 2;
                acc = realloc(acc, cap);
                if (!acc) return;
            }

            strcat(acc, more);

            if (strstr(more, "*/"))  // end of multi-line comment
                break;
        }

        push_string_list(comments, acc);
        free(acc);
    }
}
