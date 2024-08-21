/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** path_handling
*/

#include "minishell.h"

void get_env(shell_t *shell)
{
    struct list *act = NULL;
    struct list *last = NULL;

    for (int i = 0; shell->base->env[i] != NULL; i++) {
        act = malloc(sizeof(struct list));
        if (act == NULL)
            exit(84);
        act->str = shell->base->env[i];
        act->next = NULL;
        if (shell->current == NULL)
            shell->current = act;
        if (last != NULL) {
            last->next = act;
        }
        last = act;
        act->next = NULL;
    }
}

void get_home(shell_t *shell)
{
    for (int i = 0; shell->base->env[i] != NULL; i ++) {
        if (str_my(shell->base->env[i], "HOME=") == 1) {
            shell->base->home = my_strdup(&shell->base->env[i][5]);
            break;
        }
    }
    for (int i = 0; shell->base->env[i] != NULL; i ++) {
        if (str_my(shell->base->env[i], "PATH=") == 1) {
            shell->base->path = tok_word_array(&shell->base->env[i][5], ":");
            break;
        }
    }
    if (shell->base->path == NULL) {
        shell->base->path = malloc(sizeof(char *) * (3 + 1));
        shell->base->path[0] = my_strdup("/bin/");
        shell->base->path[1] = my_strdup("/usr/bin");
        shell->base->path[2] = NULL;
    }
    shell->base->oldpwd = NULL;
}

int env_length(char **env)
{
    int length = 0;

    while (env[length] != NULL) {
        length++;
    }
    return length;
}

void get_path(char **env, shell_t *shell)
{
    int len = env_length(env);

    shell->base->env = malloc(sizeof(char *) * (len + 1));
    shell->base->path = NULL;
    shell->base->env_len = len;
    if (shell->base->env == NULL) {
        exit(84);
    }
    for (int i = 0; env[i] != NULL; i++) {
        shell->base->env[i] = malloc(sizeof(char) * (my_strlen(env[i]) + 1));
        shell->base->env[i] = my_strdup(env[i]);
        if (shell->base->env[i] == NULL) {
            exit(84);
        }
    }
    shell->base->env[env_length(env)] = NULL;
    get_home(shell);
    get_env(shell);
}
