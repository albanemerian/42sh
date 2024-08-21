/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_histroy
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// handle_exlamations.c
Test(handle_exclamation, print_linked_list, .init = redirect_all_std)
{
    struct hist *head = malloc(sizeof(struct hist));
    head->id = 1;
    head->hour = 12;
    head->min = 30;
    head->str = "ls";
    head->next = NULL;

    print_linked_list(head);
    cr_assert_stdout_eq_str("1 12:30 ls\n");
}

Test(handle_exclamation, reverse_linked_list, .init = redirect_all_std)
{
    struct hist *head = malloc(sizeof(struct hist));
    head->id = 1;
    head->hour = 12;
    head->min = 30;
    head->str = "ls";
    head->next = NULL;

    struct hist *new_head = reverse_linked_list(head);
    cr_assert_eq(new_head->id, 1);
    cr_assert_eq(new_head->hour, 12);
    cr_assert_eq(new_head->min, 30);
    cr_assert_str_eq(new_head->str, "ls");
}

Test(handle_exclamation, handle_exclamation_not_found, .init = redirect_all_std)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->history = calloc(1, sizeof(history_t));

    handle_exclamation(shell, NULL, "!echo");
    cr_assert_stdout_eq_str("echo: Event not found.\n");
}

Test(handle_exclamation, handle_exclamation_ok, .init = redirect_all_std)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->history = calloc(1, sizeof(history_t));
    shell->history->hist = calloc(1, sizeof(struct hist));
    shell->history->hist->id = 1;
    shell->history->hist->hour = 12;
    shell->history->hist->min = 30;
    shell->history->hist->str = "echo";

    handle_exclamation(shell, NULL, "!echo");
    cr_assert_stdout_eq_str("echo: Event not found.\n");
}

Test(handle_exclamation, find_if_exclamation_1, .init = redirect_all_std)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->history = calloc(1, sizeof(history_t));

    int rv = find_if_exclamation(shell, NULL, "!echo");
    cr_assert_eq(rv, 1);
    cr_assert_stdout_eq_str("echo: Event not found.\n");
}

Test(handle_exclamation, find_if_exclamation_2, .init = redirect_all_std)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->history = calloc(1, sizeof(history_t));

    int rv = find_if_exclamation(shell, NULL, "echo");
    cr_assert_eq(rv, 0);
}

// history_handler.c
Test(history_handler, add_to_history_1, .init = redirect_all_std)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->history = calloc(1, sizeof(history_t));

    add_to_history(&shell->history->hist, shell, "ls");
    cr_assert_str_eq(shell->history->hist->str, "ls");
}

Test(history_handler, add_to_history_2, .init = redirect_all_std)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->history = calloc(1, sizeof(history_t));

    add_to_history(&shell->history->hist, shell, "ls");
    add_to_history(&shell->history->hist, shell, "echo");
    cr_assert_str_eq(shell->history->hist->next->str, "echo");
}

Test(history_handler, add_to_history_3, .init = redirect_all_std)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->history = calloc(1, sizeof(history_t));

    add_to_history(&shell->history->hist, shell, "ls");
    add_to_history(&shell->history->hist, shell, "echo");
    add_to_history(&shell->history->hist, shell, "pwd");
    cr_assert_str_eq(shell->history->hist->next->next->str, "pwd");
}

Test(history_handler, add_to_history_4, .init = redirect_all_std)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->history = calloc(1, sizeof(history_t));

    add_to_history(&shell->history->hist, shell, "ls");
    add_to_history(&shell->history->hist, shell, "echo");
    add_to_history(&shell->history->hist, shell, "pwd");
    add_to_history(&shell->history->hist, shell, "ls");
    cr_assert_str_eq(shell->history->hist->next->next->next->str, "ls");
}

Test(history_handler, history_handler, .init = redirect_all_std)
{
    shell_t *shell = calloc(1, sizeof(shell_t));
    shell->disp = &printf;
    shell->history = calloc(1, sizeof(history_t));
    shell->base = calloc(1, sizeof(base_t));
    shell->base->arr = calloc(1, sizeof(char *));
    shell->history->hist = calloc(1, sizeof(struct hist));
    shell->history->hist->str = strdup("ls");
    shell->history->hist->next = calloc(1, sizeof(struct hist));
    shell->history->hist->next->str = strdup("echo");

    history_handler(shell, NULL);
    fflush(stdout);
}
