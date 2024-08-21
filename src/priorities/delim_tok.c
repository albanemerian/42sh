/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** delim_tok
*/

#include "minishell.h"

tok_delim_t *fill_token(tok_delim_t *result, char *delim_found, char *ret)
{
    result->token = ret;
    if (delim_found != NULL) {
        result->delimiter = calloc(2, sizeof(char));
        result->delimiter[0] = *delim_found;
        result->delimiter[1] = '\0';
    } else
        result->delimiter = NULL;
    return result;
}

char *find_delimiter(char *p, char *delimiters)
{
    for (; *p != '\0'; p++) {
        if (strchr(delimiters, *p) != NULL) {
            return p;
        }
    }
    return NULL;
}

void update_source(char **src, char *p, tok_delim_t *result)
{
    if (p == NULL || *p == '\0') {
        result->delimiter = strdup("\0");
        *src = NULL;
    } else {
        *p = '\0';
        *src = p + 1;
    }
}

tok_delim_t *strtok_custom(char *str, char *delimiters)
{
    tok_delim_t *result = calloc(1, sizeof(tok_delim_t));
    static char *src = NULL;
    char *p = NULL;
    char *ret = NULL;
    char *delim_found = NULL;

    if (src != NULL)
        move_str(src);
    if (str != NULL)
        src = my_strdup(str);
    if (src == NULL || *src == '\0')
        return NULL;
    ret = src;
    p = src;
    delim_found = find_delimiter(p, delimiters);
    result = fill_token(result, delim_found, ret);
    update_source(&src, delim_found, result);
    return result;
}
