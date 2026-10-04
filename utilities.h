#ifndef UTILITIES_H
#define UTILITIES_H

/* Maximum size of any name/text field stored by the system */
#define TEXT_LENGTH 100

/* ---------- Validated input ---------- */
/* Reads a whole number between min and max (inclusive). Repeats until valid. */
int readInt(const char prompt[], int min, int max);

/* Reads a decimal number that is at least min. Repeats until valid. */
double readDouble(const char prompt[], double min);

/* Reads a non-empty line of text (spaces allowed) into buffer. */
void readString(const char prompt[], char buffer[], int size);

/* ---------- String helpers ---------- */
void trimSpaces(char text[]);
int equalsIgnoreCase(const char first[], const char second[]);
int containsIgnoreCase(const char text[], const char part[]);
int isValidEmail(const char email[]);
int isValidPhone(const char phone[]);

/* ---------- Display helpers ---------- */
void printHeader(const char title[]);
void printLine(char symbol, int length);

#endif
