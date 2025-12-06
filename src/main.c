#include <stdio.h>
#include <string.h>
#include "lexer.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr,"Usage: %s <filename> <js|dart>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    LanguageMode lang = (strcmp(argv[2],"dart")==0) ? LANG_DART : LANG_JS;

    SymbolTable sym;
    StringList comments;
    ErrorList errors;

    process_file_lang(filename, &sym, &comments, &errors, lang);

    // Print symbol table
    printf("==== SYMBOL TABLE (%d entries) ====\n", sym.size);
    for (int i=0;i<sym.size;i++)
        printf("%-30s | %s\n", sym.arr[i].token, sym.arr[i].attr);

    // Print errors
    printf("\n==== ERRORS (%d) ====\n", errors.size);
    for (int i=0;i<errors.size;i++)
        printf("%d: %s (line %d)\n", i+1, errors.arr[i].desc, errors.arr[i].line);

    // cleanup
    free_symbol_table(&sym);
    free_string_list(&comments);
    free_error_list(&errors);

    return 0;
}
