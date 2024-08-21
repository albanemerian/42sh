/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** find_parnethese
*/

#include "minishell.h"
#include <ctype.h>

int part_three(shell_t *shell, char *string, int i)
{
    for (int j = i - 1; j > 0 && string[j] != '('; j--) {
        if (string[j] != ' ') {
            return 1;
        }
    }
    return 0;
}

int part_two(shell_t *shell, char *string, int i)
{
    if (string[i] == ')') {
        if (part_three(shell, string, i) == 1)
            return 1;
        shell->disp("Invalid null command.\n");
        shell->base->status = 1;
        return 0;
    }
    return 1;
}

int find_erno(shell_t *shell, char *string, int num_left, int num_rigth)
{
    int i = 0;

    if (num_left > num_rigth) {
        shell->disp("Too many ('s.\n");
        shell->base->status = 1;
        return 0;
    }
    if (num_left < num_rigth) {
        shell->disp("Too many )'s.\n");
        shell->base->status = 1;
        return 0;
    }
    for (; string[i] != '\0'; i++) {
        if (part_two(shell, string, i) == 0)
            return 0;
    }
    return 1;
}

static void count_cmd(shell_t *shell, char *string, int num_left)
{
    shell->par->num_par = 1;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ';' || (string[i] == '&' && string[i + 1] == '&') ||
            (string[i] == '|' && string[i + 1] == '|'))
            shell->par->num_par += 1;
    }
    pos_parenthese(shell, string, num_left);
}

int look_for_parenthesis(shell_t *shell, char *string)
{
    int num_rigth = 0;
    int num_left = 0;

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '(')
            num_left++;
        if (string[i] == ')')
            num_rigth++;
    }
    if (num_left == 0 && num_rigth == 0)
        return 1;
    if (find_erno(shell, string, num_left, num_rigth) == 1) {
        count_cmd(shell, string, num_left);
        return 1;
    }
    return 0;
}
