#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/symbols.h"
#include "../include/errors.h"
#include "../include/comments.h"

#define ASSERT(cond,msg) do{if(!(cond)){fprintf(stderr,"ASSERT FAILED: %s\n",msg); return 1;}}while(0)

int main(void){
    SymbolTable sym; init_symbol_table(&sym);
    StringList comments; init_string_list(&comments);
    ErrorList errors; init_error_list(&errors);

    // Run JS test
    process_file_lang("tests/big_test_input.js",&sym,&comments,&errors,LANG_JS);
    ASSERT(sym.size>0,"JS symbol table should have entries");
    ASSERT(comments.size>0,"JS comments should be extracted");

    free_symbol_table(&sym);
    free_string_list(&comments);
    free_error_list(&errors);

    // Run Dart test
    init_symbol_table(&sym); init_string_list(&comments); init_error_list(&errors);
    process_file_lang("tests/big_test_input.dart",&sym,&comments,&errors,LANG_DART);
    ASSERT(sym.size>0,"Dart symbol table should have entries");
    ASSERT(comments.size>0,"Dart comments should be extracted");

    free_symbol_table(&sym);
    free_string_list(&comments);
    free_error_list(&errors);

    printf("All tests passed.\n");
    return 0;
}
