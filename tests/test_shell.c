/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_shell
*/

#include <criterion/criterion.h>
#include "minishell.h"

Test(error_handling, valid_test)
{
    shell_t shell;
    shell.history = malloc(sizeof(*shell.history));
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;
    shell.base->env = NULL;
    shell.base->env = malloc(sizeof(char *) * 2);
    shell.base->env[0] = strdup("PATH=/usr/bin");
    shell.base->env[1] = NULL;
    shell.base->env_len = 1;
    shell.base->arr = malloc(sizeof(char *) * 2);
    shell.base->arr[0] = strdup("42sh");
    shell.base->arr[1] = NULL;
    shell.base->status = 0;
    shell.base->home = strdup("/home/test");
    shell.base->oldpwd = NULL;
    shell.base->result = 0;
    shell.disp = printf;

    error_handling(&shell, shell.base->env, shell.base->arr, 1);
}

