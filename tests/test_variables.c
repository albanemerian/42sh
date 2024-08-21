/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_variables
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// set_variable.c
Test(set_variable, check_existant_var_1)
{
    set_list_t *begin = calloc(1, sizeof(set_list_t));
    begin->var = strdup("TEST");
    begin->content = strdup("42");
    begin->next = calloc(1, sizeof(set_list_t));
    begin->next->var = strdup("TEST2");

    cr_assert_eq(check_existant_var(begin, "TEST2"), 1);
}

Test(set_variable, check_existant_var_2)
{
    set_list_t *begin = calloc(1, sizeof(set_list_t));
    begin->var = strdup("TEST");
    begin->content = strdup("42");
    begin->next = calloc(1, sizeof(set_list_t));
    begin->next->var = strdup("TEST2");

    cr_assert_eq(check_existant_var(begin, "TEST3"), 0);
}

Test(set_variable, add_variables)
{
    set_list_t *begin = calloc(1, sizeof(set_list_t));
    begin->var = strdup("TEST");
    begin->content = strdup("42");
    begin->next = calloc(1, sizeof(set_list_t));
    begin->next->var = strdup("TEST2");

    char **var = calloc(1, sizeof(char *) * 2);
    var[0] = strdup("TEST3");
    var[1] = strdup("43");

    set_list_t *new_node = add_variables(var, &begin);

    cr_assert_str_eq(new_node->var, "TEST3");
    cr_assert_str_eq(new_node->content, "43");
}

Test(set_variable, add_variables_null)
{
    set_list_t *begin = calloc(1, sizeof(set_list_t));
    char **var = calloc(1, sizeof(char *) * 2);
    var[0] = strdup("TEST3");
    set_list_t *new_node = add_variables(var, &begin);

    cr_assert_str_eq(new_node->var, "TEST3");
    cr_assert_null(new_node->content);
}

Test(set_variable, upt_variables_1)
{
    set_list_t *begin = calloc(1, sizeof(set_list_t));
    begin->var = strdup("TEST");
    begin->content = strdup("42");
    begin->next = calloc(1, sizeof(set_list_t));
    begin->next->var = strdup("TEST2");

    char **var = calloc(1, sizeof(char *) * 2);
    var[0] = strdup("TEST2");
    var[1] = strdup("43");

    set_list_t *new_node = upt_variables(var, &begin);

    cr_assert_str_eq(new_node->var, "TEST");
    cr_assert_str_eq(new_node->content, "42");
    cr_assert_str_eq(new_node->next->var, "TEST2");
    cr_assert_str_eq(new_node->next->content, "43");
}

Test(set_variable, upt_variables_2)
{
    set_list_t *begin = calloc(1, sizeof(set_list_t));
    begin->var = strdup("TEST");
    begin->content = strdup("42");
    begin->next = calloc(1, sizeof(set_list_t));
    begin->next->var = strdup("TEST2");

    char **var = calloc(1, sizeof(char *) * 2);
    var[0] = strdup("TEST3");
    var[1] = strdup("43");

    set_list_t *new_node = upt_variables(var, &begin);

    cr_assert_str_eq(new_node->var, "TEST");
    cr_assert_str_eq(new_node->content, "42");
    cr_assert_str_eq(new_node->next->var, "TEST2");
    cr_assert_null(new_node->next->content);
}

Test(set_variable, set_variable_1)
{
    set_list_t *begin = calloc(1, sizeof(set_list_t));
    begin->var = strdup("TEST");
    begin->content = strdup("42");
    begin->next = calloc(1, sizeof(set_list_t));
    begin->next->var = strdup("TEST2");

    set_variable("TEST3=43", &begin);

    cr_assert_str_eq(begin->var, "TEST");
    cr_assert_str_eq(begin->content, "42");
    cr_assert_str_eq(begin->next->var, "TEST2");
    cr_assert_null(begin->next->content);
}

Test(set_variable, set_variable_2)
{
    set_list_t *begin = calloc(1, sizeof(set_list_t));
    begin->var = strdup("TEST");
    begin->content = strdup("42");
    begin->next = calloc(1, sizeof(set_list_t));
    begin->next->var = strdup("TEST2");

    set_variable("TEST=43", &begin);

    cr_assert_str_eq(begin->var, "TEST");
    cr_assert_str_eq(begin->content, "43");
    cr_assert_str_eq(begin->next->var, "TEST2");
    cr_assert_null(begin->next->content);
}

// set.c
Test(set_func, set_func)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->base = calloc(1, sizeof(base_t));
    s->base->arr = calloc(1, sizeof(char *));
    int rv = set_func(s, NULL);

    cr_assert_eq(rv, 0);
}

Test(set, modif_special_variables)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));

    modif_special_variables(s);

    cr_assert_null(s->variables);
}

// sort_set.c
Test(sort_set, sort_set_1)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));
    s->variables->var = strdup("TEST");
    s->variables->content = strdup("42");
    s->variables->next = calloc(1, sizeof(set_list_t));
    s->variables->next->var = strdup("TEST2");

    sort_set(s, NULL);

    cr_assert_str_eq(s->variables->var, "TEST");
    cr_assert_str_eq(s->variables->content, "42");
    cr_assert_str_eq(s->variables->next->var, "TEST2");
    cr_assert_null(s->variables->next->content);
}

Test(sort_set, sort_set_2)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));
    s->variables->var = strdup("TEST2");
    s->variables->content = strdup("42");
    s->variables->next = calloc(1, sizeof(set_list_t));
    s->variables->next->var = strdup("TEST");

    sort_set(s, NULL);

    cr_assert_str_eq(s->variables->var, "TEST");
    cr_assert_null(s->variables->content);
    cr_assert_str_eq(s->variables->next->var, "TEST2");
    cr_assert_str_eq(s->variables->next->content, "42");
}

// unset.c
Test(unset_func, unset_func_1, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->disp = &printf;
    s->base = calloc(1, sizeof(base_t));
    s->base->arr = calloc(1, sizeof(char *));
    s->base->arr[0] = strdup("unset");

    int rv = unset_func(s, NULL);
    fflush(stdout);

    cr_assert_eq(rv, 0);
    cr_assert_eq(s->base->status, 1);
    cr_assert_stdout_eq_str("unset: Too few arguments.\n");
}

Test(unset_func, unset_func_2)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->disp = &printf;
    s->base = calloc(1, sizeof(base_t));
    s->base->arr = calloc(4, sizeof(char *));
    s->base->arr[0] = strdup("unset");
    s->base->arr[1] = strdup("TEST");
    s->base->arr[2] = strdup("TEST2");

    s->variables = calloc(1, sizeof(set_list_t));
    s->variables->var = strdup("TEST");
    s->variables->content = strdup("42");
    s->variables->next = calloc(1, sizeof(set_list_t));
    s->variables->next->var = strdup("TEST2");

    int rv = unset_func(s, NULL);
    fflush(stdout);

    cr_assert_eq(rv, 0);
    cr_assert_null(s->variables);
}

// specials/cwd.c
Test(cwd, cwd)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));

    set_list_t *rv = cwd(s);

    cr_assert_str_eq(rv->var, "cwd");
    cr_assert_not_null(rv->content);
}

// specials/cwdcwd.c

// specials/home.c

// specials/ignoreof.c
Test(ignoreof, is_ignoreof_1)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));
    s->variables->var = strdup("ignoreof");
    s->variables->content = strdup("on");

    int rv = is_ignoreof(s);

    cr_assert_eq(rv, 1);
}

Test(ignoreof, is_ignoreof_2)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));
    s->variables->var = strdup("ignoreof");
    s->variables->content = strdup("off");

    int rv = is_ignoreof(s);

    cr_assert_eq(rv, 0);
}

Test(ignoreof, is_ignoreof_3)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(2, sizeof(set_list_t));
    s->variables->var = strdup("toto");
    s->variables->content = strdup("off");
    s->variables->next = calloc(1, sizeof(set_list_t));
    s->variables->next->var = strdup("ignoreof");

    int rv = is_ignoreof(s);

    cr_assert_eq(rv, 0);
}

// specials/precmd.c

// specials/prompt.c
Test(prompt, prompt)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));

    set_list_t *rv = prompt(s);

    cr_assert_str_eq(rv->var, "prompt");
    cr_assert_not_null(rv->content);
}

Test(prompt, display_prompt_1, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));
    s->variables->var = strdup("prompt");
    s->variables->content = strdup("[42sh@epitech %s]$ ");
    s->variables->next = calloc(1, sizeof(set_list_t));
    s->variables->next->var = strdup("cwd");
    s->variables->next->content = strdup("/home");
    s->disp = &printf;

    display_prompt(s);
    fflush(stdout);

    cr_assert_stdout_eq_str("[42sh@epitech home]$ ");
}

Test(prompt, display_prompt_2, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));
    s->variables->var = strdup("prompt");
    s->variables->content = strdup("[42sh@epitech %s]$ ");
    s->disp = &printf;

    display_prompt(s);
    fflush(stdout);

    cr_assert_stdout_eq_str("[42sh@epitech  ]$ ");
}

Test(prompt, display_prompt_3, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));
    s->variables->var = strdup("cwd");
    s->variables->content = strdup("home");
    s->variables->next = calloc(1, sizeof(set_list_t));
    s->variables->next->var = strdup("prompt");
    s->variables->next->content = strdup("[42sh@epitech %s]$ ");
    s->disp = &printf;

    display_prompt(s);
    fflush(stdout);

    cr_assert_stdout_eq_str("[42sh@epitech home]$ ");
}

Test(prompt, display_prompt_4, .init = redirect_all_std)
{
    shell_t *s = calloc(1, sizeof(shell_t));
    s->variables = calloc(1, sizeof(set_list_t));
    s->variables->var = strdup("cwd");
    s->variables->content = strdup("home");
    s->disp = &printf;

    display_prompt(s);
    fflush(stdout);
}

Test(parse_array, basic_parsing)
{
    char *array[] = {"oui=non", NULL};
    char **result = parse_array(array);

    cr_assert_not_null(result);
}

Test(parse_array, complexe_parsing)
{
    char *array[] = {"oui=non", "=non", "test", "maybe", NULL};
    char **result = parse_array(array);

    cr_assert_null(result);
}

Test(parse_array, array_null)
{
    char **array = NULL;
    char **result = parse_array(array);

    cr_assert_null(result);
}

Test(parse_array, begin_equal)
{
    char *array[] = {"=", "oui", NULL};
    char **result = parse_array(array);

    cr_assert_null(result);
}

Test(parse_array, three_words)
{
    char *array[] = {"oui", "=", "oui", NULL};
    char **result = parse_array(array);

    cr_assert_not_null(result);
}

Test(parse_array, two_words)
{
    char *array[] = {"oui=", "oui", NULL};
    char **result = parse_array(array);

    cr_assert_not_null(result);
}

Test(parse_array, not_begin_with_a_letter)
{
    char *array[] = {"oui", "=oui", NULL};
    char **result = parse_array(array);

    cr_assert_null(result);
}

Test(parse_dollar, missing_right)
{
    shell_t *shell = malloc(sizeof(shell_t));

    shell->base = malloc(sizeof(base_t));
    shell->base->arr = calloc(1, sizeof(char *) * 2);
    shell->base->arr[0] = strdup("${err");
    shell->base->arr[1] = NULL;

    cr_assert_eq(parse_dollar(shell, 0, 0), 1);
}

Test(parse_dollar, illegal_curly)
{
    shell_t *shell = malloc(sizeof(shell_t));

    shell->base = malloc(sizeof(base_t));
    shell->base->arr = calloc(1, sizeof(char *) * 2);
    shell->base->arr[0] = strdup("${{err}");
    shell->base->arr[1] = NULL;

    cr_assert_eq(parse_dollar(shell, 0, 0), 1);
}

Test(parse_dollar, newline)
{
    shell_t *shell = malloc(sizeof(shell_t));

    shell->base = malloc(sizeof(base_t));
    shell->base->arr = calloc(1, sizeof(char *) * 2);
    shell->base->arr[0] = strdup("${");
    shell->base->arr[1] = NULL;

    cr_assert_eq(parse_dollar(shell, 0, 0), 1);
}

Test(parse_dollar, no_dollar)
{
    shell_t *shell = malloc(sizeof(shell_t));

    shell->base = malloc(sizeof(base_t));
    shell->base->arr = calloc(1, sizeof(char *) * 2);
    shell->base->arr[0] = strdup("err");
    shell->base->arr[1] = NULL;

    cr_assert_eq(parse_dollar(shell, 0, 0), 2);
}


Test(my_cwdcmd, no_cwdcmd_variable)
{
    shell_t shell;
    shell.variables = malloc(sizeof(set_list_t));
    shell.variables->var = strdup("other");
    shell.variables->content = strdup("command");
    shell.variables->next = NULL;

    int option_called = 0;
    void option(shell_t *s, char *str) {
        (void)s;
        (void)str;
        option_called = 1;
    }

    my_cwdcmd(&shell);
    cr_assert_eq(option_called, 0, "Expected option not to be called");
}

Test(last_elem, valid_history)
{
    shell_t shell;
    shell.history = malloc(sizeof(*shell.history));
    shell.history->hist = malloc(sizeof(struct hist));
    shell.history->hist->str = strdup("command1");
    shell.history->hist->next = malloc(sizeof(struct hist));
    shell.history->hist->next->str = strdup("command2");
    shell.history->hist->next->next = NULL;

    char *last = last_elem(&shell);

    cr_assert_str_eq(last, "command2", "Expected last element of history to be 'command2'");
}

Test(last_cmd, no_history)
{
    shell_t shell;
    shell.history = malloc(sizeof(*shell.history));
    shell.history->hist = NULL;
    shell.variables = NULL;

    set_list_t *set_variable(char *cmd, set_list_t **variables) {
        (void)variables;
        set_list_t *new = malloc(sizeof(set_list_t));
        new->var = strdup(cmd);
        new->content = NULL;
        new->next = NULL;
        return new;
    }

    set_list_t *last = last_cmd(&shell);
    cr_assert_str_eq(last->var, "_", "Expected last command to be '_'");
}

Test(my_precmd, no_precmd_variable)
{
    shell_t shell;
    shell.variables = malloc(sizeof(set_list_t));
    shell.variables->var = strdup("other");
    shell.variables->content = strdup("command");
    shell.variables->next = NULL;

    int option_called = 0;
    void option(shell_t *s, char *str) {
        (void)s;
        (void)str;
        option_called = 1;
    }

    my_precmd(&shell);

    cr_assert_eq(option_called, 0, "Expected option not to be called");
}

Test(my_cwdcmdn, no_cwdcmd_variable)
{
    shell_t shell;
    shell.variables = malloc(sizeof(set_list_t));
    shell.variables->var = strdup("other");
    shell.variables->content = strdup("command");
    shell.variables->next = NULL;
    int option_called = 0;
    void option(shell_t *s, char *str) {
        (void)s;
        (void)str;
        option_called = 1;
    }
    my_cwdcmd(&shell);
    cr_assert_eq(option_called, 0, "Expected option not to be called");
}

Test(last_element, valid_history)
{
    shell_t shell;
    shell.history = malloc(sizeof(*shell.history));
    shell.history->hist = malloc(sizeof(struct hist));
    shell.history->hist->str = strdup("command1");
    shell.history->hist->next = malloc(sizeof(struct hist));
    shell.history->hist->next->str = strdup("command2");
    shell.history->hist->next->next = NULL;

    char *last = last_elem(&shell);
    cr_assert_str_eq(last, "command2", "Expected last element of history to be 'command2'");
}

Test(last_cmd, valid_history)
{
    shell_t shell;
    shell.history = malloc(sizeof(*shell.history));
    shell.history->hist = malloc(sizeof(struct hist));
    shell.history->hist->str = strdup("command1");
    shell.history->hist->next = malloc(sizeof(struct hist));
    shell.history->hist->next->str = strdup("command2");
    shell.history->hist->next->next = NULL;
    shell.variables = NULL;

    set_list_t *set_variable(char *cmd, set_list_t **variables) {
        (void)variables;
        set_list_t *new = malloc(sizeof(set_list_t));
        new->var = strdup(cmd);
        new->content = NULL;
        new->next = NULL;
        return new;
    }
    set_list_t *last = last_cmd(&shell);
}

Test(last_cmd_bn, no_history)
{
    shell_t shell;
    shell.history = malloc(sizeof(*shell.history));
    shell.history->hist = NULL;
    shell.variables = NULL;

    set_list_t *set_variable(char *cmd, set_list_t **variables) {
        (void)variables;
        set_list_t *new = malloc(sizeof(set_list_t));
        new->var = strdup(cmd);
        new->content = NULL;
        new->next = NULL;
        return new;
    }

    set_list_t *last = last_cmd(&shell);

    cr_assert_str_eq(last->var, "_", "Expected last command to be '_'");
}

Test(my_postcmd, no_postcmd_variable)
{
    shell_t shell;
    shell.variables = malloc(sizeof(set_list_t));
    shell.variables->var = strdup("other");
    shell.variables->content = strdup("command");
    shell.variables->next = NULL;

    int option_called = 0;
    void option(shell_t *s, char *str) {
        (void)s;
        (void)str;
        option_called = 1;
    }
    my_postcmd(&shell);
    cr_assert_eq(option_called, 0, "Expected option not to be called");
}
