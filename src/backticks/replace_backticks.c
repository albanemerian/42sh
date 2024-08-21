/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** replace_backticks
*/

#include "minishell.h"

bool is_backtick_duplicate(char *btick_cmd, char **cmd, int num_bticks)
{
    for (int j = 0; j < num_bticks; j++)
        if (strcmp(btick_cmd, cmd[j]) == 0)
            return true;
    return false;
}

void add_backtick_command(char ***cmd, char *backtick_cmd, int *num_cmds)
{
    *cmd = realloc(*cmd, (*num_cmds + 1) * sizeof(char *));
    (*cmd)[*num_cmds] = strdup(backtick_cmd);
    (*num_cmds)++;
}

void update_array(char **array, char *btick_res, char **cmd, int num_cmds)
{
    if (!btick_res)
        return;
    for (int j = 0; array[j]; j++)
        if (strcmp(array[j], cmd[num_cmds - 1]) == 0) {
            free(array[j]);
            array[j] = btick_res;
            break;
        }
}

void replace_backticks(shell_t *s, char **array)
{
    char **cmd = calloc(1, sizeof(char *));
    int num_cmds = 0;

    if (!s->bticks->keep_bticks)
        return;
    for (int i = 0; s->bticks->keep_bticks[i]; i++) {
        if (!is_backtick_duplicate(s->bticks->keep_bticks[i], cmd, num_cmds)) {
            add_backtick_command(&cmd, s->bticks->keep_bticks[i], &num_cmds);
            update_array(array, execute_backtick_command
            (s->bticks->keep_bticks[i]), cmd, num_cmds);
        }
    }
    for (int i = 0; i < num_cmds; i++)
        free(cmd[i]);
    free(cmd);
    for (int i = 0; array[i]; i++)
        clean_str(array[i]);
}
