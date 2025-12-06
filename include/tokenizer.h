// include/tokenizer.h
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>

int is_keyword(const char *w);
int is_operator_token(const char *w);
int is_identifier_start(char c);
int is_identifier_char(char c);
int is_number_start(char c);

#endif // TOKENIZER_H
