/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** init_list
*/

#include "minishell.h"

int find_posibilities(shell_t *shell, char *string, int nb_operrator)
{
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ';') {
            shell->queue->semicolon = true;
            nb_operrator += 1;
        }
        if (string[i] == '&' && string[i + 1] == '&') {
            shell->queue->and_op = true;
            nb_operrator += 1;
        }
        if (string[i] == '|' && string[i + 1] == '|') {
            shell->queue->pipe = true;
            nb_operrator += 1;
        }
    }
    return nb_operrator;
}

int check_for_operators(shell_t *shell, char **envp, char *string)
{
    int nb_operrator = 0;
    char *temp = my_strdup(string);

    shell->queue->semicolon = false;
    shell->queue->and_op = false;
    shell->queue->pipe = false;
    nb_operrator = find_posibilities(shell, temp, nb_operrator);
    if (shell->queue->semicolon == true || shell->queue->and_op == true ||
        shell->queue->pipe == true)
        return nb_operrator;
    return 0;
}
