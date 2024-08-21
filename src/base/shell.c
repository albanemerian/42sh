/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** shell
*/

#include <fcntl.h>
#include <ncurses.h>
#include "minishell.h"

void handle_ctrl_d(shell_t *shell)
{
    shell->pipe->nb_pipe = 0;
    if (shell->base->read == -1) {
        if (shell->base->status >= 256)
            shell->base->status /= 256;
        exit(shell->base->status);
    }
    shell->pipe->pipe = 0;
}

void tty_user_input(shell_t *shell, char **env)
{
    char *string = NULL;

    shell->base->read = getline(&shell->base->l, &shell->base->len, stdin);
    handle_ctrl_d(shell);
    my_precmd(shell);
    if (shell->base->l[shell->base->read - 1] == '\n')
        shell->base->l[shell->base->read - 1] = '\0';
    shell->par->is_par = false;
    string = my_strdup(shell->base->l);
    init_cmd_line(shell, string, env);
    shell->variables = last_cmd(shell);
}

void without_a_pip(shell_t *shell, char **env)
{
    shell->base->len = 0;
    if (shell->tty == true)
        tty_user_input(shell, env);
    else
        ncurses_user_input(shell, env);
    my_postcmd(shell);
    free_func(shell);
}

shell_t *malloc_struct(void)
{
    shell_t *shell = calloc(1, sizeof(shell_t));

    shell->base = calloc(1, sizeof(base_t));
    shell->pipe = calloc(1, sizeof(pipe_t));
    shell->history = calloc(1, sizeof(history_t));
    shell->queue = calloc(1, sizeof(queue_t));
    shell->par = calloc(1, sizeof(par_t));
    shell->ncurses = calloc(1, sizeof(ncurses_t));
    shell->redirections = calloc(1, sizeof(redirection_t));
    shell->bticks = calloc(1, sizeof(bticks_t));
    shell->alias = create_list();
    shell->variables = NULL;
    return shell;
}

int shell(int ac, char **av, char **env)
{
    shell_t *shell = malloc_struct();

    error_handling(shell, env, av, ac);
    fill_history_and_ncurses(shell);
    modif_special_variables(shell);
    while (1) {
        return_value(shell);
        if (isatty(STDIN_FILENO) == 1)
            prompt_moves(shell);
        without_a_pip(shell, env);
    }
    endwin();
    if (shell->base->status >= 256)
        shell->base->status /= 256;
    return shell->base->status;
}
        //display_prompt(shell);
