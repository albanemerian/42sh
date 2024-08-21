/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_itoa
*/

#include "my.h"


int my_unsignedlen(unsigned int nb)
{
    int i = 0;

    while (nb / 10 > 0) {
        i++;
        nb /= 10;
    }
    i++;
    return (i);
}

char *my_itoa(unsigned int nb)
{
    char *numbers = "0123456789";
    char *str = malloc(sizeof(char) * (my_unsignedlen(nb) + 1));
    int i = my_unsignedlen(nb);

    str[i] = '\0';
    i--;
    while (i >= 0) {
        str[i] = numbers[nb % 10];
        nb /= 10;
        i--;
    }
    return (str);
}
