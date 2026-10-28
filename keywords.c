/*
 * keywords.c
 * Checks whether a given lexeme is a C reserved keyword.
 */

#include <stdio.h>
#include <string.h>
#include "keywords.h"
#include "token.h"

static char *reserved_kword[] = {"const", "volatile", "auto", "register", "extern",
                                 "static", "signed", "unsigned", "short", "long",
                                 "double", "char", "int", "float", "struct",
                                 "union", "enum", "void", "typedef", "goto",
                                 "return", "continue", "break", "if", "else",
                                 "for", "while", "do", "switch", "case", "default", "sizeof", ""};

int is_keyword(const char *lexeme)
{

    for (int i = 0; strcmp(reserved_kword[i], "") != 0; i++)
    {
        if (strcmp(lexeme, reserved_kword[i]) == 0)
        {
          return 1;
        }
    }
    return 0;
}