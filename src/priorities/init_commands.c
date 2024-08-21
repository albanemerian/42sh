/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** init_commands
*/

#include "minishell.h"

static void check_arr(shell_t *shell)
{
    for (int i = 0; shell->queue->commands[i] != NULL; i++) {
        if ((strcmp_my(shell->queue->commands[i][1], "&&") == 1 ||
            strcmp_my(shell->queue->commands[i][1], "||") == 1) &&
            shell->queue->commands[i + 1] == NULL) {
            shell->disp("Invalid null command.\n");
            shell->base->status = 1;
            exit(1);
        }
    }
}

void init_commands(shell_t *shell, char *string, int nb_operator)
{
    char *delim[] = {"&&", "||", ";", NULL};
    char *temp = my_strdup(string);
    int i = 0;
    tok_delim_t *token = NULL;

    shell->queue->commands = calloc(nb_operator + 1, sizeof(char **));
    token = tok_delims(temp, delim);
    while (token != NULL) {
        if (strcmp_my(token->token, "") != 1) {
            shell->queue->commands[i] = calloc(2, sizeof(char *));
            move_str_end(token->token);
            shell->queue->commands[i][0] = strdup(token->token);
            shell->queue->commands[i][1] = strdup(token->delimiter);
            i++;
        }
        token = tok_delims(NULL, delim);
    }
    shell->queue->commands[i] = NULL;
    check_arr(shell);
}
