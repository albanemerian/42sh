/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_priorities
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// delim_tok.c
Test(delim_tok, fill_token_1)
{
    tok_delim_t *result = calloc(1, sizeof(tok_delim_t));
    char *delim_found = ";";
    char *ret = "ls";

    result = fill_token(result, delim_found, ret);
    cr_assert_str_eq(result->token, "ls");
    cr_assert_str_eq(result->delimiter, ";");
}

Test(delim_tok, fill_token_2)
{
    tok_delim_t *result = calloc(1, sizeof(tok_delim_t));
    char *delim_found = NULL;
    char *ret = "ls";

    result = fill_token(result, delim_found, ret);
    cr_assert_str_eq(result->token, "ls");
    cr_assert_null(result->delimiter);
}

Test(delim_tok, find_delimiter_1)
{
    char *p = "ls;";

    cr_assert_str_eq(find_delimiter(p, ";"), ";");
}

Test(delim_tok, find_delimiter_2)
{
    char *p = "ls";

    cr_assert_null(find_delimiter(p, ";"));
}

Test(delim_tok, update_source_1)
{
    char *src = strdup("ls;");
    tok_delim_t *result = calloc(1, sizeof(tok_delim_t));
    char *p = NULL;

    update_source(&src, p, result);
    cr_assert_str_empty(result->delimiter);
    cr_assert_null(src);
}

Test(delim_tok, update_source_2)
{
    char *src = strdup("ls");
    tok_delim_t *result = calloc(1, sizeof(tok_delim_t));
    char *p = src;

    update_source(&src, p, result);
    cr_assert_null(result->delimiter);
    cr_assert_not_null(src);
}

Test(delim_tok, strtok_custom_1)
{
    char *str = strdup("ls;");
    char *delimiters = ";";
    tok_delim_t *result = strtok_custom(str, delimiters);

    cr_assert_str_eq(result->token, "ls");
    cr_assert_str_eq(result->delimiter, ";");
}

Test(delim_tok, strtok_custom_2)
{
    char *str = strdup("ls;toto");
    char *delimiters = ";";
    tok_delim_t *result = strtok_custom(str, delimiters);

    cr_assert_str_eq(result->token, "ls");
    cr_assert_str_eq(result->delimiter, ";");

    result = strtok_custom(NULL, delimiters);
    cr_assert_str_eq(result->token, "toto");

    result = strtok_custom(NULL, delimiters);
    cr_assert_null(result);
}

// find_priorities.c
Test(find_priorities, find_posibilities_1)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->queue = calloc(1, sizeof(queue_t));
    char *string = strdup("ls;ls");
    int nb_operrator = 0;

    cr_assert_eq(find_posibilities(shell, string, nb_operrator), 1);
    cr_assert(shell->queue->semicolon);
}

Test(find_priorities, find_posibilities_2)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->queue = calloc(1, sizeof(queue_t));
    char *string = strdup("ls&&ls");
    int nb_operrator = 0;

    cr_assert_eq(find_posibilities(shell, string, nb_operrator), 1);
    cr_assert(shell->queue->and_op);
}

Test(find_priorities, find_posibilities_3)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->queue = calloc(1, sizeof(queue_t));
    char *string = strdup("ls||ls");
    int nb_operrator = 0;

    cr_assert_eq(find_posibilities(shell, string, nb_operrator), 1);
    cr_assert(shell->queue->pipe);
}

Test(find_priorities, check_for_operators_1)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->queue = calloc(1, sizeof(queue_t));
    char *string = strdup("ls;ls");

    cr_assert_eq(check_for_operators(shell, NULL, string), 1);
    cr_assert(shell->queue->semicolon);
}

Test(find_priorities, check_for_operators_2)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->queue = calloc(1, sizeof(queue_t));
    char *string = strdup("ls");

    cr_assert_eq(check_for_operators(shell, NULL, string), 0);
}

// init_commands.c
Test(init_commands, init_commands_1)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->queue = calloc(1, sizeof(queue_t));
    char *string = strdup("ls;ls");
    int nb_operator = 1;

    init_commands(shell, string, nb_operator);
    cr_assert_str_eq(shell->queue->commands[0][0], "ls");
    cr_assert_str_eq(shell->queue->commands[0][1], ";");
    cr_assert_not_null(shell->queue->commands[1]);
}
