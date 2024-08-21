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

static char *cwd_parser(shell_t *shell)
{
    set_list_t *t = shell->variables;

    while (t != NULL) {
        if (strcmp(t->var, "cwd") == 0)
            break;
        t = t->next;
    }
    if (t == NULL)
        return " ";
    for (int i = strlen(t->content) - 1; i >= 0; i--) {
        if (t->content[i] == '/')
            return (&t->content[i + 1]);
    }
    return (t->content);
}

set_list_t *prompt(shell_t *shell)
{
    char *prompt = "prompt=[42sh@epitech %s]$ ";

    return set_variable(prompt, &shell->variables);
}

void display_prompt(shell_t *shell)
{
    set_list_t *t = shell->variables;

    while (t != NULL) {
        if (strcmp(t->var, "prompt") == 0)
            break;
        t = t->next;
    }
    if (t == NULL)
        return;
    shell->disp(t->content, cwd_parser(shell));
}
