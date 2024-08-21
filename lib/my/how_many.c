/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** how_many
*/

#include "my.h"

int how_many(char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            count++;
    return count;
}

int posinstr(char *str, char c)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            return i;
    return my_strlen(str);
}
