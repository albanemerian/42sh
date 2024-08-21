/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_env
*/

#include <criterion/criterion.h>
#include "minishell.h"

Test(check_str, valid_string)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("VARNAME");
    shell.base->arr[2] = NULL;
    shell.base->status = 0;

    cr_assert_eq(check_str(&shell), 0, "Expected 0 for valid string");
    cr_assert_eq(shell.base->status, 0, "Expected shell status to be 0");

    free(shell.base->arr[0]);
    free(shell.base->arr[1]);
    free(shell.base->arr);
    free(shell.base);
}

Test(check_str, invalid_string)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("VAR=NAME");
    shell.base->arr[2] = NULL;
    shell.base->status = 0;

    cr_assert_eq(check_str(&shell), 1, "Expected 1 for invalid string");
    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");

    free(shell.base->arr[0]);
    free(shell.base->arr[1]);
    free(shell.base->arr);
    free(shell.base);
}
Test(set_env, test_set_env_with_too_many_arguments)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->base = malloc(sizeof(shell->base));
    shell->base->arr = malloc(sizeof(char *) * 5);
    shell->base->arr[0] = "setenv";
    shell->base->arr[1] = "key";
    shell->base->arr[2] = "value";
    shell->base->arr[3] = "extra_argument";
    shell->base->arr[4] = NULL;

    int result = set_env(shell, NULL);
    cr_assert_eq(result, 1, "Function should return 1 when there are too many arguments");
}


Test(free_tab, test_free_tab)
{
    char **fun = malloc(3 * sizeof(char *));
    fun[0] = strdup("string1");
    fun[1] = strdup("string2");
    fun[2] = NULL;
    free_tab(fun);
    cr_assert(1);
}

Test(envv_sett, add_new_node_to_empty_list)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 4);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("VARNAME");
    shell.base->arr[2] = strdup("value");
    shell.base->arr[3] = NULL;
    shell.current = NULL;

    struct list *new_node = malloc(sizeof(struct list));
    struct list *head = NULL;

    envv_sett(&shell, head, new_node);

    cr_assert_str_eq(shell.current->str, "VARNAME=value", "Expected new node with 'VARNAME=value'");
    cr_assert_null(shell.current->next, "Expected next node to be NULL");
}

Test(envv_sett, add_new_node_to_non_empty_list)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 4);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("VARNAME");
    shell.base->arr[2] = strdup("value");
    shell.base->arr[3] = NULL;

    struct list *new_node = malloc(sizeof(struct list));
    struct list *head = malloc(sizeof(struct list));
    head->str = strdup("EXISTING=var");
    head->next = NULL;
    shell.current = head;

    envv_sett(&shell, head, new_node);

    cr_assert_str_eq(shell.current->str, "EXISTING=var", "Expected first node with 'EXISTING=var'");
    cr_assert_str_eq(shell.current->next->str, "VARNAME=value", "Expected new node with 'VARNAME=value'");
    cr_assert_null(shell.current->next->next, "Expected next node to be NULL");
}

Test(arg_count, three_arguments)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 4);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("VARNAME");
    shell.base->arr[2] = strdup("value");
    shell.base->arr[3] = NULL;
    shell.base->status = 0;

    cr_assert_eq(arg_count(&shell), 1, "Expected 1 for three arguments");
    cr_assert_eq(shell.base->status, 0, "Expected shell status to be 0");
}

Test(arg_count, four_arguments)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 5);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("VARNAME");
    shell.base->arr[2] = strdup("value");
    shell.base->arr[3] = strdup("extra");
    shell.base->arr[4] = NULL;
    shell.base->status = 0;

    cr_assert_eq(arg_count(&shell), 0, "Expected 0 for four arguments");
    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");
}

Test(fill_env, update_existing_variable)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 4);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("VARNAME");
    shell.base->arr[2] = strdup("new_value");
    shell.base->arr[3] = NULL;

    struct list *new_node = malloc(sizeof(struct list));
    struct list *head = malloc(sizeof(struct list));
    head->str = strdup("VARNAME=old_value");
    head->next = NULL;
    shell.current = head;

    char **fun = NULL;

    fill_env(&shell, head, fun, new_node);

    cr_assert_str_eq(shell.current->str, "VARNAME=new_value", "Expected 'VARNAME=new_value'");
    cr_assert_null(shell.current->next, "Expected next node to be NULL");
}

Test(fill_env, add_new_variable)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 4);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("NEWVAR");
    shell.base->arr[2] = strdup("value");
    shell.base->arr[3] = NULL;

    struct list *new_node = malloc(sizeof(struct list));
    struct list *head = malloc(sizeof(struct list));
    head->str = strdup("EXISTING=var");
    head->next = NULL;
    shell.current = head;

    char **fun = NULL;

    fill_env(&shell, head, fun, new_node);

    cr_assert_str_eq(shell.current->str, "EXISTING=var", "Expected first node with 'EXISTING=var'");
    cr_assert_str_eq(shell.current->next->str, "NEWVAR=value", "Expected new node with 'NEWVAR=value'");
    cr_assert_null(shell.current->next->next, "Expected next node to be NULL");
}

Test(two_arg, invalid_string)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 4);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("1VARNAME");
    shell.base->arr[2] = strdup("value");
    shell.base->arr[3] = NULL;
    shell.base->status = 0;

    char *env[] = {NULL};

    two_arg(&shell, env);

    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");
}

Test(set_env, four_arguments)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 5);
    shell.base->arr[0] = strdup("setenv");
    shell.base->arr[1] = strdup("VARNAME");
    shell.base->arr[2] = strdup("value");
    shell.base->arr[3] = strdup("extra");
    shell.base->arr[4] = NULL;
    shell.base->status = 0;

    char *env[] = {NULL};

    cr_assert_eq(set_env(&shell, env), 1, "Expected 1 for four arguments");
    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");
}

Test(pwd_env, update_pwd)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;

    struct list *head = malloc(sizeof(struct list));
    head->str = strdup("PWD=old_value");
    head->next = NULL;

    char *fun[] = {"PWD", NULL};
    char *temp_arg = NULL;

    pwd_env(&shell, fun, temp_arg, head);

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    char *expected = malloc(strlen("PWD=") + strlen(cwd) + 1);
    strcpy(expected, "PWD=");
    strcat(expected, cwd);

    cr_assert_str_eq(head->str, expected, "Expected updated PWD");
    cr_assert_eq(shell.base->status, 0, "Expected shell status to be 0");
}

Test(exit_func, two_arguments_not_a_number)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("exit");
    shell.base->arr[1] = strdup("not_a_number");
    shell.base->arr[2] = NULL;
    shell.base->status = 0;

    char *env[] = {NULL};

    cr_assert_eq(exit_func(&shell, env), 1, "Expected 1 for two arguments where the second is not a number");
    cr_assert_eq(shell.base->status, 1, "Expected shell status to be 1");
}

Test(alone_env, valid_env)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("env");
    shell.base->arr[1] = strdup("ENV1");
    shell.base->arr[2] = NULL;
    shell.current = NULL;

    struct list *head = NULL;
    struct list *new_node = malloc(sizeof(struct list));

    char *my_cat(char *str1, char *str2) {
        char *result = malloc(strlen(str1) + strlen(str2) + 1);
        strcpy(result, str1);
        strcat(result, str2);
        return result;
    }

    alone_env(&shell, head, new_node);

    cr_assert_str_eq(shell.current->str, "ENV1=", "Expected first element of list to be 'ENV1='");
    cr_assert_null(shell.current->next, "Expected second element of list to be NULL");
}

Test(env_alone, valid_env)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->arr = malloc(sizeof(char *) * 3);
    shell.base->arr[0] = strdup("env");
    shell.base->arr[1] = strdup("ENV1");
    shell.base->arr[2] = NULL;
    shell.current = malloc(sizeof(struct list));
    shell.current->str = strdup("ENV1=value1");
    shell.current->next = NULL;

    char *env[] = {NULL};

    char **my_str_to_word_array(char *str) {
        char **array = malloc(sizeof(char *) * 2);
        array[0] = strdup("ENV1");
        array[1] = NULL;
        return array;
    }

    cr_assert_eq(env_alone(&shell, env), 0, "Expected env_alone to return 0");
    cr_assert_str_eq(shell.current->str, "ENV1=", "Expected first element of list to be 'ENV1='");
}

Test(fill_str, valid_line)
{
    char *line = strdup("command arg1 arg2");
    char **array = fill_str(line);

    cr_assert_str_eq(array[0], "command", "Expected first element of array to be 'command'");
    cr_assert_str_eq(array[1], "arg1", "Expected second element of array to be 'arg1'");
    cr_assert_str_eq(array[2], "arg2", "Expected third element of array to be 'arg2'");
    cr_assert_null(array[3], "Expected fourth element of array to be NULL");
}

Test(make_array, valid_input)
{
    shell_t shell;
    shell.bticks = malloc(sizeof(*shell.bticks));
    shell.bticks->l = strdup("command `arg1` arg2");
    shell.bticks->quote = '`';

    char **p = malloc(sizeof(char *) * 2);
    p[0] = strdup("command");
    p[1] = NULL;

    char *res = strdup("`arg1`");

    char **n = malloc(sizeof(char *) * 2);
    n[0] = strdup("arg2");
    n[1] = NULL;

    char **array = make_array(&shell, p, res, n);

    cr_assert_str_eq(array[0], "command", "Expected first element of array to be 'command'");
    cr_assert_str_eq(array[1], "arg1", "Expected second element of array to be 'arg1'");
    cr_assert_str_eq(array[2], "arg2", "Expected third element of array to be 'arg2'");
    cr_assert_null(array[3], "Expected fourth element of array to be NULL");
}

