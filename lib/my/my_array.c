/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell1-albane.merian
** File description:
** my_array
*/

#include "my.h"
#include "struct.h"

// static int my_alpha(int a)
// {
//     return (a == 45 || a == 46 || a != 47 || a == 61 ||
//         (a >= 65 && a <= 90) || (a >= 97 && a <= 122));
// }

// static int my_num(char *nb)
// {
//     for (int i = 0; nb[i] != '\0'; i++) {
//         if (nb[i] <= 48 || nb[i] <= 57) {
//             return 0;
//         }
//     }
//     return 1;
// }

// char **wordss_counter(const char *str)
// {
//     int counter = 0;
//     char **array;

//     for (int i = 0; str[i] != '\0'; i++) {
//         if (!my_isalpha(str[i]) && !my_isnum((char *)&str[i]))
//             counter++;
//     }
//     array = (char **)malloc((counter + 1) * sizeof(char *));
//     if (array == NULL)
//         return NULL;
//     return array;
// }

// void midlless_words(array_t *a, const char *str, int i)
// {
//     if (a->start < str + i) {
//         a->length = i - (a->start - str) + 1;
//         a->array[a->ind] = (char *)malloc((a->length + 1) * sizeof(char));
//         my_strncpy(a->array[a->ind], a->start, a->length);
//         a->array[a->ind][a->length - 1] = '\0';
//         a->ind++;
//     }
// }

// void lastss_line(array_t *a, const char *str)
// {
//     a->length = my_strlen(a->start);
//     a->array[a->ind] = (char *)malloc((a->length + 1) * sizeof(char));
//     my_strncpy(a->array[a->ind], a->start, a->length);
//     a->array[a->ind][a->length] = '\0';
// }

// char **my_array(const char *str)
// {
//     array_t *a = malloc(sizeof(array_t));

//     a->array = wordss_counter(str);
//     a->start = str;
//     a->len = my_strlen(str);
//     for (int i = 0; str[i] != '\0'; i++) {
//         if (str[i] == '=') {
//             midlless_words(a, str, i);
//             a->start = str + i + 1;
//         }
//     }
//     lastss_line(a, str);
//     return a->array;
// }

static int is_alphanum(char c)
{
    if (c == '=')
        return (0);
    return (1);
}

static int j_length(char const *str, int i, int j)
{
    int k = 0;

    while (str[j] != '\0' && k < i) {
        if (is_alphanum(str[j]) == 0 && is_alphanum(str[j + 1]) == 1)
            k++;
        j++;
    }
    return (j);
}

static int count_words(char const *str)
{
    int words = 0;
    int letters = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_alphanum(str[i]) == 1)
            letters++;
        if ((is_alphanum(str[i]) == 0 && is_alphanum(str[i + 1]) == 1 &&
            letters > 0) || (is_alphanum(str[i]) == 1 && str[i + 1] == '\0') ||
            (is_alphanum(str[i]) == 0 && str[i + 1] == '\0' && letters > 0))
            words++;
    }
    return (words);
}

static char *count_letters(char const *str, int i)
{
    char *result = NULL;
    int j = 0;
    int k = 0;

    for (int l = 0; is_alphanum(str[l]) == 0; l++)
        j++;
    j = j_length(str, i, j);
    k = j;
    while (str[k] != '\0') {
        if (is_alphanum(str[k]) == 0) {
            result = malloc(sizeof(char) * (k - j + 1));
            return (result);
        }
        k++;
    }
    result = malloc(sizeof(char) * (k - j + 1));
    return (result);
}

static char *fill_letters(char const *str, int i)
{
    char *result = count_letters(str, i);
    int j = 0;
    int k = 0;

    for (int l = 0; is_alphanum(str[l]) == 0; l++)
        j++;
    j = j_length(str, i, j);
    k = j;
    while (str[k] != '\0') {
        if (is_alphanum(str[k]) == 0) {
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

char **my_array(char const *str)
{
    int i = 0;
    int temp = 0;
    char **dest = malloc(sizeof(char *) * (count_words(str) + 1));

    while (i < count_words(str)) {
        dest[i] = fill_letters(str, i);
        i++;
    }
    dest[i] = NULL;
    return (dest);
}
