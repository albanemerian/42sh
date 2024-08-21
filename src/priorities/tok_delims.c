/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** tok_delims
*/

#include "minishell.h"

static void upt_src(char **src, char *p, tok_delim_t *result)
{
    if (p == NULL || *p == '\0') {
        result->delimiter = strdup("\0");
        *src = NULL;
    } else
        *src = p + strlen(result->delimiter);
}

static char *find_delim(char *p, char **delimiters)
{
    char *found = NULL;
    char *temp = NULL;

    for (int i = 0; delimiters[i] != NULL; i++) {
        temp = strstr(p, delimiters[i]);
        if (temp != NULL) {
            found = (found == NULL || temp < found) ? temp : found;
        }
    }
    return found;
}

static char *delims_found(tok_delim_t *result, char *ret, char *delim_found,
    char **delimiters)
{
    size_t delim_len = 0;

    for (int i = 0; delimiters[i] != NULL; i++) {
        if (strstr(delim_found, delimiters[i]) == delim_found) {
            delim_len = strlen(delimiters[i]);
            result->delimiter = strndup(delimiters[i], delim_len);
            break;
        }
    }
    return delim_found;
}

static tok_delim_t *fill_tok(tok_delim_t *result, char *delim_found,
    char *ret, char **delimiters)
{
    size_t token_len = 0;

    if (delim_found != NULL) {
        delim_found = delims_found(result, ret, delim_found, delimiters);
        token_len = delim_found - ret;
        result->token = strndup(ret, token_len);
    } else {
        result->token = strdup(ret);
        result->delimiter = NULL;
    }
    return result;
}

tok_delim_t *tok_delims(char *str, char **delimiters)
{
    tok_delim_t *result = calloc(1, sizeof(tok_delim_t));
    static char *src = NULL;
    char *p = NULL;
    char *ret = NULL;
    char *delim_found = NULL;

    if (src != NULL)
        move_str(src);
    if (str != NULL)
        src = strdup(str);
    if (src == NULL || *src == '\0')
        return NULL;
    ret = src;
    p = src;
    delim_found = find_delim(p, delimiters);
    result = fill_tok(result, delim_found, ret, delimiters);
    upt_src(&src, delim_found, result);
    return result;
}
