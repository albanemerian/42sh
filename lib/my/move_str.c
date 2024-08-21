/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** move_str
*/

#include "my.h"

void move_str(char *str)
{
    int i = 0;
    int j = 0;
    int len = my_strlen(str);

    for (; i < len; i++) {
        if (str[i] != ' ')
            break;
    }
    if (i > 0) {
        for (; j < len - i; j++)
            str[j] = str[j + i];
        str[j] = '\0';
        len = my_strlen(str);
    }
    for (i = len - 1; i >= 0; i--) {
        if (str[i] != ' ')
            break;
    }
    if (i < len - 1)
        str[i + 1] = '\0';
}
