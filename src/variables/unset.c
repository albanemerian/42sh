/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** ncurses handler
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"
#include <ncurses.h>

static int no_prev(set_list_t **data, char *var)
{
    set_list_t **list = data;
    set_list_t *temp;

    if (strcmp((*list)->var, var) == 0) {
        temp = *list;
        *list = (*list)->next;
        free(temp);
        return (0);
    }
    return (1);
}

static int del_node(set_list_t **bot, char *var)
{
    set_list_t **list = bot;
    set_list_t *current = *list;
    set_list_t *previous = NULL;

    while (strcmp(current->var, var) != 0) {
        previous = current;
        current = current->next;
        if (current->next == NULL)
            break;
    }
    if (current != NULL) {
        previous->next = current->next;
        free(current);
    }
    return (0);
}

int unset_func(shell_t *shell, char **env)
{
    if (my_tablen(shell->base->arr) < 2) {
        shell->disp("unset: Too few arguments.\n");
        shell->base->status = 1;
        return 0;
    }
    for (int i = 1; i < my_tablen(shell->base->arr); i++) {
        if (no_prev(&shell->variables, shell->base->arr[i]) == 1)
            del_node(&shell->variables, shell->base->arr[i]);
    }
    return 0;
}
