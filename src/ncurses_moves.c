/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** ncurses handler
*/

#include "../include/minishell.h"
#include <fcntl.h>
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

static void move_by_letters(shell_t *shell, set_list_t *set)
{
    char temp[1024];

    sprintf(temp, set->content, cwd_parser(shell));
    for (int i = 0; temp[i] != '\0'; i++) {
        move(shell->ncurses->line, shell->ncurses->col);
        printw("%c", temp[i]);
        shell->ncurses->prompt += 1;
        shell->ncurses->col += 1;
    }
    shell->ncurses->prompt = shell->ncurses->col;
}

void prompt_moves(shell_t *shell)
{
    for (set_list_t *set = shell->variables; set != NULL; set = set->next) {
        if (strcmp(set->var, "prompt") == 0)
            move_by_letters(shell, set);
    }
}

int key_left_pressed(shell_t *shell, int *i)
{
    if (shell->ncurses->ch == KEY_LEFT) {
        if (shell->ncurses->prompt < shell->ncurses->col) {
            shell->ncurses->col -= 1;
            *i -= 1;
            move(shell->ncurses->line, shell->ncurses->col);
            refresh();
        }
        return 1;
    }
    return 0;
}

int key_right_pressed(shell_t *shell, int *i)
{
    if (shell->ncurses->ch == KEY_RIGHT) {
        if (shell->ncurses->col < shell->ncurses->size_input) {
            shell->ncurses->col += 1;
            *i += 1;
            move(shell->ncurses->line, shell->ncurses->col);
            refresh();
        }
        return 1;
    }
    return 0;
}
