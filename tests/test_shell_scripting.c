/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_shell_scripting
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// execute.c
Test(execute, read_42shrc)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    char **env = calloc(1, sizeof(char *));
    s->base = calloc(1, sizeof(base_t));

    shell_t *rv = read_42shrc(s, env);
    cr_assert_eq(rv, s);
}

Test(execute, check_line_false)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    char **env = calloc(1, sizeof(char *));
    s->base = calloc(1, sizeof(base_t));
    s->base->l = strdup("# This is a comment\n");

    bool rv = check_line(s, env);
    cr_assert_eq(rv, false);
}

Test(execute, check_line_true)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    char **env = calloc(1, sizeof(char *));
    s->base = calloc(1, sizeof(base_t));
    s->base->l = strdup("echo Hello, World!\n");

    bool rv = check_line(s, env);
    cr_assert_eq(rv, true);
}
