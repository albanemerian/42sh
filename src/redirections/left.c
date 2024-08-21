/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** left
*/

#include "minishell.h"
#include <fcntl.h>

int single_left_two(shell_t *shell, int input_fd, char *line, int *i)
{
    char *line2 = NULL;

    line2 = my_strdup(line + *i + 1);
    move_str(line2);
    input_fd = open(line2, O_RDONLY);
    if (input_fd == -1) {
        print("%s: No such file or directory.\n", line2);
        shell->base->status = 1;
        exit(1);
    }
    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("Error redirecting standard input");
        shell->base->status = 1;
        exit(1);
    }
    close(input_fd);
    return input_fd;
}

int single_left_redir(shell_t *shell, int *i, char *line)
{
    char *line1 = NULL;
    int input_fd = 0;
    pid_t pid = fork();

    if (pid == -1)
        exit(1);
    if (pid == 0) {
        *i -= 1;
        line1 = my_strndup(line, *i);
        input_fd = single_left_two(shell, input_fd, line, i);
        option(shell, line1);
        exit(shell->base->status);
    } else
        waitpid(pid, &shell->base->status, 0);
    return 1;
}

int look_for_left_chev(shell_t *shell, int *i, char *line)
{
    shell->base->status = 0;
    if (line[*i] == '<') {
        (*i)++;
        if (line[*i] != '<') {
            return single_left_redir(shell, i, line);
        }
        if (line[*i] == '<') {
            return double_left_redir(shell, i, line);
        }
    }
    return 0;
}
