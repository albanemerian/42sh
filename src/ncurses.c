/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** ncurses handler
*/

#include "../include/minishell.h"
#include <fcntl.h>
#include <ncurses.h>

static int list_len(struct hist *list)
{
    struct hist *current = list;
    int i = 0;

    if (current == NULL)
        return 0;
    while (current != NULL) {
        i++;
        current = current->next;
    }
    return i;
}

static void display_input(shell_t *shell, char *str)
{
    shell->ncurses->size_input = shell->ncurses->prompt;
    shell->ncurses->col = shell->ncurses->size_input;
    shell->ncurses->input = my_strdup(str);
    for (int i = 0; shell->ncurses->input[i] != '\0'; i++) {
        move(shell->ncurses->line, shell->ncurses->col);
        printw("%c", shell->ncurses->input[i]);
        shell->ncurses->col += 1;
    }
}

static void apply_history(shell_t *shell)
{
    struct hist *current = shell->history->hist;
    struct hist *temp = NULL;

    for (int i = 0; current != NULL; i++) {
        if (i == shell->ncurses->hist_num)
            break;
        temp = current;
        current = current->next;
    }
    if (temp == NULL)
        return;
    for (int i = 0; i < my_strlen(shell->ncurses->input); i++)
        shell->disp("\b \b");
    display_input(shell, temp->str);
}

static void already_zero(shell_t *shell)
{
    if (shell->ncurses->hist_num == 0) {
        for (int i = 0; i < my_strlen(shell->ncurses->input); i++)
            shell->disp("\b \b");
        shell->ncurses->col = shell->ncurses->prompt;
        shell->ncurses->input = my_strdup("\0");
    }
}

static int handle_arrow(shell_t *shell, int *i)
{
    if (shell->ncurses->ch == KEY_UP) {
        if (shell->ncurses->hist_num != list_len(shell->history->hist)) {
            shell->ncurses->hist_num += 1;
            apply_history(shell);
            *i = my_strlen(shell->ncurses->input);
        }
        return 1;
    }
    if (shell->ncurses->ch == KEY_DOWN) {
        if (shell->ncurses->hist_num > 0) {
            shell->ncurses->hist_num -= 1;
            already_zero(shell);
            apply_history(shell);
            *i = my_strlen(shell->ncurses->input);
        }
        return 1;
    }
    return 0;
}

static int handle_removing(shell_t *shell, int i)
{
    if (i > 0) {
        shell->ncurses->input[i - 1] = '\0';
        printw("\b \b");
        refresh();
        return 1;
    }
    return 0;
}

static void add_character(shell_t *shell, int *i)
{
    char *next = NULL;

    if (my_strlen(shell->ncurses->input) == *i) {
        shell->ncurses->input[*i] = shell->ncurses->ch;
        printw("%c", shell->ncurses->input[*i]);
        shell->ncurses->col += 1;
        shell->ncurses->size_input += 1;
        refresh();
        *i += 1;
    } else {
        next = strdup(&shell->ncurses->input[*i]);
        shell->ncurses->input[*i] = shell->ncurses->ch;
        for (int j = 0; next[j] != '\0'; j++)
            shell->ncurses->input[*i + 1 + j] = next[j];
        printw("%s", &shell->ncurses->input[*i]);
        shell->ncurses->col += 1;
        shell->ncurses->size_input += 1;
        refresh();
        *i += 1;
    }
}

static void not_arrow(shell_t *shell, int *i)
{
    if (key_left_pressed(shell, i) == 1)
        return;
    if (key_right_pressed(shell, i) == 1)
        return;
    if (shell->ncurses->ch == KEY_BACKSPACE || shell->ncurses->ch == 127) {
        if (*i > 0) {
            *i -= handle_removing(shell, *i);
            shell->ncurses->col -= 1;
            shell->ncurses->size_input -= 1;
        }
    } else {
        add_character(shell, i);
    }
}

void get_prompt_entered(shell_t *shell)
{
    int i = 0;

    shell->ncurses->input = calloc(1, sizeof(char) * 1024);
    shell->ncurses->ch = getch();
    while (shell->ncurses->ch != '\n' && i < 1024 - 1) {
        move(shell->ncurses->line, shell->ncurses->col);
        if (handle_arrow(shell, &i) == 0)
            not_arrow(shell, &i);
        shell->ncurses->size_input = shell->ncurses->prompt + i;
        shell->ncurses->ch = getch();
    }
    shell->ncurses->hist_num = 0;
    if (shell->ncurses->line > 55) {
        printw("\n");
        shell->ncurses->line += 1;
    }
}

void display_execution(shell_t *shell)
{
    char *buff = NULL;
    int fd = open(".render", O_RDONLY);

    buff = calloc(1, sizeof(char) * 2147483647);
    read(fd, buff, 2147483647);
    for (int i = 0; buff[i] != '\0'; i++) {
        move(shell->ncurses->line, shell->ncurses->col);
        shell->disp("%c", buff[i]);
        shell->ncurses->col += 1;
        if (buff[i] == '\n') {
            shell->ncurses->line += 1;
            shell->ncurses->col = 0;
        }
    }
    shell->ncurses->col = 0;
    free(buff);
    close(fd);
}
