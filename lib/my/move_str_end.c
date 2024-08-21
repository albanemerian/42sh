/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** move_str_end
*/

#include "my.h"
#include <string.h>
#include <ctype.h>

void move_str_end(char *str)
{
    int i = 0;
    int len = 0;

    if (str == NULL)
        return;
    len = strlen(str);
    if (len == 0)
        return;
    i = len - 1;
    while (i >= 0 && isspace(str[i])) {
        str[i] = '\0';
        i--;
    }
}
