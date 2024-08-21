/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** list
*/

#include "minishell.h"

void push_to_list_tail(list_t *list, void *data)
{
    node_t *new_node = create_node(data);

    if (new_node == NULL)
        return;
    add_node(list, new_node);
}

void display_list(list_t *list, void(*display_data)())
{
    node_t *node = NULL;

    if (display_data == NULL)
        return;
    node = list->first;
    while (node != NULL) {
        display_data(node->data);
        node = node->next;
    }
}

bool delete_in_list(list_t *list, void const *ref, bool(*compare_data)(),
    void(*destroy_data)())
{
    node_t *current = NULL;
    node_t *prev = NULL;

    if (list == NULL || compare_data == NULL)
        return false;
    current = list->first;
    while (current != NULL) {
        if (compare_data(current->data, ref)) {
            delete_node(list, prev, current, destroy_data);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

alias_t *search_in_list(list_t *list, char *ref, bool(*compare_data)())
{
    node_t *current = NULL;
    alias_t *al = NULL;

    if (list == NULL || compare_data == NULL)
        return NULL;
    current = list->first;
    while (current != NULL) {
        al = current->data;
        if (compare_data(al->name, ref))
            return al;
        current = current->next;
    }
    return NULL;
}

bool replace_in_list(list_t *alias_list, alias_t *alias,
    bool(*compare_data)())
{
    node_t *current = NULL;
    alias_t *al = NULL;

    if (alias_list == NULL || compare_data == NULL)
        return false;
    current = alias_list->first;
    while (current != NULL) {
        al = current->data;
        if (compare_data(al->name, alias->name)) {
            al = alias;
            current->data = al;
            return true;
        }
        current = current->next;
    }
    return false;
}
