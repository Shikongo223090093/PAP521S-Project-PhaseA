/* utilities.c - validated input and string helper functions used by all modules */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilities.h"

/* Discards whatever is left of an over-long input line. */
static void flushRestOfLine(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* discard */
    }
}

/* Reads one line safely with fgets() and removes the trailing newline. */
static void readLine(const char prompt[], char buffer[], int size)
{
    printf("%s", prompt);

    if (fgets(buffer, size, stdin) == NULL)
    {
        printf("\nInput ended. Exiting the system.\n");
        exit(0);
    }

    if (strchr(buffer, '\n') == NULL)
    {
        flushRestOfLine();          /* line was longer than the buffer */
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

int readInt(const char prompt[], int min, int max)
{
    char line[64];
    char extra;
    int value;

    while (1)
    {
        readLine(prompt, line, sizeof(line));

        /* Exactly one item must be read: "12abc" reads two, so it is rejected */
        if (sscanf(line, "%d %c", &value, &extra) == 1 && value >= min && value <= max)
        {
            return value;
        }
        printf("  Invalid input. Enter a whole number between %d and %d.\n", min, max);
    }
}

double readDouble(const char prompt[], double min)
{
    char line[64];
    char extra;
    double value;

    while (1)
    {
        readLine(prompt, line, sizeof(line));

        /* NaN and infinity fail these comparisons, so they are rejected too */
        if (sscanf(line, "%lf %c", &value, &extra) == 1 && value >= min && value <= 1000000000000.0)
        {
            return value;
        }
        printf("  Invalid input. Enter a number that is at least %.2f.\n", min);
    }
}

void trimSpaces(char text[])
{
    int start = 0;
    int end = (int)strlen(text);
    int i;

    while (text[start] != '\0' && isspace((unsigned char)text[start]))
    {
        start++;
    }
    while (end > start && isspace((unsigned char)text[end - 1]))
    {
        end--;
    }
    for (i = 0; i < end - start; i++)
    {
        text[i] = text[start + i];
    }
    text[end - start] = '\0';
}

void readString(const char prompt[], char buffer[], int size)
{
    while (1)
    {
        readLine(prompt, buffer, size);
        trimSpaces(buffer);

        if (strlen(buffer) > 0)
        {
            return;
        }
        printf("  This field cannot be empty.\n");
    }
}

/* Copies src into dest in lowercase (dest must hold size characters). */
static void toLowerCopy(const char src[], char dest[], int size)
{
    int i;
    for (i = 0; i < size - 1 && src[i] != '\0'; i++)
    {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

int equalsIgnoreCase(const char first[], const char second[])
{
    char a[TEXT_LENGTH + 1];
    char b[TEXT_LENGTH + 1];

    toLowerCopy(first, a, sizeof(a));
    toLowerCopy(second, b, sizeof(b));
    return strcmp(a, b) == 0;
}

int containsIgnoreCase(const char text[], const char part[])
{
    char a[TEXT_LENGTH + 1];
    char b[TEXT_LENGTH + 1];

    toLowerCopy(text, a, sizeof(a));
    toLowerCopy(part, b, sizeof(b));
    return strstr(a, b) != NULL;
}

int isValidEmail(const char email[])
{
    int length = (int)strlen(email);
    int atPosition = -1;
    int lastDot = -1;
    int i;

    for (i = 0; i < length; i++)
    {
        if (isspace((unsigned char)email[i]))
        {
            return 0;
        }
        if (email[i] == '@')
        {
            if (atPosition != -1)
            {
                return 0;               /* more than one @ */
            }
            atPosition = i;
        }
        if (email[i] == '.')
        {
            lastDot = i;
        }
    }

    /* needs text before @, a dot after @, and text after the dot */
    return atPosition > 0 && lastDot > atPosition + 1 && lastDot < length - 1;
}

int isValidPhone(const char phone[])
{
    int length = (int)strlen(phone);
    int i;

    if (length < 7 || length > 15)
    {
        return 0;
    }
    for (i = 0; i < length; i++)
    {
        if (!isdigit((unsigned char)phone[i]) && !(i == 0 && phone[i] == '+'))
        {
            return 0;
        }
    }
    return 1;
}

void printLine(char symbol, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        putchar(symbol);
    }
    putchar('\n');
}

void printHeader(const char title[])
{
    printf("\n");
    printLine('=', 60);
    printf(" %s\n", title);
    printLine('=', 60);
}
