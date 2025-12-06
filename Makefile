CC=gcc
CFLAGS=-O2 -Wall -std=c11 -Iinclude

SRC=src/main.c src/lexer.c src/tokenizer.c src/comments.c src/symbols.c src/errors.c src/utils.c
TESTSRC=tests/test_runner.c src/lexer.c src/tokenizer.c src/comments.c src/symbols.c src/errors.c src/utils.c

all: lexer test_runner

lexer: $(SRC)
	$(CC) $(CFLAGS) -o lexer $(SRC)

test_runner: $(TESTSRC)
	$(CC) $(CFLAGS) -o tests/test_runner $(TESTSRC)

clean:
	rm -f lexer tests/test_runner
