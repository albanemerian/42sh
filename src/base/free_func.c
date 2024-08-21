/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** free_func
*/

#include "minishell.h"

void free_func(shell_t *shell)
{
    if (shell->base->l)
        free(shell->base->l);
    refresh();
}
