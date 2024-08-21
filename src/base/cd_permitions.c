/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** cd_permitions
*/

#include "minishell.h"


int handle(shell_t *shell, char *new)
{
    if (strcmp_my(shell->base->arr[1], "-") == 1 &&
        shell->base->arr[1][1] == '\0') {
        if (shell->base->oldpwd != NULL) {
            chdir(shell->base->oldpwd);
            shell->base->oldpwd = my_strdup(new);
            env_pwd(shell);
            return 0;
        } else {
            print(": No such file or directory.\n");
            return 1;
        }
    } else {
        print("%s: No such file or directory.\n", shell->base->arr[1]);
        return 1;
    }
    return 0;
}

int perme_handler(shell_t *shell, char *new)
{
    struct stat path_stat;

    stat(shell->base->arr[1], &path_stat);
    if (access(shell->base->arr[1], R_OK) == -1) {
        print("%s/: Permission denied.\n", shell->base->arr[1]);
        shell->base->status = 1;
        return 1;
    }
    if (S_ISDIR(path_stat.st_mode) == 1) {
        shell->base->oldpwd = my_strdup(new);
        chdir(shell->base->arr[1]);
        env_pwd(shell);
        shell->base->status = 0;
        return 0;
    } else {
        print("%s: Not a directory.\n", shell->base->arr[1]);
        shell->base->status = 1;
        return 1;
    }
}
