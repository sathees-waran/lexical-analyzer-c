/*
 * scanner.h
 * Public interface for reading a source file and extracting lexemes.
 */

#ifndef SCANNER_H
#define SCANNER_H

int scanner_init(const char *filename);

int scanner_next_char(void);

int scanner_peek(void);

int scanner_next_word(char *buff);

void scanner_close(void);

int scanner_get_line(void);

#endif