/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** tok_word_array
*/

#include "my.h"

static int is_alphanum(char *delim, char c)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (delim[i] == c)
            return (0);
    }
    return (1);
}

static int j_length(char const *str, int i, int j, char *delim)
{
    int k = 0;

    while (str[j] != '\0' && k < i) {
        if (is_alphanum(delim, str[j]) == 0 &&
            is_alphanum(delim, str[j + 1]) == 1)
            k++;
        j++;
    }
    return (j);
}

static int count_words(char const *str, char *delim)
{
    int words = 0;
    int letters = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_alphanum(delim, str[i]) == 1)
            letters++;
        if ((is_alphanum(delim, str[i]) == 0 && is_alphanum(delim, str[i + 1])
            == 1 && letters > 0) || (is_alphanum(delim, str[i]) == 1 &&
            str[i + 1] == '\0') || (is_alphanum(delim, str[i]) == 0 &&
            str[i + 1] == '\0' && letters > 0))
            words++;
    }
    return (words);
}

static char *count_letters(char const *str, int i, char *delim)
{
    char *result = NULL;
    int j = 0;
    int k = 0;

    for (int l = 0; is_alphanum(delim, str[l]) == 0; l++)
        j++;
    j = j_length(str, i, j, delim);
    k = j;
    while (str[k] != '\0') {
        if (is_alphanum(delim, str[k]) == 0) {
            result = malloc(sizeof(char) * (k - j + 1));
            return (result);
        }
        k++;
    }
    result = malloc(sizeof(char) * (k - j + 1));
    return (result);
}

static char *fill_letters(char const *str, int i, char *delim)
{
    char *result = count_letters(str, i, delim);
    int j = 0;
    int k = 0;

    for (int l = 0; is_alphanum(delim, str[l]) == 0; l++)
        j++;
    j = j_length(str, i, j, delim);
    k = j;
    while (str[k] != '\0') {
        if (is_alphanum(delim, str[k]) == 0) {
            result = my_strncpy(result, &str[j], k - j);
            result[k - j] = '\0';
            return (result);
        }
        k++;
    }
    result = my_strncpy(result, &str[j], k - j);
    result[k - j] = '\0';
    return (result);
}

char **tok_word_array(char const *str, char *delim)
{
    int i = 0;
    int temp = 0;
    char **dest = malloc(sizeof(char *) * (count_words(str, delim) + 1));

    while (i < count_words(str, delim)) {
        dest[i] = fill_letters(str, i, delim);
        i++;
    }
    dest[i] = NULL;
    return (dest);
}
