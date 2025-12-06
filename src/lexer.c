// src/lexer.c
#include "lexer.h"
#include "tokenizer.h"
#include "utils.h"
#include "symbols.h"
#include "errors.h"
#include "comments.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void process_file_lang(const char *filename, SymbolTable *symtbl, StringList *comments, ErrorList *errors, LanguageMode lang) {
    FILE *f = fopen(filename, "r");
    if (!f) { perror("fopen"); return; }

    init_symbol_table(symtbl);
    init_string_list(comments);
    init_error_list(errors);
    StringList declared; init_string_list(&declared);

    char linebuf[2048];
    int lineno = 0;

    // Keyword lists
    const char *js_keywords[]   = { "var", "let", "const", "function", "if", "else", "while", "return", NULL };
    const char *dart_keywords[] = { "var", "final", "const", "class", "void", "if", "else", "while", "return", "import", "library", NULL };
    const char **kwlist = (lang == LANG_JS) ? js_keywords : dart_keywords;

    // Read file line by line
    while(fgets(linebuf, sizeof(linebuf), f)) {
        lineno++;
        int i = 0;
        int L = (int)strlen(linebuf);

        // Extract comments (may advance lineno if multiline comment consumes further lines)
        extract_comments_from_line(linebuf, comments, f, &lineno);

        // Remove single-line comments
        char *pos_sl = strstr(linebuf, "//");
        if(pos_sl) *pos_sl = '\0';
        L = (int)strlen(linebuf); // recalc length after truncation

        // Tokenization loop
        while(i < L) {
            char c = linebuf[i];
            if(isspace((unsigned char)c)) { i++; continue; }

            // String literal
            if(c == '"' || c == '\'') {
                char quote = c;
                char tok[512] = {0}; int k = 0;
                tok[k++] = c; i++;
                while(i < L && linebuf[i] != quote) {
                    if(linebuf[i] == '\\' && i+1 < L) { tok[k++] = linebuf[i++]; tok[k++] = linebuf[i++]; }
                    else tok[k++] = linebuf[i++];
                    if(k >= 511) break;
                }
                if(i < L) tok[k++] = linebuf[i++];
                tok[k] = 0;
                add_symbol(symtbl, tok, "string literal");
                continue;
            }

            // Number literal
            if(isdigit((unsigned char)c)) {
                char tok[512]; int k = 0;
                while(i < L && (isdigit((unsigned char)linebuf[i]) || linebuf[i] == '.')) tok[k++] = linebuf[i++];
                tok[k] = 0;
                add_symbol(symtbl, tok, "number");
                continue;
            }

            // Identifier or keyword
            if(is_identifier_start(c)) {
                char tok[512]; int k = 0;
                int startpos = i;
                while(i < L && is_identifier_char(linebuf[i])) tok[k++] = linebuf[i++];
                tok[k] = 0;

                if(is_keyword(tok)) add_symbol(symtbl, tok, "keyword");
                else add_symbol(symtbl, tok, "identifier");

                // Declaration detection (still simple, per-line prefix)
                char prefix[512] = {0};
                int back = startpos - 1;
                if(back > 0) {
                    int plen = back; if(plen > 500) plen = 500;
                    strncpy(prefix, linebuf, plen); prefix[plen] = 0;
                    if((lang==LANG_JS && (strstr(prefix,"var")||strstr(prefix,"let")||strstr(prefix,"const"))) ||
                       (lang==LANG_DART && (strstr(prefix,"var")||strstr(prefix,"final")||strstr(prefix,"const")))) {
                        if(!string_list_contains(&declared, tok)) push_string_list(&declared, tok);
                    }
                }

                // ---- Inline heuristic: misspelled keyword detection (do here so we have correct lineno) ----
                // Only for identifiers that are long enough and not real keywords.
                int tlen = (int)strlen(tok);
                if(tlen >= 3 && !is_keyword(tok)) {
                    for(int kidx = 0; kwlist[kidx]; kidx++){
                        int d = levenshtein(tok, kwlist[kidx]);
                        // Be conservative: report only distance == 1 (very likely a typo)
                        if(d == 1) {
                            char buf[512];
                            snprintf(buf, sizeof(buf), "Possible misspelled keyword '%s' (close to '%s')", tok, kwlist[kidx]);
                            push_error(errors, buf, lineno);
                            break;
                        }
                    }
                }

                // NOTE: removed "undeclared identifier" checks from lexer — that belongs to the parser/semantic phase.
                continue;
            }

            // Operators multi-char
            int matched = 0;
            for(int oplen = 3; oplen >= 1; oplen--) {
                if(i + oplen <= L) {
                    char tmp[5] = {0}; strncpy(tmp, &linebuf[i], oplen);
                    for(int t=0; t<oplen; t++) if(isspace((unsigned char)tmp[t])) tmp[t]=0;
                    if(strlen(tmp) == 0) continue;
                    if(is_operator_token(tmp)) {
                        add_symbol(symtbl,tmp,"operator");

                        // Inline operator heuristic: flag '=>' placement at the correct line
                        if(strcmp(tmp, "=>") == 0) {
                            push_error(errors, "Found '=>' operator — check placement.", lineno);
                        }

                        i+=oplen; matched=1; break;
                    }
                }
            }
            if(matched) continue;

            // Punctuation
            char single[2] = {linebuf[i],0}; add_symbol(symtbl,single,"punct"); i++;
        }
    }

    fclose(f);

    // -------------------- Write Comments --------------------
    FILE *cf = fopen("comments.txt","w");
    if(cf){
        fprintf(cf,"Comments extracted from %s\n\n", filename);
        for(int i=0; i<comments->size; i++){
            fprintf(cf,"%s", comments->items[i]);
            if(comments->items[i][strlen(comments->items[i])-1] != '\n')
                fprintf(cf,"\n");
        }
        fclose(cf);
    }

    free_string_list(&declared);
}
