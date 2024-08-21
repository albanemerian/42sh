/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_backticks
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// handle_backticks.c
Test(handle_backticks, handle_backticks, .init = redirect_all_std)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->bticks = malloc(sizeof(bticks_t));
    shell->bticks->keep_bticks = NULL;
    shell->bticks->nb_bticks = 0;
    shell->bticks->quote = '`';
    char **array = calloc(1, sizeof(char *));
    array[0] = strdup("ls");
    char *result = strdup("ls -l");
    handle_backticks(shell, array, result);
    cr_assert_str_eq(shell->bticks->keep_bticks[0], "ls -l");
    cr_assert_eq(shell->bticks->nb_bticks, 1);
}

Test(replace_backticks, add_backtick_command, .init = redirect_all_std)
{
    char **cmd = calloc(1, sizeof(char *));
    char *backtick_cmd = strdup("ls");
    int num_cmds = 0;
    add_backtick_command(&cmd, backtick_cmd, &num_cmds);
    cr_assert_str_eq(cmd[0], "ls");
    cr_assert_eq(num_cmds, 1);
}

Test(replace_backticks, update_array, .init = redirect_all_std)
{
    char **array = calloc(1, sizeof(char *));
    array[0] = strdup("ls");
    char *btick_res = strdup("ls -l");
    char **cmd = calloc(1, sizeof(char *));
    cmd[0] = strdup("ls");
    int num_cmds = 1;
    update_array(array, btick_res, cmd, num_cmds);
    cr_assert_str_eq(array[0], "ls -l");
}
