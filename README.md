# 🔍 Lexical Analyzer in C  
### Supports **JavaScript** and **Dart** Source Files  
A fully-custom, modular lexical analyzer implemented in **C**, capable of tokenizing JavaScript and Dart files with support for comments, identifiers, keywords, numbers, operators, punctuation, and error reporting.

---

## ✨ Features

### ✔ Multi-language Support  
- Detects and tokenizes **JavaScript**
- Detects and tokenizes **Dart**
- Uses file extension or explicit input to decide the language mode.

### ✔ Modular Architecture  
The project is divided into independent components:
- `lexer.c` → Reads input file line by line  
- `tokenizer.c` → Breaks each line into tokens  
- `utils.c` → Character checks, keyword checks, string helpers  
- `comments.c` → Extracts single & multi-line comments  
- `symbols.c` → Builds a symbol table  
- `errors.c` → Stores lexical errors  
- `main.c` → Final orchestrator  
- `Makefile` → For easy build/run

### ✔ Token Types Supported
- Keywords  
- Identifiers  
- Numbers  
- Operators  
- Punctuation  
- Strings  
- Comments  
- Errors (illegal tokens)

### ✔ Symbol Table  
Tracks all unique identifiers and tokens.

### ✔ Detailed Error Logging  
Reports invalid characters, unknown symbols, unterminated strings, or bad numeric patterns.

---

## 📁 Project Structure

| File | Purpose |
|------|---------|
| `src/main.c` | Entry point, handles overall flow |
| `src/lexer.c` | Reads file & coordinates tokenization |
| `src/tokenizer.c` | Core token generation logic |
| `src/utils.c` | Utility helpers for chars, keywords, identifiers |
| `src/comments.c` | Single & multi-line comment extraction |
| `src/symbols.c` | Symbol table management |
| `src/errors.c` | Error table management |
| `include/*.h` | Header files for each module |
| `Makefile` | Build automation |

---

## 🚀 How to Build & Run

### **Build**
```bash
make
