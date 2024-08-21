/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** ncurses handler
*/

#include <stdlib.h>
#include "minishell.h"
#include <ncurses.h>

void display_set(shell_t *shell)
{
    set_list_t *list = shell->variables;

    while (list != NULL) {
        print("%s\t", list->var);
        if (list->content != NULL)
            print("%s\n", list->content);
        else
            print("\n");
        list = list->next;
    }
}
