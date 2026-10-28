/*
 * classifier.c
 * Determines the TokenType of a lexeme (keyword, identifier, literal,
 * operator, punctuation, or preprocessor directive).
 */
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "keywords.h"

int classify(char *buff)
{
    int i = 0;

    if (buff[0] == '#')
    {
        return PREPROCESSOR;
    }
    
    /* Keyword */
    if (is_keyword(buff))
    {
        return KEYWORD;
    }

    

    /* Identifier */
    if (isalpha(buff[0]) || buff[0] == '_')
    {
        i = 1;

        while (buff[i] != '\0')
        {
            if (!isalnum(buff[i]) && buff[i] != '_')
            {
                return INVALID;
            }

            i++;
        }

        return IDENTIFIER;
    }

    /* Integer / Float */
    if (isdigit(buff[0]))
    {
        int dot_count = 0;

        for (i = 0; buff[i] != '\0'; i++)
        {
            if (buff[i] == '.')
            {
                dot_count++;
            }
            else if (!isdigit(buff[i]))
            {
                return INVALID;
            }
        }

        if (dot_count == 0)
        {
            return INT_CONST;
        }

        if (dot_count == 1)
        {
            return FLOAT_CONST;
        }

        return INVALID;
    }

    /* String literal */
    if (buff[0] == '"' && buff[strlen(buff) - 1] == '"')
    {
        return STRING_CONST;
    }

    /* Character literal */
    if (buff[0] == '\'' && buff[strlen(buff) - 1] == '\'')
    {
        return CHAR_CONST;
    }
    /* Operators */
    if (strcmp(buff, "=") == 0 ||
        strcmp(buff, "+") == 0 ||
        strcmp(buff, "-") == 0 ||
        strcmp(buff, "*") == 0 ||
        strcmp(buff, "/") == 0 ||
        strcmp(buff, "%") == 0 ||
        strcmp(buff, "==") == 0 ||
        strcmp(buff, "!=") == 0 ||
        strcmp(buff, "<") == 0 ||
        strcmp(buff, ">") == 0 ||
        strcmp(buff, "<=") == 0 ||
        strcmp(buff, ">=") == 0 ||
        strcmp(buff, "++") == 0 ||
        strcmp(buff, "--") == 0 ||
        strcmp(buff, "+=") == 0 ||
        strcmp(buff, "-=") == 0 ||
        strcmp(buff, "*=") == 0 ||
        strcmp(buff, "/=") == 0 ||
        strcmp(buff, "%=") == 0 ||
        strcmp(buff, "&&") == 0 ||
        strcmp(buff, "||") == 0 ||
        strcmp(buff, "!") == 0)
    {
        return OPERATOR;
    }

    /* Punctuation */
    if (strcmp(buff, "(") == 0 ||
        strcmp(buff, ")") == 0 ||
        strcmp(buff, "{") == 0 ||
        strcmp(buff, "}") == 0 ||
        strcmp(buff, "[") == 0 ||
        strcmp(buff, "]") == 0 ||
        strcmp(buff, ";") == 0 ||
        strcmp(buff, ",") == 0)
    {
        return PUNCTUATION;
    }

    return INVALID;
}