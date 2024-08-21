/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** prompt
*/

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include <ncurses.h>

static int no_prev(shell_t *shell, char *var, char *content)
{
    struct list *list = shell->current;

    if (strncmp(list->str, var, strlen(var)) == 0) {
        free(list->str);
        list->str = calloc(1, sizeof(char) *
            (strlen(var) + strlen(content) + 1));
        sprintf(list->str, "%s%s", var, content);
        shell->base->home = my_strdup(content);
        return (0);
    }
    return (1);
}

static int del_node(shell_t *shell, char *var, char *content)
{
    struct list *list = shell->current;
    struct list *current = list;

    while (strncmp(current->str, var, strlen(var)) != 0 && current != NULL)
        current = current->next;
    if (current != NULL) {
        free(current->str);
        current->str = calloc(1, sizeof(char) *
            (strlen(var) + strlen(content) + 1));
        sprintf(current->str, "%s%s", var, content);
        shell->base->home = my_strdup(content);
    }
    return (0);
}

static char *get_homes(shell_t *shell)
{
    char *home = NULL;
    struct list *t = shell->current;

    while (t != NULL) {
        if (strncmp(t->str, "HOME=", 5) == 0) {
            home = my_strdup(&t->str[5]);
            return home;
        }
        t = t->next;
    }
    return NULL;
}

set_list_t *home(shell_t *shell)
{
    char *home = get_homes(shell);
    char *var = NULL;

    if (home != NULL) {
        var = calloc(1, sizeof(char) * (strlen(home) + 6));
        var = strcpy(var, "home=");
        var = strcat(var, home);
        return set_variable(var, &shell->variables);
    }
    return NULL;
}

void change_home_value(shell_t *shell, char *name)
{
    if (strncmp(name, "home", 4) == 0) {
        if (no_prev(shell, "HOME=", &name[5]) == 1)
            del_node(shell, "HOME=", &name[5]);
    }
}
