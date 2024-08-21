/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** env
*/


#include "minishell.h"

int arg_count(shell_t *shell)
{
    int counter = 0;

    for (int i = 0; shell->base->arr[i] != NULL; i++)
        counter++;
    if (counter > 3) {
        print("setenv: Too many arguments.\n");
        shell->base->status = 1;
        return 0;
    }
    return 1;
}

void two_arg(shell_t *shell, char **env)
{
    char **fun = 0;

    if (check_str(shell) == 1)
        return;
    if (!(my_al(shell->base->arr[1][0]))) {
        print("setenv: Variable name must begin with a letter.\n");
        shell->base->status = 1;
        return;
    }
    env_set(shell, env, fun);
    shell->base->status = 0;
    return;
}

int set_env(shell_t *shell, char **env)
{
    if (arg_count(shell) == 0)
        return 1;
    if (shell->base->arr[0] != NULL && shell->base->arr[1] == NULL) {
        cmd_env(shell, env);
        shell->base->status = 0;
        return 0;
    }
    if (shell->base->arr[1] != NULL && shell->base->arr[2] == NULL) {
        if (!(my_al(shell->base->arr[1][0]))) {
            print("setenv: Variable name must begin with a letter.\n");
            shell->base->status = 1;
            return 1;
        }
        if (check_str(shell) == 1)
            return 1;
        env_alone(shell, env);
        shell->base->status = 0;
    } else
        two_arg(shell, env);
    return 0;
}

void pwd_env(shell_t *shell, char **fun,
    char *temp_arg, struct list *head)
{
    char cwd[1024];

    if (str_my(fun[0], "PWD") == 1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            temp_arg = my_cat(fun[0], "=");
            temp_arg = my_realoc(temp_arg, cwd);
            temp_arg = my_cat(temp_arg, cwd);
            head->str = temp_arg;
            shell->base->status = 0;
            return;
        }
    }
}

void env_pwd(shell_t *shell)
{
    char **fun = 0;
    char *temp_arg = 0;
    struct list *head = shell->current;
    struct list *new_node = malloc(sizeof(struct list));

    if (new_node == NULL)
        exit(84);
    while (head != NULL) {
        fun = my_array(head->str);
        pwd_env(shell, fun, temp_arg, head);
        head = head->next;
    }
    return;
}
