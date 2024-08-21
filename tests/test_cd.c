/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_cd
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "../include/minishell.h"

void setup(void)
{
    cr_redirect_stdout();
}

Test(cd_home, valid_test)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(shell->base));
    shell->base->home = strdup("/home/test");
    shell->base->oldpwd = NULL;
    shell->base->status = 0;
    shell->disp = printf;

    cd_home(shell, "/home/test");
}

Test(cd_home, invalid_test)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->home = NULL;
    shell.base->oldpwd = NULL;
    shell.base->status = 0;
    shell.disp = printf;

    cd_home(&shell, "/home/test");
    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");
}

// Test(handle, valid_test)
Test(handle, invalid_test)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("cd");
    shell.base->arr[1] = strdup("-");
    shell.base->arr[2] = NULL;
    shell.base->oldpwd = NULL;
    shell.base->status = 0;
    shell.disp = printf;

    cr_assert_eq(handle(&shell, "/home/test"), 1, "Expected error");
}

Test(handle, invalid_directory)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("cd");
    shell.base->arr[1] = strdup("/nonexistent");
    shell.base->arr[2] = NULL;
    shell.base->oldpwd = NULL;
    shell.base->status = 0;
    shell.disp = printf;

    cr_assert_eq(handle(&shell, "/home/test"), 1, "Expected error");
}

Test(perme_handler, valid_directory)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("cd");
    shell.base->arr[1] = strdup("/home/test");
    shell.base->arr[2] = NULL;
    shell.base->oldpwd = NULL;
    shell.base->status = 0;
    shell.disp = printf;
    cr_assert_eq(shell.base->status, 0, "Expected shell status to be 0");

}

Test(perme_handler, invalid_directory)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("cd");
    shell.base->arr[1] = strdup("/nonexistent");
    shell.base->arr[2] = NULL;
    shell.base->oldpwd = NULL;
    shell.base->status = 0;
    shell.disp = printf;

    cr_assert_eq(perme_handler(&shell, "/home/test"), 1, "Expected error");
    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");

}

Test(perme_handler, not_a_directory)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("cd");
    shell.base->arr[1] = strdup("/home/test/file.txt");
    shell.base->arr[2] = NULL;
    shell.base->oldpwd = NULL;
    shell.base->status = 0;
    shell.disp = printf;

    cr_assert_eq(perme_handler(&shell, "/home/test"), 1, "Expected error");
    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");
}

Test(perme_handlers, not_a_directory, .init = setup)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("cd");
    shell.base->arr[1] = strdup("/home/test/file.txt");
    shell.base->arr[2] = NULL;
    shell.base->oldpwd = NULL;
    shell.base->status = 0;
    shell.disp = printf;

    cr_assert_eq(perme_handler(&shell, "/home/test"), 1, "Expected error");
    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");

    fflush(stdout);
}
