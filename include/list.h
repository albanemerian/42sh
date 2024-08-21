/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** list
*/



#ifndef LIST_H_
    #define LIST_H_

// linked_lists -> list.c
void push_to_list_tail(list_t *list, void *data);
void display_list(list_t *list, void(*display_data)());
bool delete_in_list(list_t *list, void const *ref, bool(*compare_data)(),
    void(*destroy_data)());
void display_list(list_t *list, void(*display_data)());
int linked_list_len(list_t *list);
alias_t *search_in_list(list_t *list, char *ref, bool(*compare_data)());
bool replace_in_list(list_t *alias_list, alias_t *alias,
    bool(*compare_data)());

// linked_lists -> manage_list.c
list_t *create_list(void);
void destroy_list(list_t *list, void(*destroy_data)());

// linked_lists -> my_list_len.c
int linked_list_len(list_t *list);

// linked_lists -> node.c
node_t *create_node(void *data);
void destroy_node(node_t *node, void(*destroy_data)());
void add_node(list_t *list, node_t *new_node);
void delete_node(list_t *list, node_t *prev, node_t *current,
    void(*destroy_data)());

#endif /* !LIST_H_ */
