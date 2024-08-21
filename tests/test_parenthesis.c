/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_parenthesis
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// find_parnethese.c
Test(find_parnethese, part_three_1)
{
    shell_t s;
    char *line = strdup("(ls)");
    int i = 0;
    int res = part_three(&s, line, i);

    cr_assert_eq(res, 0);
}

Test(find_parnethese, part_three_2)
{
    shell_t s;
    char *line = strdup("(ls -l)");
    int i = strlen(line) - 1;
    int res = part_three(&s, line, i);

    cr_assert_eq(res, 1);
}

Test(find_parnethese, part_two_1)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->disp = &printf;
    char *line = strdup("(ls -l)");
    int i = strlen(line) - 1;
    int res = part_two(s, line, i);

    cr_assert_eq(res, 1);
}

Test(find_parnethese, part_two_2, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->disp = &printf;
    char *line = strdup(")");
    int i = 0;
    int res = part_two(s, line, i);

    cr_assert_eq(res, 0);
}

Test(find_parnethese, part_two_3)
{
    shell_t s;
    char *line = strdup(" ");
    int i = 0;
    int res = part_two(&s, line, i);

    cr_assert_eq(res, 1);
}

Test(find_parnethese, find_erno_1, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->disp = &printf;
    char *line = strdup("(");
    int num_left = 1;
    int num_rigth = 0;
    int res = find_erno(s, line, num_left, num_rigth);
    fflush(stdout);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("Too many ('s.\n");
}

Test(find_parnethese, find_erno_2, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->disp = &printf;
    char *line = strdup(")");
    int num_left = 0;
    int num_rigth = 1;
    int res = find_erno(s, line, num_left, num_rigth);
    fflush(stdout);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("Too many )'s.\n");
}

Test(find_parnethese, find_erno_3, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->disp = &printf;
    char *line = strdup(")");
    int num_left = 0;
    int num_rigth = 0;
    int res = find_erno(s, line, num_left, num_rigth);

    cr_assert_eq(res, 0);
}

Test(find_parnethese, find_erno_4)
{
    shell_t s;
    char *line = strdup(" ");
    int num_left = 0;
    int num_rigth = 0;
    int res = find_erno(&s, line, num_left, num_rigth);

    cr_assert_eq(res, 1);
}

Test(find_parnethese, look_for_parenthesis_1)
{
    shell_t s;
    char *line = strdup("ls -l");
    int res = look_for_parenthesis(&s, line);

    cr_assert_eq(res, 1);
}

Test(find_parnethese, look_for_parenthesis_3, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->disp = &printf;
    char *line = strdup("(ls -l");
    int res = look_for_parenthesis(s, line);
    fflush(stdout);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("Too many ('s.\n");
}

Test(check_parentheses, check_if_parenthese_ls_l)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->disp = &printf;
    char *line = strdup("(ls -l)");
    char *expected_result = "ls -l";

    check_if_parenthese(s, line);
    cr_assert_str_eq(line, expected_result, "Expected \"%s\" but got \"%s\"", expected_result, line);
}

Test(fill_parentheses, fill_new_arr_test)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->par = calloc(1, sizeof(par_t));
    s->par->array = calloc(2, sizeof(char *));
    s->par->array[0] = strdup("ls -l ; pwd || echo hello && echo world");
    s->par->num_par = 4;

    fill_new_arr(s);

    cr_assert_str_eq(s->par->commands[0][0], "ls -l ");
    cr_assert_str_eq(s->par->commands[0][1], ";");
    cr_assert_str_eq(s->par->commands[1][0], "pwd ");
    cr_assert_str_eq(s->par->commands[1][1], "||");
    cr_assert_str_eq(s->par->commands[2][0], "echo hello ");
    cr_assert_str_eq(s->par->commands[2][1], "&&");
    cr_assert_str_eq(s->par->commands[3][0], "echo world");
    cr_assert_null(s->par->commands[4]);
}

Test(pos_parentheses, no_pipe_test)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->par = calloc(1, sizeof(par_t));
    int num_left = 1;
    char *string = strdup("(ls -l)");

    int ret = pos_parenthese(s, string, num_left);

    cr_assert_eq(ret, 1, "Expected 1 but got %d", ret);
}
