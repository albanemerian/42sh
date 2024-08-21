/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** glob
*/

#include "../include/minishell.h"

char **no_matching(shell_t *shell)
{
    print("%s: No match.\n", shell->base->arr[0]);
    shell->base->status = 1;
    return NULL;
}

int perform_glob(char *pattern, char ***exp_arg, int *num_exp)
{
    glob_t globb;
    int rv = -1;

    rv = glob(pattern, 0, NULL, &globb);
    if (rv == 0) {
        for (int j = 0; j < globb.gl_pathc; j++) {
            *exp_arg = realloc(*exp_arg, (*num_exp + 2) * sizeof(char *));
            (*exp_arg)[(*num_exp)] = strdup(globb.gl_pathv[j]);
            (*num_exp)++;
        }
    }
    (*exp_arg)[(*num_exp)] = NULL;
    if (rv == GLOB_NOMATCH)
        return 1;
    return 0;
}

char **handle_glob(shell_t *shell)
{
    char **exp_arg = NULL;
    int num_exp = 0;
    int rv = -1;

    for (int i = 0; shell->base->arr[i] != NULL; i++) {
        if (strchr(shell->base->arr[i], '*') != NULL ||
            strchr(shell->base->arr[i], '?') != NULL) {
            rv = perform_glob(shell->base->arr[i], &exp_arg, &num_exp);
            continue;
        }
        exp_arg = realloc(exp_arg, (num_exp + 2) * sizeof(char *));
        exp_arg[num_exp] = strdup(shell->base->arr[i]);
        num_exp++;
    }
    if (rv == 1)
        return no_matching(shell);
    exp_arg[num_exp] = NULL;
    return exp_arg;
}
