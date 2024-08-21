/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** history_handler
*/

#include "minishell.h"
#include <time.h>

static void fill_history(shell_t *shell, struct hist *new_node, char *string)
{
    time_t current_time;
    struct tm *time_info;

    time(&current_time);
    time_info = localtime(&current_time);
    new_node->id = shell->history->cmd_num;
    new_node->str = strdup(string);
    new_node->hour = time_info->tm_hour;
    new_node->min = time_info->tm_min;
    new_node->next = NULL;
    return;
}

void add_to_history(struct hist **head, shell_t *shell, char *string)
{
    struct hist *new_node = NULL;
    struct hist *current = NULL;

    new_node = malloc(sizeof(struct hist));
    if (new_node == NULL)
        exit(0);
    fill_history(shell, new_node, string);
    if (*head == NULL) {
        *head = new_node;
    } else {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
        new_node->next = NULL;
    }
    shell->history->cmd_num++;
}

static int empty_historic(shell_t *shell, struct hist *head)
{
    struct hist *temp = NULL;

    if (shell->base->arr[1] != NULL && strcmp_my("-c",
        shell->base->arr[1]) == 1) {
        while (head != NULL) {
            temp = head;
            head = head->next;
            free(temp->str);
            free(temp);
        }
        shell->history->hist = NULL;
        return 1;
    }
    return 0;
}

int history_handler(shell_t *shell, char **envp)
{
    struct hist *head = shell->history->hist;

    if (empty_historic(shell, head) == 1) {
        return 1;
    }
    while (head != NULL) {
        shell->disp("\t%i   %02d:%02d   %s\n", head->id, head->hour,
            head->min, head->str);
        head = head->next;
    }
    return 1;
}
