/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** ncurses handler
*/

#include <stdlib.h>
#include "minishell.h"
#include <ncurses.h>

static char **parse_setvar(char *var)
{
    char *cpy = my_strdup(var);
    char **result = calloc(1, sizeof(char *) * 2);
    char *t = strtok(cpy, "=\n");

    for (int i = 0; t != NULL && i < 2; i++) {
        result[i] = my_strdup(t);
        t = strtok(NULL, "\n");
    }
    free(cpy);
    return result;
}

int check_existant_var(set_list_t *begin, char *cmp)
{
    set_list_t *list = begin;

    while (list != NULL) {
        if (strcmp_my(cmp, list->var) == 1)
            return 1;
        list = list->next;
    }
    return 0;
}

set_list_t *add_variables(char **var, set_list_t **begin)
{
    set_list_t *new_node = malloc(sizeof(set_list_t));

    new_node->var = my_strdup(var[0]);
    if (var[1] == NULL)
        new_node->content = NULL;
    else
        new_node->content = my_strdup(var[1]);
    new_node->next = *begin;
    return new_node;
}

set_list_t *upt_variables(char **var, set_list_t **begin)
{
    set_list_t *save = *begin;
    set_list_t **list = begin;

    while (*list != NULL) {
        if (strcmp_my(var[0], (*list)->var) == 1) {
            (*list)->content = var[1];
            *list = save;
            return *list;
        }
        *list = (*list)->next;
    }
    *list = save;
    return *list;
}

set_list_t *set_variable(char *var, set_list_t **begin)
{
    char **new_var = parse_setvar(var);

    if (check_existant_var(*begin, new_var[0]) == 0)
        return add_variables(new_var, begin);
    if (check_existant_var(*begin, new_var[0]) == 1 && new_var[1] != NULL)
        return upt_variables(new_var, begin);
    return (*begin);
}
