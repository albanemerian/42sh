/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** execute
*/

#include "minishell.h"
#include <fcntl.h>
#include <string.h>

shell_t *read_42shrc(shell_t *s, char **env)
{
    FILE *file = fopen(".42shrc", "r");

    if (!file)
        return s;
    s->tty = true;
    s->disp = &printf;
    modif_special_variables(s);
    get_path(env, s);
    for (s->base->read = getline(&s->base->l, &s->base->len, file);
        s->base->read != -1; s->base->read = getline(&s->base->l,
        &s->base->len, file)) {
        if (!check_line(s, env))
            continue;
        my_precmd(s);
        init_cmd_line(s, strdup(s->base->l), env);
        s->variables = last_cmd(s);
        my_postcmd(s);
    }
    fclose(file);
    return s;
}

bool check_line(shell_t *s, char **env)
{
    if (s->base->l[s->base->read - 1] == 10)
        s->base->l[s->base->read - 1] = 0;
    if (s->base->l[0] == '#')
        return false;
    return true;
}

int shell_scripting(char *path, shell_t *s, char **env)
{
    FILE *file = fopen(path, "r");

    if (!file)
        exit(84);
    s->tty = true;
    s->disp = &printf;
    modif_special_variables(s);
    get_path(env, s);
    for (s->base->read = getline(&s->base->l, &s->base->len, file);
        s->base->read != -1; s->base->read = getline(&s->base->l,
        &s->base->len, file)) {
        if (!check_line(s, env))
            continue;
        my_precmd(s);
        init_cmd_line(s, strdup(s->base->l), env);
        s->variables = last_cmd(s);
        my_postcmd(s);
    }
    fclose(file);
    exit(s->base->status);
}
