/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** init_parenthese
*/

#include "minishell.h"
#include <string.h>

void fill_new_arr(shell_t *shell)
{
    char *delim[] = {";", "||", "&&", NULL};
    char *temp = my_strdup(shell->par->array[0]);
    int i = 0;
    tok_delim_t *sleep = tok_delims(temp, delim);

    shell->par->commands = calloc(shell->par->num_par + 1, sizeof(char **));
    while (sleep != NULL) {
        if (strcmp_my(sleep->token, "") != 1) {
            shell->par->commands[i] = calloc(2, sizeof(char *));
            shell->par->commands[i][0] = strdup(sleep->token);
            shell->par->commands[i][1] = strdup(sleep->delimiter);
            i++;
        }
        sleep = tok_delims(NULL, delim);
    }
    shell->par->commands[i] = NULL;
}

static char *rest_par(const char *str, int *count, int i, int *start)
{
    char *result = NULL;

    if (str[i] == '(') {
        if (*count == 0) {
            *start = i + 1;
        }
        (*count)++;
    }
    if (str[i] == ')') {
        (*count)--;
        if (*count == 0 && *start != -1) {
            result = (char *)malloc((i - *start + 1) * sizeof(char));
            strncpy(result, str + *start, i - *start);
            result[i - *start] = '\0';
        }
    }
    return result;
}

char *between_par(const char *str)
{
    int len = strlen(str);
    char *result = NULL;
    int count = 0;
    int start = -1;

    for (int i = 0; i < len; i++) {
        result = rest_par(str, &count, i, &start);
        if (result != NULL)
            break;
    }
    return result;
}

void fill_arr_par(shell_t *shell, char *string, int num_left)
{
    char *temp = my_strdup(string);
    char *res = between_par(temp);

    shell->par->array = calloc(2, sizeof(char *));
    shell->par->array[0] = strdup(res);
    shell->par->array[1] = NULL;
    shell->par->is_par = true;
    fill_new_arr(shell);
}

void check_if_parenthese(shell_t *shell, char *string)
{
    int len = strlen(string);

    if (string[0] == '(') {
        memmove(string, string + 1, len - 1);
        string[len - 1] = '\0';
    }
    if (string[strlen(string) - 1] == ')')
        string[strlen(string) - 1] = '\0';
}

int pos_parenthese(shell_t *shell, char *string, int num_left)
{
    int i = 0;
    int k = 0;

    shell->par->pos = malloc(sizeof(int) * num_left);
    for (int j = 0; string[j] != '\0'; j++) {
        if (string[j] == '|')
            i += 1;
        if (string[j] == '(') {
            shell->par->pos[k] = i;
            k += 1;
        }
    }
    if (i == 0)
        return 1;
    shell->par->array = calloc(num_left + 1, sizeof(char *));
    fill_arr_par(shell, string, num_left);
    return 0;
}
