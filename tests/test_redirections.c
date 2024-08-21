/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_redirections
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}
