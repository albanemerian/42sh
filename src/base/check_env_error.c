/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** check_env_error
*/
#include "minishell.h"

int check_str(shell_t *shell)
{
    char *str = my_strdup(shell->base->arr[1]);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            print("setenv: Variable name must contain ");
            print("alphanumeric characters.\n");
            shell->base->status = 1;
            return 1;
        }
    }
    return 0;
}

void free_tab(char **fun)
{
    for (int i = 0; fun[i] != NULL; i++)
        free(fun[i]);
    free(fun);
}

void envv_sett(shell_t *shell, struct list *head,
    struct list *new_node)
{
    char *env_temp = 0;

    env_temp = my_cat(shell->base->arr[1], "=");
    new_node->str = env_temp;
    new_node->str = my_cat(new_node->str, shell->base->arr[2]);
    new_node->next = NULL;
    if (shell->current == NULL) {
        shell->current = new_node;
    } else {
        head = shell->current;
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = new_node;
    }
}

void fill_env(shell_t *shell, struct list *head,
    char **fun, struct list *new_node)
{
    char *temp_arg = NULL;
    char *temp_arg2 = NULL;

    while (head != NULL) {
        fun = my_str_to_word_array(head->str);
        if (strcmp_my(fun[0], shell->base->arr[1]) == 1) {
            temp_arg = my_cat(fun[0], "=");
            temp_arg2 = my_strdup(shell->base->arr[2]);
            temp_arg = my_cat(temp_arg, temp_arg2);
            head->str = temp_arg;
            free(temp_arg2);
            free_tab(fun);
            return;
        }
        head = head->next;
    }
    envv_sett(shell, head, new_node);
}

void env_set(shell_t *shell, char **env, char **fun)
{
    struct list *head = shell->current;
    struct list *new_node = malloc(sizeof(struct list));

    if (new_node == NULL)
        exit(84);
    fill_env(shell, head, fun, new_node);
    return;
}
