/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** option_handler
*/

#include <fcntl.h>
#include "minishell.h"

const char *flag_m[11] = {"env", "exit", "cd", "setenv", "unsetenv", "history",
    "set", "unset", "alias", "unalias", "echo"};

const int (*fm[11])(shell_t *, char **) = {
    &cmd_env, &exit_func, &cd_handler, &set_env, &unset_env, &history_handler,
    &set_func, &unset_func, &alias_handler, &unalias_handler, &echo_command};

static int is_empty(shell_t *shell)
{
    shell->base->result = 0;
    if (shell->base->l == NULL)
        return 1;
    for (int i = 0; shell->base->l[i] != '\0'; i++)
        if (shell->base->l[i] != ' ' && shell->base->l[i] != '\t')
            return 0;
    return 1;
}

static int replace_dollar(shell_t *shell, int i)
{
    int result = 0;

    for (int j = 0; shell->base->arr[i][j] != '\0'; j++) {
        result = parse_dollar(shell, i, j);
        if (result != 2)
            return result;
    }
    return 0;
}

static int check_dollar(shell_t *shell)
{
    for (int i = 0; shell->base->arr[i] != NULL; i++) {
        if (replace_dollar(shell, i) == 1)
            return 1;
    }
    return 0;
}

char **fill_str(char *line)
{
    char *fun = my_strdup(line);
    char **array = NULL;
    int i = 0;
    int j = 0;

    for (char *str = strtok(fun, " ()\t\n"); str;
        str = strtok(NULL, " ()\t\n"))
        i++;
    array = calloc(i + 1, sizeof(char *));
    for (char *str = strtok(line, " ()\t\n"); str;
        str = strtok(NULL, " ()\t\n")) {
        array[j] = strdup(str);
        j++;
    }
    array[j] = NULL;
    free(fun);
    free(line);
    return array;
}

char **make_array(shell_t *s, char **p, char *res, char **n)
{
    char **array = NULL;

    if (!p || !n)
        return NULL;
    array = calloc(my_tablen(p) + my_tablen(n) + 2, sizeof(char *));
    if (res[0] != '\0' && (how_many(res, '`') >= 2 ||
        s->bticks->quote == '`')) {
        res = strndup(s->bticks->l + posinstr(s->bticks->l, '`') + 1,
            posinstr(s->bticks->l + posinstr(s->bticks->l, '`') + 1, '`'));
    }
    for (int i = 0; p[i]; i++)
        array[i] = strdup(p[i]);
    array[my_tablen(p)] = res;
    for (int i = 0; n[i]; i++)
        array[my_tablen(p) + 1 + i] = strdup(n[i]);
    array[my_tablen(p) + my_tablen(n) + 1] = NULL;
    if (how_many(res, '`') >= 2 || s->bticks->quote == '`')
        handle_backticks(s, array, res);
    return array;
}

char **fill_quote(shell_t *s, char *line)
{
    char *before = NULL;
    char **prev = NULL;
    char *res = NULL;
    char *after = NULL;
    char **next = NULL;

    if (how_many(line, s->bticks->quote) < 2) {
        s->disp("Unmatched '%c'.\n", s->bticks->quote);
        return NULL;
    }
    before = strndup(line, posinstr(line, s->bticks->quote));
    prev = fill_str(strdup(before));
    res = strndup(line + posinstr(line, s->bticks->quote) + 1, posinstr
        (line + posinstr(line, s->bticks->quote) + 1, s->bticks->quote));
    after = strdup(line + strlen(before) + strlen(res) + 2);
    next = parse_str(s, strdup(after));
    free(before);
    free(after);
    s->bticks->l = strdup(line);
    return make_array(s, prev, res, next);
}

char **parse_str(shell_t *s, char *line)
{
    char **arr = NULL;

    if (s->bticks->keep_bticks && s->bticks->nb_bticks > 0) {
        for (int i = 0; i < s->bticks->nb_bticks; i++)
            free(s->bticks->keep_bticks[i]);
        s->bticks->keep_bticks = NULL;
        s->bticks->nb_bticks = 0;
    }
    if (how_many(line, '"') || how_many(line, '\'') || how_many(line, '`')) {
        if (how_many(line, '"') || how_many(line, '\''))
            s->bticks->quote = (posinstr(line, '"') < posinstr(line, '\'')
            ? '"' : '\'');
        else
            s->bticks->quote = '`';
        arr = fill_quote(s, line);
        if (!arr)
            s->base->status = 1;
        return arr;
    }
    return fill_str(line);
}

void option(shell_t *shell, char *string)
{
    if (is_empty(shell) == 1)
        return;
    add_to_history(&shell->history->hist, shell, string);
    shell->base->arr = parse_str(shell, strdup(string));
    if (!shell->base->arr)
        return;
    shell->base->arr = handle_glob(shell);
    if (!shell->base->arr)
        return;
    if (check_dollar(shell) == 1 || look_for_dir(shell, string) == 1)
        return;
    for (int index = 0; index < 11; index++)
        if (strcmp_my(shell->base->arr[0], flag_m[index]) == 1) {
            fm[index](shell, shell->base->env);
            return;
        }
    if (find_if_exclamation(shell, shell->base->env, shell->base->arr[0]) == 1)
        return;
    last_exec(shell, shell->base->env);
}
