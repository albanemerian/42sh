/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** ncurses handler
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"
#include <ncurses.h>

int set_func(shell_t *shell, char **env)
{
    char **temp = NULL;

    if (my_tablen(shell->base->arr) == 1) {
        sort_set(shell, env);
        display_set(shell);
    }
    if (my_tablen(shell->base->arr) >= 2) {
        temp = parse_array(&shell->base->arr[1]);
        for (int i = 0; i < my_tablen(temp); i++) {
            change_term_value(shell, temp[i]);
            change_home_value(shell, temp[i]);
            shell->variables = set_variable(temp[i],
                &shell->variables);
        }
    }
    return 0;
}

static char *find_var(struct list *current, char *arg)
{
    char *temp = NULL;

    if (strncmp(current->str, &arg[1], strlen(arg) - 1) == 0) {
        if (current->str[strlen(arg) - 1] == '=') {
            temp = &current->str[strlen(arg)];
            return temp;
        }
    }
    return NULL;
}

static int choose_error_message(int left, int right, int letter)
{
    if (letter == 0 && left > 0) {
        print("Newline in variable name.\n");
        return 1;
    }
    if (left > right) {
        print("Missing '}'.\n");
        return 1;
    }
    return 0;
}

static int is_curly_bracket(char *str)
{
    int right = 0;
    int left = 0;
    int letter = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (left > 0)
            letter++;
        if (str[i] == '{')
            left++;
        if (str[i] == '}')
            right++;
        if (left == right && left == 1)
            return 2;
        if (left > 1) {
            printf("Illegal variable name.\n");
            return 1;
        }
    }
    return choose_error_message(left, right, letter);
}

static char *check_for_variable(char *arg, shell_t *shell)
{
    struct list *current = shell->current;
    set_list_t *list = shell->variables;
    char *temp = NULL;

    while (current != NULL) {
        temp = find_var(current, arg);
        if (temp != NULL)
            return temp;
        current = current->next;
    }
    while (list != NULL) {
        if (strcmp(list->var, &arg[1]) == 0)
            return list->content;
        list = list->next;
    }
    print("%s: Undefined variable.\n", &arg[1]);
    return NULL;
}

static int check_curly_right(char *curly)
{
    int size = 0;

    while (curly[size] != '\0') {
        if (curly[size] == '}')
            return size;
        size++;
    }
    return 0;
}

static int apply_dollar_parse_curly(shell_t *shell, int i, int j)
{
    char *result = NULL;
    char *temp = &shell->base->arr[i][j + 1];
    int size = check_curly_right(temp) + j + 1;

    temp = my_strndup(temp, check_curly_right(temp));
    temp = check_for_variable(temp, shell);
    if (temp != NULL) {
        result = calloc(1, sizeof(char) * (j + strlen(temp) + size + 1));
        result = strncpy(result, shell->base->arr[i], j);
        result = strcat(result, temp);
        result = strcat(result, &shell->base->arr[i][size + 1]);
        shell->base->arr[i] = my_strdup(result);
        return 0;
    }
    shell->base->status = 1;
    return 1;
}

static int apply_dollar_parse(shell_t *shell, int i, int j)
{
    char *result = NULL;
    char *temp = NULL;

    temp = check_for_variable(&shell->base->arr[i][j], shell);
    if (temp != NULL) {
        result = calloc(1, sizeof(char) * (j + strlen(temp) + 1));
        result = strncpy(result, shell->base->arr[i], j);
        result = strcat(result, temp);
        shell->base->arr[i] = my_strdup(result);
        return 0;
    }
    shell->base->status = 1;
    return 1;
}

int parse_dollar(shell_t *shell, int i, int j)
{
    if (shell->base->arr[i][j] == '$') {
        if (is_curly_bracket(&shell->base->arr[i][j]) == 1) {
            shell->base->status = 1;
            return 1;
        }
        if (is_curly_bracket(&shell->base->arr[i][j]) == 2) {
            return apply_dollar_parse_curly(shell, i, j);
        } else {
            return apply_dollar_parse(shell, i, j);
        }
    }
    return 2;
}

void modif_special_variables(shell_t *shell)
{
    shell->variables = cwd(shell);
    shell->variables = home(shell);
    shell->variables = prompt(shell);
    shell->variables = term(shell);
}
