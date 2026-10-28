/**
 * @file  main.c
 * @brief Entry point for the lexical analyzer. Opens a .c source file,
 *        scans it into lexemes, classifies each token, and prints the
 *        token stream to stdout.
 * @author Sathees Waran
 */

#include <stdio.h>
#include <string.h>
#include "token.h"
#include "keywords.h"
#include "scanner.h"
#include "classifier.h"

int main(int argc, char *argv[])
{
    /* ---- Step 1: validate argument count ---- */
    if (argc != 2)
    {
        printf("Input file not passed!!\n");
        return 0;
    }

    /* ---- Step 2: validate file extension is ".c" ---- */
    int len = strlen(argv[1]);
    if (len < 3 || argv[1][len - 2] != '.' || argv[1][len - 1] != 'c')
    {
        printf("Wrong input Error!!\n");
        return 0;
    }

    /* ---- Step 3: open the source file via scanner ---- */
    int ret = scanner_init(argv[1]);
    if (ret == 0)
    {
        printf("Open : %s : Failure\n", argv[1]);
        return 0;
    }
    else
    {
        printf("Open : %s : Success\n", argv[1]);
    }

    printf("Parsing : %s : Started\n", argv[1]);

    /* ---- Step 4: main tokenizing loop ---- */
    char buff[MAX_LEXEME_LEN];
    while (scanner_next_word(buff) == 1)
    {
        TokenType type = classify(buff);
        const char *label;

        switch (type)
        {
        case KEYWORD:
            label = "Keyword";
            break;
        case IDENTIFIER:
            label = "Identifier";
            break;
        case OPERATOR:
            label = "Operator";
            break;
        case PUNCTUATION:
            label = "Punctuation";
            break;
        case PREPROCESSOR:
            label = "Pre-Processor";
            break;
        case INT_CONST:
            label = "Int Constant";
            break;
        case FLOAT_CONST:
            label = "Float Constant";
            break;
        case CHAR_CONST:
            label = "Char Constant";
            break;
        case STRING_CONST:
            label = "String Constant";
            break;
        default:
            label = "Invalid";
        }

        printf("%-16s: %s\n", label, buff);
    }

    printf("\n");
    printf("Parsing : %s : Done\n", argv[1]);

    /* ---- Step 5: cleanup ---- */
    scanner_close();

    return 0;
}