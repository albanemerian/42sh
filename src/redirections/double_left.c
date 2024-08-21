/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** double_left
*/

#include "minishell.h"

void get_lines(shell_t *shell, char *line1, char *line2)
{
    char *l = NULL;
    size_t len = 0;
    ssize_t read = 0;

    while (1) {
        print("? ");
        read = getline(&l, &len, stdin);
        if (l[read - 1] == '\n')
            l[read - 1] = '\0';
        if (read == -1 || strcmp_my(l, line2) == 1) {
            option(shell, line1);
            exit(0);
        }
    }
}

int double_left_redir(shell_t *shell, int *i, char *line)
{
    char *line1 = NULL;
    char *line2 = NULL;
    pid_t pid = fork();

    *i -= 2;
    line1 = my_strndup(line, *i);
    *i += 4;
    line2 = my_strdup(line + *i);
    if (pid == -1)
        exit(1);
    if (pid == 0)
        get_lines(shell, line1, line2);
    else
        waitpid(pid, &shell->base->status, 0);
    return 1;
}

int double_redir(shell_t *shell, int *i, char *line)
{
    char *line1 = NULL;
    char *line2 = NULL;

    (*i) -= 2;
    line1 = my_strndup(line, *i);
    (*i) += 3;
    line2 = my_strdup(line + *i);
    if (line2 == NULL) {
        print("Missing name for redirect.\n");
        shell->redirections->status = 2;
        shell->base->status = 1;
        exit(1);
    }
    shell->redirections->is_double = 1;
    execute_simp_dir(shell, line1, line2);
    return 1;
}
