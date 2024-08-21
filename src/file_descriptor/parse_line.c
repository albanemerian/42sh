/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** parse_line
*/

#include "minishell.h"

int nbw(char *str, char *delim)
{
    int cpt = 0;
    char *tmp = strtok(str, delim);

    for (; tmp; cpt++)
        tmp = strtok(NULL, delim);
    return cpt;
}

char **parse(char *cmd, char *delim)
{
    int nbww = nbw(my_strdup(cmd), delim);
    char **arr = malloc(sizeof(char *) * (nbww + 1));
    int i = 0;

    for (char *str = strtok(cmd, delim); str;
        str = strtok(NULL, delim)) {
        arr[i] = my_strdup(str);
        i++;
    }
    arr[i] = NULL;
    return arr;
}
