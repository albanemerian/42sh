/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_file_descriptor
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(nbw, basic_test)
{
    char str[] = "Hello, world!";
    int count = nbw(strdup(str), ", ");
    cr_assert_eq(count, 2, "Expected 2 words, but got %d", count);
}

Test(parse, basic_test)
{
    char str[] = "Hello, world!";
    char **words = parse(strdup(str), ", ");
    cr_assert_str_eq(words[0], "Hello", "First word should be 'Hello'");
    cr_assert_str_eq(words[1], "world!", "Second word should be 'world!'");
    cr_assert_null(words[2], "Third word should be NULL");
    for (int i = 0; i < 2; i++) {
        free(words[i]);
    }
    free(words);
}
