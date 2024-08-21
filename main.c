/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** main
*/

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    return shell(ac, av, env);
}
