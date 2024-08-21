/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_exlamations
*/

#include "minishell.h"

void print_linked_list(struct hist *head)
{
    struct hist *curr = head;

    while (curr != NULL) {
        print("%d %d:%d %s\n", curr->id, curr->hour, curr->min,
            curr->str);
        curr = curr->next;
    }
}

struct hist *reverse_linked_list(struct hist *head)
{
    struct hist *curr = head;
    struct hist *prev = NULL;
    struct hist *next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void handle_exclamation(shell_t *shell, char **envp, char *string)
{
    int i = 0;
    char **array = NULL;

    shell->history->hist = reverse_linked_list(shell->history->hist);
    while (shell->history->hist != NULL) {
        array = string_to_word_array(shell->history->hist->str);
        if (i > 0 && my_strncmp(array[0], &string[1],
            my_strlen(string) - 1) == 0) {
            print("%s\n", shell->history->hist->str);
            option(shell, shell->history->hist->str);
            break;
        }
        shell->history->hist = shell->history->hist->next;
        i++;
    }
    shell->history->hist = reverse_linked_list(shell->history->hist);
    print("%s: Event not found.\n", &string[1]);
}

int find_if_exclamation(shell_t *shell, char **envp, char *string)
{
    if (string[0] == '!' && string[1] != '\0') {
        handle_exclamation(shell, envp, string);
        return (1);
    }
    return (0);
}
