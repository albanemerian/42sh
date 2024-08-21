/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_linked_lists
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// list.c
Test(list, push_to_list_tail)
{
    list_t *list = create_list();
    char *data = strdup("test");

    push_to_list_tail(list, data);
    cr_assert_str_eq(list->first->data, "test");
}

// manage_list.c
Test(manage_list, create_list)
{
    list_t *list = create_list();

    cr_assert_not_null(list);
    cr_assert_null(list->first);
}

Test(manage_list, destroy_list)
{
    list_t *list = create_list();
    char *data = strdup("test");

    push_to_list_tail(list, data);
    destroy_list(list, free);
}

Test(manage_list, destroy_list_null)
{
    list_t *list = NULL;

    destroy_list(list, free);
}

// my_list_len.c
Test(my_list_len, linked_list_len)
{
    list_t *list = create_list();
    char *data = strdup("test");

    push_to_list_tail(list, data);
    cr_assert_eq(linked_list_len(list), 1);
}

Test(my_list_len, linked_list_len_null)
{
    list_t *list = create_list();
    list->first = NULL;

    cr_assert_eq(linked_list_len(list), 0);
}

// node.c
Test(node, create_node)
{
    char *data = strdup("test");
    node_t *node = create_node(data);

    cr_assert_str_eq(node->data, "test");
}

Test(node, destroy_node)
{
    char *data = strdup("test");
    node_t *node = create_node(data);

    destroy_node(node, free);
}

Test(node, add_node)
{
    list_t *list = create_list();
    char *data_1 = strdup("test");
    node_t *node_1 = create_node(data_1);

    add_node(list, node_1);
    cr_assert_str_eq(list->first->data, "test");

    char *data_2 = strdup("test_2");
    node_t *node_2 = create_node(data_2);
    add_node(list, node_2);
    cr_assert_str_eq(list->first->next->data, "test_2");

    char *data_3 = strdup("test_3");
    node_t *node_3 = create_node(data_3);
    add_node(list, node_3);
    cr_assert_str_eq(list->first->next->next->data, "test_3");
}

Test(node, delete_node)
{
    list_t *list = create_list();
    char *data_1 = strdup("test");
    node_t *node_1 = create_node(data_1);

    add_node(list, node_1);
    char *data_2 = strdup("test_2");
    node_t *node_2 = create_node(data_2);
    add_node(list, node_2);
    char *data_3 = strdup("test_3");
    node_t *node_3 = create_node(data_3);
    add_node(list, node_3);

    delete_node(list, NULL, list->first, free);
    cr_assert_str_eq(list->first->data, "test_2");
    delete_node(list, list->first, list->first->next, free);
    cr_assert_str_eq(list->first->data, "test_2");
    delete_node(list, list->first, list->first, free);
}
