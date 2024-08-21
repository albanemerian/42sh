/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** alias_command_line
*/

#include "minishell.h"
#include <errno.h>

char **simple_cases(char **alias_commands, int alias_i, shell_t *shell)
{
    if (my_tablen(alias_commands) == 1) {
        shell->base->arr[alias_i] = alias_commands[0];
        return shell->base->arr;
    }
    if (my_tablen(shell->base->arr) == 1) {
        shell->base->arr = my_array_dup(alias_commands);
        return shell->base->arr;
    }
    return NULL;
}

char **complex_case(int alias_i, char **alias_commands, shell_t *shell)
{
    int index = 0;
    char **new_arr = NULL;

    if (!alias_commands)
        return NULL;
    new_arr = calloc((my_tablen(shell->base->arr) + my_tablen(alias_commands)
        + 1), sizeof(char *));
    for (; index < alias_i; index++)
        new_arr[index] = my_strdup(shell->base->arr[index]);
    for (int i = 0; alias_commands[i] != NULL; i++) {
        new_arr[index] = my_strdup(alias_commands[i]);
        index++;
    }
    for (int i = alias_i + 1; shell->base->arr[i] != NULL; i++) {
        new_arr[index] = my_strdup(shell->base->arr[i]);
        index++;
    }
    new_arr[index] = NULL;
    return new_arr;
}

char **alias_command_line(shell_t *shell, int alias_i)
{
    alias_t *alias = find_alias(shell, alias_i);
    char **alias_commands = alias->command;
    char **arr_cpy = my_array_dup(shell->base->arr);

    if (alias && strstr(alias->name, " ") != NULL) {
        shell->base->arr[0] = alias->name;
        return shell->base->arr;
    }
    shell->base->arr = simple_cases(alias_commands, alias_i, shell);
    if (shell->base->arr)
        return shell->base->arr;
    shell->base->arr = arr_cpy;
    return complex_case(alias_i, alias_commands, shell);
}
