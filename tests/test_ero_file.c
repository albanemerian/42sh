/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_ero_file
*/
#include <criterion/criterion.h>
#include <string.h>
#include "../include/minishell.h"

Test(diff_built, valid_commands)
{
    cr_assert_eq(diff_built("env"), 1, "Expected 'env' to be a built-in command");
    cr_assert_eq(diff_built("setenv"), 1, "Expected 'setenv' to be a built-in command");
    cr_assert_eq(diff_built("cd"), 1, "Expected 'cd' to be a built-in command");
    cr_assert_eq(diff_built("exit"), 1, "Expected 'exit' to be a built-in command");
    cr_assert_eq(diff_built("invalid"), 0, "Expected 'invalid' to not be a built-in command");
}

Test(null_command, valid_test)
{
    shell_t shell;
    shell.pipe = malloc(sizeof(*shell.pipe));
    shell.pipe->nb_pipe = 1;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;
    shell.disp = printf;

    cr_assert_eq(null_command(&shell, 0), 1, "Expected null command error");
    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");

    shell.base->status = 0;
    cr_assert_eq(null_command(&shell, 2), 0, "Expected no null command error");
    cr_assert_eq(shell.base->status, 0, "Expected shell status to be 0");
}

Test(is_found, valid_test)
{
    shell_t shell;
    shell.pipe = malloc(sizeof(*shell.pipe));
    shell.pipe->arr = malloc(sizeof(char **) * 2);
    shell.pipe->arr[0] = malloc(sizeof(char *) * 2);
    shell.pipe->arr[0][0] = strdup("command > output");
    shell.pipe->arr[0][1] = NULL;
    shell.pipe->arr[1] = NULL;
    shell.pipe->nb_pipe = 1;

    cr_assert_eq(is_found(&shell, 0), true, "Expected '>' to be found");
}

Test(check_for_wrong_redir, valid_test)
{
    shell_t shell;
    shell.pipe = malloc(sizeof(*shell.pipe));
    shell.pipe->arr = malloc(sizeof(char **) * 2);
    shell.pipe->arr[0] = malloc(sizeof(char *) * 2);
    shell.pipe->arr[0][0] = strdup("command > output");
    shell.pipe->arr[0][1] = NULL;
    shell.pipe->arr[1] = NULL;
    shell.pipe->nb_pipe = 1;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;
    shell.disp = printf;
}

Test(check_for_wrong_redir, ambiguous_redirect)
{
    shell_t shell;
    shell.pipe = malloc(sizeof(*shell.pipe));
    shell.pipe->arr = malloc(sizeof(char **) * 3);
    shell.pipe->arr[0] = malloc(sizeof(char *) * 2);
    shell.pipe->arr[0][0] = strdup("command > output");
    shell.pipe->arr[0][1] = NULL;
    shell.pipe->arr[1] = malloc(sizeof(char *) * 2);
    shell.pipe->arr[1][0] = strdup("command > output");
    shell.pipe->arr[1][1] = NULL;
    shell.pipe->arr[2] = NULL;
    shell.pipe->nb_pipe = 2;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;
    shell.disp = printf;
}

