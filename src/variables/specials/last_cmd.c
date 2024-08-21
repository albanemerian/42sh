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

char *last_elem(shell_t *shell)
{
    struct hist *current = shell->history->hist;

    while (current->next != NULL)
        current = current->next;
    return current->str;
}

set_list_t *last_cmd(shell_t *shell)
{
    char *cmd = NULL;

    if (shell->history->hist != NULL) {
        cmd = calloc(1, sizeof(char) * (strlen(last_elem(shell)) + 8));
        sprintf(cmd, "_=%s", last_elem(shell));
        return set_variable(cmd, &shell->variables);
    } else {
        cmd = calloc(1, sizeof(char) * 7);
        sprintf(cmd, "_");
        return set_variable(cmd, &shell->variables);
    }
    return NULL;
}
