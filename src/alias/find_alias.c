/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** find_alias
*/

#include "minishell.h"
#include <errno.h>
#include <ncurses.h>

int handle_alias_loop(shell_t *shell, int i)
{
    shell->alias->loop = false;
    if (search_in_list(shell->alias, shell->base->arr[i], my_str_cmp)) {
        shell->base->arr = alias_command_line(shell, i);
        if (shell->alias->loop) {
            print("Alias loop.\n");
            shell->base->status = 1;
            return 1;
        }
    }
    return 0;
}

alias_t *find_alias(shell_t *shell, int alias_i)
{
    alias_t *alias_found = NULL;
    alias_t *tmp = search_in_list(shell->alias, shell->base->arr[alias_i],
        my_str_cmp);
    alias_t *alias = tmp;

    while (alias != NULL) {
        alias_found = alias;
        alias = search_in_list(shell->alias, my_array_to_str(alias->command),
            my_str_cmp);
        if (!alias)
            return alias_found;
        if (my_str_cmp(my_array_to_str(alias->command),
            my_array_to_str(tmp->command))) {
            shell->alias->loop = true;
            break;
        }
        shell->alias->loop = false;
    }
    return alias;
}
