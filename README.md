# JS Lexical Analyzer (C) - Modular

## Build (macOS)
Requirements: `gcc` (Xcode command line tools)

1. Open Terminal.
2. Navigate to project root (where Makefile is).
3. Run:
	example: ./lexer big_test_input.js 


Project structure:
js_lexer_c/                   <- project root
├─ include/
│  ├─ lexer.h
│  ├─ tokenizer.h
│  ├─ comments.h
│  ├─ symbols.h
│  ├─ errors.h
│  └─ utils.h
├─ src/
│  ├─ main.c
│  ├─ lexer.c
│  ├─ tokenizer.c
│  ├─ comments.c
│  ├─ symbols.c
│  ├─ errors.c
│  └─ utils.c
├─ tests/
│  ├─ test_runner.c
│  └─ big_test_input.js    <- 150+ line JS file
├─ Makefile
└─ README.md
