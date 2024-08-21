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

static int is_on(char *state)
{
    if (strcmp(state, "on") == 0)
        return 1;
    return 0;
}

int is_ignoreof(shell_t *shell)
{
    set_list_t *current = shell->variables;

    while (current != NULL) {
        if (strcmp(current->var, "ignoreof") == 0)
            break;
        current = current->next;
    }
    if (current != NULL) {
        if (current->content != NULL)
            return is_on(current->content);
    }
    return 0;
}
