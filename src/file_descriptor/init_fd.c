/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** init_fd
*/

#include "minishell.h"


void handle_pipes(shell_t *shell, char *string, char **env)
{
    char *delim = "|";
    char *temp = strdup(string);
    int i = 0;
    tok_delim_t *token = NULL;

    shell->pipe->arr = calloc(shell->pipe->nb_pipe + 1, sizeof(char **));
    token = strtok_custom(temp, delim);
    while (token != NULL) {
        if (strcmp_my(token->token, "") != 1) {
            shell->pipe->arr[i] = calloc(2, sizeof(char *));
            move_str_end(token->token);
            shell->pipe->arr[i][0] = strdup(token->token);
            shell->pipe->arr[i][1] = strdup(token->delimiter);
            i++;
        }
        token = strtok_custom(NULL, delim);
    }
    shell->pipe->arr[i] = NULL;
}

void init_fd(shell_t *shell, char *string, char **env)
{
    char *temp = strdup(string);

    shell->pipe->pipe = false;
    shell->pipe->nb_pipe = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '|' && string[i + 1] != '|') {
            shell->pipe->pipe = true;
            shell->pipe->nb_pipe += 1;
        }
    }
    if (shell->pipe->pipe == true) {
        shell->pipe->nb_pipe += 1;
        shell->pipe->input = dup(STDIN_FILENO);
        shell->pipe->output = dup(STDOUT_FILENO);
        handle_pipes(shell, temp, env);
    }
}
