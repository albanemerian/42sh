/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** echo_command
*/

#include "minishell.h"

int echo_command(shell_t *shell, char **env)
{
    for (int i = 1; shell->base->arr[i] != NULL; i++) {
        print("%s", shell->base->arr[i]);
        if (shell->base->arr[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
    }
    write(STDOUT_FILENO, "\n", 1);
    return 0;
}
