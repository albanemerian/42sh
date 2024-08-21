/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** my_list_len
*/

#include "minishell.h"

int linked_list_len(list_t *list)
{
    int len = 0;
    node_t *node = NULL;

    if (list->first == NULL)
        return 0;
    node = list->first;
    while (node != NULL) {
        len++;
        node = node->next;
    }
    return len;
}
