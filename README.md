# C Lexical Analyzer

A modular lexical analyzer written in C that reads a C source file, extracts lexemes, and classifies them into token categories. The project demonstrates fundamental compiler-design concepts through separate scanning, keyword lookup, and token-classification modules.

## Features

- Reads a C source file provided through the command line.
- Skips whitespace and single-line (`//`) and multi-line (`/* ... */`) comments.
- Extracts identifiers, keywords, numeric constants, string literals, character literals, operators, punctuation, and preprocessor directives.
- Classifies each extracted lexeme and prints its token category.
- Checks that an input filename has a `.c` extension and reports whether the file was opened successfully.
- Uses separate source and header files to keep the implementation modular.

## Technologies Used

- **Programming Language:** C
- **Standard Libraries:** `stdio.h`, `string.h`, `ctype.h`
- **Compiler:** GCC or Clang

## Project Structure

| File | Responsibility |
|---|---|
| `main.c` | Entry point. Validates command-line arguments and the `.c` extension, initializes the scanner, retrieves and classifies lexemes, prints token categories, and closes the file. |
| `scanner.c` | Reads the source file character by character. Skips whitespace and comments, and extracts preprocessor directives, identifiers, numeric lexemes, quoted literals, operators, and punctuation. |
| `scanner.h` | Declares the scanner interface for file initialization, character reading, lookahead, lexeme extraction, cleanup, and line-number access. |
| `classifier.c` | Classifies lexemes as keywords, identifiers, integer constants, floating-point constants, character constants, string constants, operators, punctuation, preprocessor directives, or invalid tokens. |
| `classifier.h` | Declares the `classify()` function used to determine a lexeme's token type. |
| `keywords.c` | Maintains the list of reserved C keywords and implements the keyword lookup function. |
| `keywords.h` | Declares the `is_keyword()` function for checking reserved keywords. |
| `token.h` | Defines `MAX_LEXEME_LEN`, the `TokenType` enumeration, and the `Token` structure containing a token type, lexeme, and line number. |

## How It Works

1. **Input Validation:** `main.c` expects one command-line argument and checks that the filename ends in `.c`.
2. **File Initialization:** The scanner opens the specified source file for reading.
3. **Lexeme Scanning:** `scanner_next_word()` extracts one lexeme at a time while skipping whitespace and comments.
4. **Token Classification:** `classify()` determines the token category, using `is_keyword()` to identify reserved keywords.
5. **Output:** The program prints each lexeme alongside its classification.
6. **Cleanup:** The scanner closes the source file after processing.

## Build and Run

Compile the source files using GCC:

```bash
gcc main.c scanner.c classifier.c keywords.c -o lexer
```

Run the analyzer by providing a C source file:

```bash
./lexer sample.c
```

Replace `sample.c` with the path to the C source file you want to analyze.

## Example

Given an input file named `sample.c`:

```c
#include <stdio.h>

int main(void)
{
    int count = 10;
    printf("Hello");
    return 0;
}
```

The output will contain entries similar to:

```text
Pre-Processor   : #include <stdio.h>
Keyword         : int
Identifier      : main
Punctuation     : (
...
Keyword         : return
Int Constant    : 0
Punctuation     : ;
```

The exact output depends on the lexemes found in the input file.

## Skills Demonstrated

- C programming and modular program design
- File handling using standard I/O
- Character-by-character input scanning
- String processing and character classification
- Lexical analysis and token categorization
- Header files and function interfaces
- Command-line argument validation
- Fundamental compiler-design concepts

## Scope and Limitations

This project implements a basic lexical analyzer for learning and demonstration. It is not a complete C language lexer or parser. The supported keyword list, operators, and punctuation are explicitly defined in the source code. The scanner recognizes selected two-character operators, while the classifier recognizes only its listed operators and punctuation. The project does not perform syntax analysis or validate the complete C grammar.

## Author

**Satheeswaran M**

- **Email:** [satheeswaran.vnr@gmail.com](mailto:satheeswaran.vnr@gmail.com)
- **LinkedIn:** [sathees-waran](https://www.linkedin.com/in/sathees-waran/)
