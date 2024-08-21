/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** ignoreof
*/

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include <ncurses.h>

int return_value(shell_t *shell)
{
    char *value = calloc(1, sizeof(char) * (
        strlen(my_itoa(shell->base->status)) + 3));

    value = strcpy(value, "?=");
    value = strcat(value, my_itoa(shell->base->status));
    value[strlen(my_itoa(shell->base->status)) + 4] = '\0';
    shell->variables = set_variable(value, &shell->variables);
    return 0;
}
