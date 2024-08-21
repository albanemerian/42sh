/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** sort set
*/

#include <stdlib.h>
#include "minishell.h"
#include <ncurses.h>

void sort_set(shell_t *shell, char **env)
{
    set_list_t *begin = shell->variables;
    set_list_t **current = &shell->variables;
    char *temp_var = NULL;
    char *temp_content = NULL;

    while ((*current)->next != NULL) {
        if (strcmp((*current)->var, (*current)->next->var) > 0) {
            temp_var = my_strdup((*current)->var);
            temp_content = my_strdup((*current)->content);
            (*current)->var = my_strdup((*current)->next->var);
            (*current)->content = my_strdup((*current)->next->content);
            (*current)->next->var = my_strdup(temp_var);
            (*current)->next->content = my_strdup(temp_content);
            *current = begin;
        } else {
            *current = (*current)->next;
        }
    }
    shell->variables = begin;
}
