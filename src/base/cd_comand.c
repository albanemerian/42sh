/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** cd_comand
*/

#include "minishell.h"
#include <errno.h>

void cd_home(shell_t *shell, char *new)
{
    char *save = NULL;

    if (shell->base->home == NULL) {
        print("cd: No home directory.\n");
        shell->base->status = 1;
        return;
    }
    save = my_strdup(new);
    if (chdir(shell->base->home) == -1) {
        print("cd: Can't change to home directory.\n");
        shell->base->status = 1;
        return;
    }
    shell->base->oldpwd = save;
    env_pwd(shell);
    shell->base->status = 0;
    return;
}

int go_back_home(shell_t *shell, char *new)
{
    cd_home(shell, new);
    shell->variables = cwd(shell);
    my_cwdcmd(shell);
    return 0;
}

int change_pwd(shell_t *shell, char *new)
{
    if (perme_handler(shell, new) == 1)
        return 1;
    shell->variables = cwd(shell);
    my_cwdcmd(shell);
    return 0;
}

int cd_handler(shell_t *shell, char **env)
{
    char new[1024];

    getcwd(new, sizeof(new));
    if (my_tablen(shell->base->arr) == 1 ||
        strcmp_my(shell->base->arr[1], "~") == 1)
            return go_back_home(shell, new);
    if (shell->base->result == access(shell->base->arr[1], F_OK))
        return change_pwd(shell, new);
    if (handle(shell, new) != 0) {
        shell->base->status = 1;
        return 1;
    }
    shell->variables = cwd(shell);
    my_cwdcmd(shell);
    shell->base->status = 0;
    return 0;
}
