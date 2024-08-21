/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_pipes
*/

#include "minishell.h"

static void restore_fd(shell_t *shell, pid_t pid)
{
    for (int i = 0; i < shell->pipe->nb_pipe; i++)
        waitpid(pid, &shell->base->status, 0);
    if (shell->pipe->pipe == true) {
        dup2(shell->pipe->input, STDIN_FILENO);
        dup2(shell->pipe->output, STDOUT_FILENO);
    }
    shell->pipe->input = 0;
    shell->pipe->output = 0;
}

static void child_process(int i, int fds[][2], int nb_args)
{
    if (i > 0) {
        close(fds[i - 1][1]);
        dup2(fds[i - 1][0], 0);
    }
    if (i < nb_args - 1) {
        close(fds[i][0]);
        dup2(fds[i][1], 1);
    }
}

static void parent_process(int i, int fds[][2], int nb_args)
{
    if (i > 0)
        close(fds[i - 1][0]);
    if (i < nb_args - 1)
        close(fds[i][1]);
    wait(NULL);
}

static void exec_func_from_par(shell_t *shell)
{
    for (int f = 0; shell->par->commands[f] != NULL; f++)
        option(shell, shell->par->commands[f][0]);
}

static int handle_parent(shell_t *shell, int i,
    int fd[shell->pipe->nb_pipe][2], pid_t pid)
{
    int t = 0;

    if (shell->par->is_par == true && shell->par->pos[t] == i) {
        pipe(fd[i]);
        pid = fork();
        if (pid == 0) {
            child_process(i, fd, shell->pipe->nb_pipe);
            exec_func_from_par(shell);
            exit(0);
        }
        parent_process(i, fd, shell->pipe->nb_pipe);
        t++;
        i += 1;
    }
    return i;
}

static int pipe_error(shell_t *shell, char *string)
{
    for (int j = 0; shell->pipe->arr[j] != NULL; j++) {
        if (check_for_wrong_redir(shell, j, string) == 1)
            return 1;
    }
    return 0;
}

int create_piip(shell_t *shell, char *string)
{
    int fd[shell->pipe->nb_pipe - 1][2];
    pid_t pid;

    if (pipe_error(shell, string) == 1)
        return 1;
    for (int i = 0; i < shell->pipe->nb_pipe; i++) {
        if (pipe(fd[i]) == -1)
            exit(84);
        i = handle_parent(shell, i, fd, pid);
        pid = fork();
        if (pid == 0) {
            child_process(i, fd, shell->pipe->nb_pipe);
            option(shell, shell->pipe->arr[i][0]);
            exit(0);
        }
        parent_process(i, fd, shell->pipe->nb_pipe);
    }
    restore_fd(shell, pid);
    return 0;
}
