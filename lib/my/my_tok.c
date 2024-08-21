/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_tok
*/

#include "my.h"


char **my_tok(char **array, char *line, char *delim)
{
    char *fun = my_strdup(line);
    char *token = strtok(fun, delim);
    int i = 0;
    int j = 0;
    char *sleep = NULL;

    while (token != NULL) {
        i++;
        token = strtok(NULL, delim);
    }
    array = calloc(i + 1, sizeof(char *));
    sleep = strtok(line, delim);
    while (sleep != NULL) {
        array[j] = my_strdup(sleep);
        j++;
        sleep = strtok(NULL, delim);
    }
    array[i] = NULL;
    return array;
}
