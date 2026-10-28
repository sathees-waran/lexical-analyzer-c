/*
 * scanner.c
 * Reads a .c source file character by character and assembles lexemes,
 * skipping whitespace and comments, handling strings, numbers, operators,
 * and preprocessor directives.
 */

#include <stdio.h>
#include <ctype.h>

#include "token.h"
#include "scanner.h"

static FILE *fp = NULL;
static int current_line = 1;

int scanner_init(const char *filename)
{
   fp = fopen(filename, "r");

   if (fp == NULL)
   {
      return 0;
   }

   current_line = 1;

   return 1;
}

int scanner_next_char(void)
{
   int ch;

   ch = fgetc(fp);

   if (ch == '\n')
   {
      current_line++;
   }

   return ch;
}

int scanner_peek(void)
{
   int ch;

   ch = fgetc(fp);

   if (ch != EOF)
   {
      ungetc(ch, fp);
   }

   return ch;
}

int scanner_next_word(char *buff)
{
   int ch;
   int i = 0;

   /* Skip whitespace */
   do
   {
      ch = scanner_next_char();

   } while (ch == ' ' || ch == '\t' || ch == '\n');

   /* End of file */
   if (ch == EOF)
   {
      return 0;
   }

   /* Skip comments */

   if (ch == '/')
   {
      int next = scanner_peek();

      /* Single-line comment */
      if (next == '/')
      {
         scanner_next_char();

         while ((ch = scanner_next_char()) != '\n' && ch != EOF)
         {
         }

         return scanner_next_word(buff);
      }

      /* Multi-line comment */
      if (next == '*')
      {
         scanner_next_char();

         while (1)
         {
            ch = scanner_next_char();

            if (ch == EOF)
            {
               return 0;
            }

            if (ch == '*' && scanner_peek() == '/')
            {
               scanner_next_char();
               break;
            }
         }

         return scanner_next_word(buff);
      }
   }

   /* Preprocessor */

   if (ch == '#')
   {
      i = 0;
      buff[i++] = ch;

      while ((ch = scanner_next_char()) != '\n' && ch != EOF)
      {
         if (i < MAX_LEXEME_LEN - 1)
         {
            buff[i++] = ch;
         }
      }

      buff[i] = '\0';

      return 1;
   }

   /* Identifier / Keyword */
   if (isalpha(ch) || ch == '_')
   {
      buff[i++] = ch;

      while (1)
      {
         ch = scanner_peek();

         if (isalnum(ch) || ch == '_')
         {
            buff[i++] = scanner_next_char();
         }
         else
         {
            break;
         }

         if (i >= MAX_LEXEME_LEN - 1)
         {
            break;
         }
      }

      buff[i] = '\0';

      return 1;
   }

   /* Number */
   if (isdigit(ch))
   {
      buff[i++] = ch;

      while (1)
      {
         ch = scanner_peek();

         if (isdigit(ch) || ch == '.')
         {
            buff[i++] = scanner_next_char();
         }
         else
         {
            break;
         }

         if (i >= MAX_LEXEME_LEN - 1)
         {
            break;
         }
      }

      buff[i] = '\0';

      return 1;
   }

   /* String or character literal */
   if (ch == '"' || ch == '\'')
   {
      int quote = ch;

      buff[i++] = ch;

      while (i < MAX_LEXEME_LEN - 1)
      {
         ch = scanner_next_char();

         if (ch == EOF)
         {
            break;
         }

         buff[i++] = ch;

         if (ch == quote)
         {
            break;
         }
      }

      buff[i] = '\0';

      return 1;
   }

   /* Operator / punctuation */

   buff[i++] = ch;

   /* Check for two-character operators */
   if (ch == '=' || ch == '!' ||
       ch == '<' || ch == '>' ||
       ch == '+' || ch == '-' ||
       ch == '*' || ch == '/' ||
       ch == '%' || ch == '&' ||
       ch == '|')
   {
      int next = scanner_peek();

      if ((ch == '=' && next == '=') ||
          (ch == '!' && next == '=') ||
          (ch == '<' && next == '=') ||
          (ch == '>' && next == '=') ||
          (ch == '+' && next == '+') ||
          (ch == '-' && next == '-') ||
          (ch == '+' && next == '=') ||
          (ch == '-' && next == '=') ||
          (ch == '*' && next == '=') ||
          (ch == '/' && next == '=') ||
          (ch == '%' && next == '=') ||
          (ch == '&' && next == '&') ||
          (ch == '|' && next == '|'))
      {
         buff[i++] = scanner_next_char();
      }
   }

   buff[i] = '\0';

   return 1;
}

void scanner_close(void)
{
   if (fp != NULL)
   {
      fclose(fp);
      fp = NULL;
   }
}

int scanner_get_line(void)
{
   return current_line;
}