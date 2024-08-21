/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** find_error
*/


#include <string.h>
#include "minishell.h"
#include <fcntl.h>

int diff_built(char *str)
{
    print("%s\n", str);
    if (strcmp_my(str, "env") != 1 && strcmp_my(str, "setenv") != 1 &&
        strcmp_my(str, "cd") != 1 && strcmp_my(str, "exit") != 1)
        return 0;
    return 1;
}

int null_command(shell_t *shell, int j)
{
    if (j <= shell->pipe->nb_pipe - 1) {
        shell->disp("Invalid null command.\n");
        shell->base->status = 1;
        return 1;
    }
    return 0;
}

int find_error_cmd(shell_t *shell, int j)
{
    char *path = strdup("/usr/bin/");
    char *dup = NULL;
    char **temp = NULL;

    if (null_command(shell, j) == 1)
        return 1;
    j -= 1;
    dup = strdup(shell->pipe->arr[j][0]);
    j += 1;
    temp = string_to_word_array(dup);
    check_if_parenthese(shell, temp[0]);
    if (access(temp[0], X_OK) == -1 && diff_built(temp[0]) == 0 &&
        strcmp_my("./42sh", temp[0]) != 1 &&
        access(my_cat(path, temp[0]), X_OK) == -1) {
        print("%s: Command not found.\n", temp[0]);
        shell->base->status = 1;
        return 1;
    }
    return 0;
}

static int check_full_path(shell_t *shell, char *string)
{
    char *temp = my_strdup(string);
    char **dup = string_to_word_array(temp);
    char *path = NULL;
    char *str = NULL;

    if (access(dup[0], X_OK) == 0)
        return 1;
    for (int i = 0; shell->base->path[i] != NULL; i++) {
        path = my_strdup(shell->base->path[i]);
        str = my_cat(path, "/");
        str = my_cat(str, dup[0]);
        if (access(str, X_OK) == 0)
            return 1;
    }
    return 0;
}

void find_error(shell_t *shell)
{
    shell->pipe->error = false;
    for (int i = 0; shell->pipe->arr[i] != NULL; i++) {
            check_if_parenthese(shell, shell->pipe->arr[i][0]);
        if (check_full_path(shell, shell->pipe->arr[i][0]) == 0 &&
            diff_built(shell->pipe->arr[i][0]) == 0) {
            shell->pipe->error = true;
            print("%s: Command not found.\n", shell->pipe->arr[i][0]);
        }
    }
}

int base_pipes(shell_t *shell, char *string)
{
    int j = 0;

    for (; shell->pipe->arr[j] != NULL; j++) {
        if (check_for_builtin(shell, shell->base->env, j) == 1)
            return 1;
    }
    if (find_error_cmd(shell, j) == 1)
        return 1;
    find_error(shell);
    return 0;
}
