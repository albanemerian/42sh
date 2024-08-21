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

static int no_prev(struct list **data, char *var, char *content)
{
    struct list **list = data;

    if (strncmp((*list)->str, var, strlen(var)) == 0) {
        free((*list)->str);
        (*list)->str = calloc(1, sizeof(char) *
            (strlen(var) + strlen(content) + 1));
        sprintf((*list)->str, "%s%s", var, content);
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
    }
    return (0);
}

static char *get_term(shell_t *shell)
{
    char *term = NULL;
    struct list *t = shell->current;

    while (t != NULL) {
        if (strncmp(t->str, "TERM=", 5) == 0) {
            term = my_strdup(&t->str[5]);
            return term;
        }
        t = t->next;
    }
    return NULL;
}

set_list_t *term(shell_t *shell)
{
    char *term = get_term(shell);
    char *var = NULL;

    if (term != NULL) {
        var = calloc(1, sizeof(char) * (strlen(term) + 6));
        var = strcpy(var, "term=");
        var = strcat(var, term);
        return set_variable(var, &shell->variables);
    }
    return NULL;
}

void change_term_value(shell_t *shell, char *name)
{
    if (strncmp(name, "term", 4) == 0) {
        if (strcmp(&name[5], "xterm") != 0 &&
            strcmp(&name[5], "xterm-256color") != 0)
                shell->disp("42sh: using dumb terminal settings.\n");
        if (no_prev(&shell->current, "TERM=", &name[5]) == 1)
            del_node(shell, "TERM=", &name[5]);
    }
}
