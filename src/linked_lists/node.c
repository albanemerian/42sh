/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** node
*/

#include "minishell.h"

node_t *create_node(void *data)
{
    node_t *node = calloc(1, sizeof(node_t));

    if (node == NULL)
        return NULL;
    node->data = data;
    node->next = NULL;
    return (node);
}

void destroy_node(node_t *node, void(*destroy_data)())
{
    if (destroy_data != NULL)
        destroy_data(node->data);
    free(node);
}

void add_node(list_t *list, node_t *new_node)
{
    node_t *current = NULL;

    if (list->first == NULL)
        list->first = new_node;
    else {
        current = list->first;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
}

void delete_node(list_t *list, node_t *prev, node_t *current,
    void(*destroy_data)())
{
    if (prev == NULL)
        list->first = current->next;
    else
        prev->next = current->next;
    destroy_node(current, destroy_data);
}
