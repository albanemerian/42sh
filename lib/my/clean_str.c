/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** clean_str
*/

#include "my.h"

static int is_wspace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

static char *clean(char *start, char *end)
{
    while (start < end && is_wspace(*(start + 1)))
        start++;
    return start;
}

char *clean_str(char *str)
{
    char *start = str;
    char *end = str + strlen(str) - 1;
    char *write = str;

    while (*start != '\0' && is_wspace(*start))
        start++;
    while (end > start && is_wspace(*end))
        end--;
    while (start <= end) {
        *write = *start;
        if (is_wspace(*start))
            start = clean(start, end);
        start++;
        write++;
    }
    *write = '\0';
    return str;
}
