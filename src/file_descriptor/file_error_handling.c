/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** error_handling
*/

#include "minishell.h"

bool is_found(shell_t *shell, int i)
{
    bool found = false;

    for (int j = 0; shell->pipe->arr[i][0][j] != '\0'; j++) {
        if (shell->pipe->arr[i][0][j] == '>') {
            found = true;
            break;
        }
    }
    return found;
}

int check_for_wrong_redir(shell_t *shell, int i, char *string)
{
    bool found = false;
    char **temp = NULL;

    found = is_found(shell, i);
    if (found == true) {
        temp = my_tok(temp, shell->pipe->arr[i][0], ">\n\0");
        if (i < (shell->pipe->nb_pipe - 1) && found == true) {
            print("Ambiguous output redirect.\n");
            shell->base->status = 1;
            exit(1);
        }
        if (found == true && temp[1] == NULL) {
            print("Missing name for redirect.\n");
            shell->base->status = 1;
            exit(1);
        }
    }
    if (base_pipes(shell, string) == 1)
        return 1;
    return 0;
}
