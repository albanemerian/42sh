/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** history
*/


#ifndef HISTORY_H_
    #define HISTORY_H_

// histroy -> handle_exlamations.c
void print_linked_list(struct hist *head);
struct hist *reverse_linked_list(struct hist *head);
void handle_exclamation(shell_t *shell, char **envp, char *string);
int find_if_exclamation(shell_t *shell, char **envp, char *string);

// histroy -> history_handler.c
void add_to_history(struct hist **head, shell_t *shell, char *string);
int history_handler(shell_t *shell, char **envp);

#endif /* !HISTORY_H_ */
