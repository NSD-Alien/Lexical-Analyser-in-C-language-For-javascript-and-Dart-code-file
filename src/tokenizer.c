// src/tokenizer.c
#include "tokenizer.h"
#include "utils.h"     // for is_keyword, identifier helpers
#include <string.h>
#include <ctype.h>

//------------------------------------------------------
// Operator table
//------------------------------------------------------

static const char *operators[] = {
    "+","-","*","/","%","=","==","===","!=","!==",
    ">",">=","<","<=","&&","||","!","++","--",
    "+=","-=","*=","/=","=>"
};
static int operator_count = sizeof(operators)/sizeof(operators[0]);

//------------------------------------------------------
// Tokenizer helper functions (NO duplicates from utils.c)
//------------------------------------------------------

int is_operator_token(const char *w) {
    for (int i = 0; i < operator_count; i++)
        if (strcmp(w, operators[i]) == 0)
            return 1;
    return 0;
}

int is_number_start(char c) {
    return isdigit((unsigned char)c);
}
