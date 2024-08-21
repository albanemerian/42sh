/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** init_and_find
*/

#include "minishell.h"

void handle_opperator(shell_t *shell, char *string, char **env, int *i)
{
    for (int j = 0; j < 1; j++) {
        if (shell->pipe->pipe == true)
            create_and_exec(shell, shell->queue->commands[*i][0]);
        else
            option(shell, shell->queue->commands[*i][j]);
        if (shell->base->status == 0 && strcmp_my
            (shell->queue->commands[*i][1], "||") == 1)
            *i += 1;
        if (shell->base->status != 0 && strcmp_my
            (shell->queue->commands[*i][1], "&&") == 1) {
            *i += 1;
            break;
        }
        if (shell->pipe->error == true)
            shell->base->status = 1;
        shell->pipe->error = false;
    }
}

int exec_pos(shell_t *shell, char *string, char **env, int nb_operrator)
{
    init_fd(shell, string, env);
    if (nb_operrator == 0 && shell->pipe->nb_pipe == 0) {
        option(shell, string);
        return 1;
    }
    if (shell->par->is_par == false &&
        shell->pipe->pipe == true && nb_operrator == 0)
        create_and_exec(shell, string);
    if (shell->par->is_par == true &&
        shell->pipe->pipe == true) {
        create_piip(shell, string);
        if (shell->pipe->error == true)
            shell->base->status = 1;
        return 1;
    }
    return 0;
}

void init_cmd_line(shell_t *shell, char *string, char **env)
{
    int nb_operrator = check_for_operators(shell, shell->base->env, string);

    if (look_for_parenthesis(shell, string) == 0)
        return;
    if (exec_pos(shell, string, env, nb_operrator) == 1)
        return;
    init_commands(shell, string, nb_operrator);
    for (int i = 0; shell->queue->commands[i] != NULL; i++) {
        shell->pipe->nb_pipe = 0;
        shell->pipe->pipe = false;
        init_fd(shell, shell->queue->commands[i][0], env);
        handle_opperator(shell, string, env, &i);
    }
}
