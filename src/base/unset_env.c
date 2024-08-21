/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell1-albane.merian
** File description:
** unset_env
*/

#include "minishell.h"


void unset_envv(shell_t *shell, int len, int i)
{
    struct list *head = shell->current;
    struct list *previous = NULL;

    while (head != NULL) {
        len = my_strlen(head->str);
        if (my_strncmp(head->str, shell->base->arr[i], len) == 0) {
            previous->next = head->next;
            return;
        } else {
            previous = head;
            head = head->next;
        }
    }
    return;
}

int unset_env(shell_t *shell, char **env)
{
    int len = 0;

    if (shell->base->arr[1] == NULL) {
        print("unsetenv: Too few arguments.\n");
        shell->base->status = 1;
        return 0;
    }
    for (int i = 0; shell->base->arr[i] != NULL; i++)
        unset_envv(shell, len, i);
    return 0;
}
