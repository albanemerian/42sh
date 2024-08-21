/*
** EPITECH PROJECT, 2023
** my_strlen
** File description:
** task03 - chgt putchar -> return
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int my_strlen(char const *str)
{
    int c = 0;

    if (str == NULL) {
        return (0);
    }
    for (int i = 0; str[i] != '\0'; i++) {
        c += 1;
    }
    return (c);
}
