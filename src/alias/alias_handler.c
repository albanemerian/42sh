/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** init_alias
*/

#include "minishell.h"

static void display_alias(alias_t *alias, shell_t *shell)
{
    if (!alias)
        return;
    if (my_tablen(alias->command) > 1)
        print("%s\t(%s)\n", alias->name, my_array_to_str(alias->command));
    if (my_tablen(alias->command) == 1)
        print("%s\t%s\n", alias->name, alias->command[0]);
}

static void destroy_alias(alias_t *alias)
{
    free(alias->name);
    for (int i = 0; alias->command[i] != NULL; i++)
        free(alias->command[i]);
    free(alias->command);
    free(alias);
}

static bool compare_alias(alias_t *alias, char *name)
{
    return my_str_cmp(alias->name, name);
}

void split_command(char *command_str, alias_t *new_alias)
{
    char *command_copy = my_strdup(command_str);
    char *token;
    int count = 0;
    int i = 0;

    token = strtok(command_copy, " ");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " ");
    }
    new_alias->command = malloc((count + 1) * sizeof(char *));
    if (new_alias->command != NULL) {
        token = strtok(command_str, " ");
        while (token != NULL) {
            new_alias->command[i] = my_strdup(token);
            token = strtok(NULL, " ");
            i++;
        }
        new_alias->command[count] = NULL;
    }
}

alias_t *create_alias(shell_t *shell)
{
    alias_t *new_alias = calloc(1, sizeof(alias_t));
    char *command_str = my_array_to_str(shell->base->arr + 2);

    if (!new_alias) {
        print("Error: unsuccessful calloc\n");
        return NULL;
    }
    new_alias->name = my_strdup(shell->base->arr[1]);
    if (strchr(command_str, ' ') == NULL) {
        new_alias->command = my_array_dup(shell->base->arr + 2);
        new_alias->command[my_tablen(shell->base->arr + 2)] = NULL;
    } else
        split_command(command_str, new_alias);
    free(command_str);
    return new_alias;
}

int alias_handler(shell_t *shell, char **env)
{
    alias_t *alias = NULL;

    if (my_tablen(shell->base->arr) == 1)
        display_list(shell->alias, display_alias);
    if (my_tablen(shell->base->arr) == 2) {
        alias = search_in_list(shell->alias, shell->base->arr[1], my_str_cmp);
        if (alias)
            print("%s\n", my_array_to_str(alias->command));
    }
    if (my_tablen(shell->base->arr) > 2) {
        if (!replace_in_list(shell->alias, create_alias(shell),
            my_str_cmp))
            push_to_list_tail(shell->alias, create_alias(shell));
    }
    return (0);
}

int unalias_handler(shell_t *shell, char **env)
{
    if (my_tablen(shell->base->arr) == 1) {
        print("unalias: Too few arguments.\n");
        return (1);
    }
    for (int i = 1; shell->base->arr[i] != NULL; i++)
        delete_in_list(shell->alias, shell->base->arr[i], compare_alias,
        destroy_alias);
    return (0);
}
