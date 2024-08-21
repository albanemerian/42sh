/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** init_ncurse
*/

#include <fcntl.h>
#include <ncurses.h>
#include "minishell.h"

int init_screen(shell_t *shell)
{
    if (shell->tty == false) {
        shell->ncurses->win = initscr();
        shell->ncurses->hist_num = 0;
        shell->ncurses->prompt = 0;
        shell->ncurses->size_input = 0;
        scrollok(shell->ncurses->win, true);
        keypad(shell->ncurses->win, TRUE);
        noecho();
        refresh();
        return 1;
    }
    return 0;
}

void fill_history_and_ncurses(shell_t *shell)
{
    if (isatty(STDIN_FILENO) == 1) {
        shell->tty = false;
        shell->disp = &printw;
        shell->ncurses->hist_num = 0;
    } else {
        shell->tty = true;
        shell->disp = &printf;
    }
    init_screen(shell);
}

int builtin_clear(shell_t *shell, char *string)
{
    if (strncmp(string, "clear", 5) == 0) {
        clear();
        shell->ncurses->line = 0;
        return 1;
    }
    shell->ncurses->out = dup(STDOUT_FILENO);
    shell->ncurses->err = dup(STDERR_FILENO);
    return 0;
}

void ncurses_user_input(shell_t *shell, char **env)
{
    char *string = NULL;

    shell->ncurses->fd = open(".render", O_RDONLY | O_WRONLY | O_TRUNC);
    get_prompt_entered(shell);
    shell->ncurses->col = 0;
    shell->ncurses->line += 1;
    move(shell->ncurses->line, shell->ncurses->col);
    shell->base->l = shell->ncurses->input;
    if (my_str_isprintable(shell->base->l) == 0)
        return;
    string = my_strdup(shell->base->l);
    if (builtin_clear(shell, string) == 1)
        return;
    dup2(shell->ncurses->fd, STDOUT_FILENO);
    dup2(shell->ncurses->fd, STDERR_FILENO);
    init_cmd_line(shell, string, env);
    dup2(shell->ncurses->out, STDOUT_FILENO);
    dup2(shell->ncurses->err, STDERR_FILENO);
    close(shell->ncurses->fd);
    display_execution(shell);
}
