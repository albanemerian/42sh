/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell1-albane.merian
** File description:
** set_env_alone
*/

#include "minishell.h"

void alone_env(shell_t *shell, struct list *head, struct list *new_node)
{
    char *temp_arg = my_strdup(shell->base->arr[1]);
    char *env_temp = my_cat(temp_arg, "=");

    new_node->str = env_temp;
    new_node->next = NULL;
    if (shell->current == NULL) {
        shell->current = new_node;
    } else {
        head = shell->current;
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = new_node;
        free(temp_arg);
    }
}

int env_alone(shell_t *shell, char **env)
{
    struct list *head = shell->current;
    struct list *new_node = malloc(sizeof(struct list));

    if (new_node == NULL)
        exit(84);
    while (head != NULL) {
        shell->base->fun = my_str_to_word_array(head->str);
        if (strcmp_my(shell->base->fun[0], shell->base->arr[1]) == 1) {
            shell->base->temp = my_strdup(shell->base->arr[1]);
            shell->base->arg = my_cat(shell->base->temp, "=");
            head->str = shell->base->arg;
            free(shell->base->temp);
            free_tab(shell->base->fun);
            return 0;
        }
        head = head->next;
    }
    alone_env(shell, head, new_node);
    return 0;
}
