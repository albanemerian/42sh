/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_pipes
*/

#include "minishell.h"

int check_for_builtin(shell_t *shell, char **env, int i)
{
    if (my_strncmp("cd", shell->pipe->arr[i][0], 2) == 0 &&
        i == shell->pipe->nb_pipe - 1) {
        shell->base->arr = string_to_word_array(shell->pipe->arr[i][0]);
        cd_handler(shell, env);
        return 1;
    }
    if (my_strncmp("exit", shell->pipe->arr[i][0], 4) == 0 &&
        i == shell->pipe->nb_pipe - 1) {
        shell->base->arr = string_to_word_array(shell->pipe->arr[i][0]);
        exit_func(shell, env);
    }
    return 0;
}

static int pipe_error(shell_t *shell, char *string)
{
    for (int j = 0; shell->pipe->arr[j] != NULL; j++) {
        if (check_for_wrong_redir(shell, j, string) == 1)
            return 1;
    }
    return 0;
}

void manage_fd(int fd, int fd_source)
{
    if (dup2(fd, fd_source) == -1)
        exit(1);
    close(fd);
}

void mr_pipe(shell_t *shell, char **arr, int fd[2], int i)
{
    pid_t pid = 0;

    if (i)
        manage_fd(fd[0], STDIN_FILENO);
    if (arr[i + 1])
        if (pipe(fd) == -1)
            exit(1);
    pid = fork();
    if (!pid) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        option(shell, my_strdup(arr[i]));
        exit(shell->base->status);
    }
    close(fd[1]);
    return;
}

int create_and_exec(shell_t *shell, char *string)
{
    char **arr = parse(my_strdup(string), "|");
    pid_t pid[2] = {0};
    int fd[2] = {0};

    if (pipe_error(shell, string) == 1)
        return 1;
    pid[0] = fork();
    if (!pid[0]) {
        if (pipe(fd) == -1)
            exit(1);
        for (int i = 0; arr[i] != NULL; i++) {
            mr_pipe(shell, arr, fd, i);
        }
        close(fd[0]);
        for (int i = 0; arr[i + 1] != NULL; i++)
            wait(NULL);
        exit(shell->base->status);
    }
    waitpid(pid[0], &pid[1], 0);
    return 0;
}

    // for (int i = 0; i < shell->pipe->nb_pipe; i++) {
    //     if (pipe(fd[i]) == -1)
    //         exit(84);
    //     i = handle_parent(shell, i, fd, pid);
    //     pid = fork();
    //     if (pid == 0) {
    //         child_process(i, fd, shell->pipe->nb_pipe);
    //         option(shell, shell->pipe->arr[i][0]);
    //         exit(0);
    //     }
    //     parent_process(i, fd, shell->pipe->nb_pipe);
    // }
    // restore_fd(shell, pid);
