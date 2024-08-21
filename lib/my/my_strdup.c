/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** my_strdup
*/
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

char *my_strdup(char const *src)
{
    int src_size = 0;
    char *dest = NULL;
    int i = 0;

    if (src == NULL)
        return NULL;
    src_size = my_strlen(src);
    dest = malloc(sizeof(char) * (src_size + 1));
    if (dest == NULL)
        return NULL;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    if (dest == 0) {
        return (NULL);
    }
    dest[src_size] = '\0';
    return (dest);
}
