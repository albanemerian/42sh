/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** cwd
*/

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include <ncurses.h>

set_list_t *cwd(shell_t *shell)
{
    char *cwd = NULL;
    char pwd[1024];

    getcwd(pwd, sizeof(pwd));
    cwd = calloc(1, sizeof(char) * (strlen(pwd) + 5));
    cwd = strcpy(cwd, "cwd=");
    cwd = strcat(cwd, pwd);
    cwd[strlen(pwd) + 4] = '\0';
    return set_variable(cwd, &shell->variables);
}
