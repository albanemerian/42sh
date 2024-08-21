/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_alias
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// alias_handler.c
Test(alias_handler, alias_handler_1, .init = redirect_all_std)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 2);
    shell->base->arr[0] = "alias";
    shell->base->arr[1] = NULL;
    shell->alias = create_list();
    push_to_list_tail(shell->alias, create_alias(shell));
    int rv = alias_handler(shell, NULL);
    cr_assert_eq(rv, 0);
}

Test(alias_handler, alias_handler_1_1, .init = redirect_all_std)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 2);
    shell->base->arr[0] = "alias";
    shell->base->arr[1] = NULL;
    shell->alias = create_list();
    int rv = alias_handler(shell, NULL);
    cr_assert_eq(rv, 0);
}

Test(alias_handler, alias_handler_1_2, .init = redirect_all_std)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 2);
    shell->base->arr[0] = "alias";
    shell->base->arr[1] = NULL;
    shell->alias = create_list();
    push_to_list_tail(shell->alias, create_alias(shell));
    int rv = alias_handler(shell, NULL);
    cr_assert_eq(rv, 0);
}

Test(alias_handler, alias_handler_2)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 3);
    shell->base->arr[0] = "alias";
    shell->base->arr[1] = "toto";
    shell->base->arr[2] = NULL;
    int rv = alias_handler(shell, NULL);
    cr_assert_eq(rv, 0);
}

Test(alias_handler, alias_handler_3)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 4);
    shell->base->arr[0] = "alias";
    shell->base->arr[1] = "toto";
    shell->base->arr[2] = "ls";
    shell->base->arr[3] = NULL;
    shell->alias = create_list();
    int rv = alias_handler(shell, NULL);
    cr_assert_eq(rv, 0);
}

Test(alias_handler, unalias_handler_1, .init = redirect_all_std)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 2);
    shell->base->arr[0] = "unalias";
    shell->base->arr[1] = NULL;
    int rv = unalias_handler(shell, NULL);
    cr_assert_eq(rv, 1);
    cr_assert_stdout_eq_str("unalias: Too few arguments.\n");
}

Test(alias_handler, unalias_handler_2, .init = redirect_all_std)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 3);
    shell->base->arr[0] = "unalias";
    shell->base->arr[1] = "toto";
    shell->base->arr[2] = NULL;
    shell->alias = create_list();
    push_to_list_tail(shell->alias, create_alias(shell));
    int rv = unalias_handler(shell, NULL);
    cr_assert_eq(rv, 0);
}

Test(split_command, split_command_1)
{
    alias_t *new_alias = malloc(sizeof(alias_t));
    new_alias->command = malloc(sizeof(char *) * 2);
    new_alias->command[0] = "ls";
    new_alias->command[1] = NULL;
    char *command_str = "ls";
    split_command(command_str, new_alias);
    cr_assert_str_eq(new_alias->command[0], "ls");
}

//alias_command_line.c
Test(simple_cases, simple_cases_1)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 2);
    shell->base->arr[0] = "ls";
    shell->base->arr[1] = NULL;
    char **alias_commands = malloc(sizeof(char *) * 2);
    alias_commands[0] = "ls";
    alias_commands[1] = NULL;
    char **rv = simple_cases(alias_commands, 0, shell);
    cr_assert_str_eq(rv[0], "ls");
}

Test(complex_case, complex_case_1)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 2);
    shell->base->arr[0] = "ls";
    shell->base->arr[1] = NULL;
    char **alias_commands = malloc(sizeof(char *) * 2);
    alias_commands[0] = "ls";
    alias_commands[1] = NULL;
    char **rv = complex_case(0, alias_commands, shell);
    alias_commands = NULL;
    shell->base->arr = NULL;
    char **rv2 = simple_cases(alias_commands, 0, shell);
    cr_assert_null(rv2);
    char **rv3 = complex_case(0, alias_commands, shell);
    cr_assert_null(rv3);
}

//find_alias.c
Test(handle_alias_loop, handle_alias_loop_1)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->alias = create_list();
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 2);
    shell->base->arr[0] = "ls";
    shell->base->arr[1] = NULL;
    int rv = handle_alias_loop(shell, 0);
    cr_assert_eq(rv, 0);
}

Test(find_alias, find_alias_1)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->alias = create_list();
    shell->base = malloc(sizeof(base_t));
    shell->base->arr = malloc(sizeof(char *) * 2);
    shell->base->arr[0] = "ls";
    shell->base->arr[1] = NULL;
    alias_t *rv = find_alias(shell, 0);
    cr_assert_null(rv);
}
