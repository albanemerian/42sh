/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_gork
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include <errno.h>
#include "../include/minishell.h"

// Test(handle_error, enoexec)
// {
//     shell_t shell;
//     shell.base = malloc(sizeof(*shell.base));
//     shell.base->arr = malloc(sizeof(char *) * 2);
//     shell.base->arr[0] = strdup("command");
//     shell.base->arr[1] = NULL;
//     shell.base->status = 0;

//     errno = ENOEXEC;

//     handle_error(&shell);

//     cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");

//     free(shell.base->arr[0]);
//     free(shell.base->arr);
//     free(shell.base);
// }

// Test(handle_error, eacces)
// {
//     shell_t shell;
//     shell.base = malloc(sizeof(*shell.base));
//     shell.base->arr = malloc(sizeof(char *) * 2);
//     shell.base->arr[0] = strdup("command");
//     shell.base->arr[1] = NULL;
//     shell.base->status = 0;

//     errno = EACCES;

//     handle_error(&shell);

//     cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");

//     free(shell.base->arr[0]);
//     free(shell.base->arr);
//     free(shell.base);
// }

// Test(handle_error, enoent)
// {
//     shell_t shell;
//     shell.base = malloc(sizeof(*shell.base));
//     shell.base->arr = malloc(sizeof(char *) * 2);
//     shell.base->arr[0] = strdup("command");
//     shell.base->arr[1] = NULL;
//     shell.base->status = 0;

//     errno = ENOENT;
//     handle_error(&shell);

//     cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");

//     free(shell.base->arr[0]);
//     free(shell.base->arr);
//     free(shell.base);
// }
