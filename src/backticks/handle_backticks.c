/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_backticks
*/

#include "minishell.h"

void handle_backticks(shell_t *s, char **array, char *result)
{
    if (result[0] != '\0' && (how_many(result, '`') >= 2 ||
        s->bticks->quote == '`')) {
        clean_str(result);
        if (!s->bticks->keep_bticks)
            s->bticks->keep_bticks = calloc(1, sizeof(char *));
        else
            s->bticks->keep_bticks = realloc(s->bticks->keep_bticks,
                (s->bticks->nb_bticks + 1) * sizeof(char *));
        s->bticks->keep_bticks[s->bticks->nb_bticks] = strdup(result);
        s->bticks->nb_bticks++;
    }
    replace_backticks(s, array);
}
