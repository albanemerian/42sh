/*
** EPITECH PROJECT, 2023
** my_tablen
** File description:
** my_unsigned_nbr
*/

#include <unistd.h>
#include "my.h"

int my_tablen(char **array)
{
    int size = 0;

    if (array == NULL)
        return 0;
    for (int i = 0; array[i] != NULL; i++)
        size++;
    return size;
}

int my_tripletablen(char ***array)
{
    int size = 0;

    if (array == NULL)
        return 0;
    for (int i = 0; array[i] != NULL; i++)
        size++;
    return size;
}
