/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** error_handling
*/

#include "minishell.h"

void error_handling(shell_t *shell, char **env, char **av, int ac)
{
    if (!shell || !env)
        exit(84);
    shell->history->cmd_num = 0;
    shell->base->status = 0;
    shell = read_42shrc(shell, env);
    if (ac == 2) {
        if (!strcmp(av[1], "-h") || !strcmp(av[1], "--help"))
            helper(ac);
        shell_scripting(av[1], shell, env);
    } else if (ac != 1)
        exit(84);
    get_path(env, shell);
}
