/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_arraydup
*/

#include "my.h"

char **my_array_dup(char **array)
{
    int i = 0;
    char **new_array = NULL;

    if (array == NULL)
        return NULL;
    while (array[i] != NULL)
        i++;
    new_array = malloc(sizeof(char *) * (i + 1));
    if (new_array == NULL)
        return NULL;
    i = 0;
    while (array[i] != NULL) {
        new_array[i] = strdup(array[i]);
        i++;
    }
    new_array[i] = NULL;
    return new_array;
}
