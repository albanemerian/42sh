/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** precmd
*/

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include <ncurses.h>

void my_precmd(shell_t *shell)
{
    set_list_t *current = shell->variables;

    while (current != NULL) {
        if (strcmp(current->var, "precmd") == 0)
            break;
        current = current->next;
    }
    if (current != NULL) {
        if (current->content != NULL)
            option(shell, current->content);
    }
}
