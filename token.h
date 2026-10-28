
/*
 * token.h
 * Defines TokenType enum and Token struct shared across all lexer modules.
 */

#ifndef TOKEN_H
#define TOKEN_H

#define MAX_LEXEME_LEN 256

typedef enum
{
    KEYWORD,
    IDENTIFIER,
    INT_CONST,
    FLOAT_CONST,
    CHAR_CONST,
    STRING_CONST,
    OPERATOR,
    PUNCTUATION,
    PREPROCESSOR,
    EOF_TOKEN,
    INVALID
} TokenType;

typedef struct
{
    TokenType type;              /* what kind of token this is */
    char lexeme[MAX_LEXEME_LEN]; /* the actual text matched */
    int line_no;                 /* source line, for error messages */
} Token;

#endif