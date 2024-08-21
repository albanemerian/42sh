/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_base
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// option_handler.c

Test(option_handler, fill_str)
{
    char *line = strdup("ls -l");
    char **array = fill_str(line);

    cr_assert_str_eq(array[0], "ls");
    cr_assert_str_eq(array[1], "-l");
    cr_assert_null(array[2]);
}

Test(option_handler, option_1_1)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    char *line = strdup("ls -l 'test' -a");
    s->base->result = 42;
    option(s, line);

    cr_assert_eq(s->base->result, 0);
}

Test(option_handler, option_1_2)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    char *line = strdup("  \t ");
    s->base->l = line;
    s->base->result = 42;
    option(s, line);

    cr_assert_eq(s->base->result, 0);
}

Test(option_handler, option_1_3)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    char *line = strdup("ls -l 'test' -a");
    s->base->result = 42;
    option(s, line);

    cr_assert_eq(s->base->result, 0);
}

// glob.c
Test(glob, handle_glob)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->base->arr = calloc(3, sizeof(char *));
    s->base->arr[0] = strdup("ls");
    s->base->arr[1] = strdup("*.c");
    s->base->arr[2] = NULL;
    char **exp_args = handle_glob(s);

    cr_assert_str_eq(exp_args[0], "ls");
}

Test(glob, no_matching)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->base->arr = calloc(3, sizeof(char *));
    s->base->arr[0] = strdup("ls");
    s->base->arr[1] = strdup("*.c");
    s->base->arr[2] = NULL;
    char **exp_args = no_matching(s);

    cr_assert_null(exp_args);
}

// echo_command.c
Test(echo_command, echo_command, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->base->arr = calloc(3, sizeof(char *));
    s->base->arr[0] = strdup("echo");
    s->base->arr[1] = strdup("Hello");
    s->base->result = echo_command(s, s->base->arr);

    cr_assert_eq(s->base->result, 0);
    cr_assert_stdout_eq_str("Hello\n");
}

Test(echo_command, echo_command_2, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->base->arr = calloc(4, sizeof(char *));
    s->base->arr[0] = strdup("echo");
    s->base->arr[1] = strdup("Hello");
    s->base->arr[2] = strdup("World");
    s->base->result = echo_command(s, s->base->arr);

    cr_assert_eq(s->base->result, 0);
    cr_assert_stdout_eq_str("Hello World\n");
}
