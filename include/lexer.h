#ifndef LEXER_H
#define LEXER_H

#include "symbols.h"
#include "errors.h"
#include "comments.h"

typedef enum {
    LANG_JS,
    LANG_DART
} LanguageMode;

void process_file_lang(const char *filename, SymbolTable *symtbl, StringList *comments, ErrorList *errors, LanguageMode lang);

#endif // LEXER_H
