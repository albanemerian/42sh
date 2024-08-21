/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_arr_to_str
*/

#include "my.h"
#include <stdlib.h>
#include <string.h>

static char *my_cpy(char *dest, const char *src)
{
    char *temp = dest;

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return temp;
}

static size_t my_len(const char *str)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char **dup_it(char **dup_str, int *i)
{
    if (dup_str[*i] == NULL) {
        for (int j = 0; j < *i; j++) {
            free(dup_str[j]);
        }
        free(dup_str);
        return NULL;
    }
    return dup_str;
}

char **dup_arr(char **strings)
{
    int num_str = 0;
    char **dup_str = NULL;

    while (strings[num_str] != NULL) {
        num_str++;
    }
    dup_str = (char **)malloc((num_str + 1) * sizeof(char *));
    if (dup_str == NULL) {
        return NULL;
    }
    for (int i = 0; i < num_str; i++) {
        dup_str[i] = my_strdup(strings[i]);
        dup_it(dup_str, &i);
    }
    dup_str[num_str] = NULL;
    return dup_str;
}

void fil_str(int num_str, int cur_pos, char **strings, char *result)
{
    for (int i = 0; i < num_str; i++) {
        my_cpy(result + cur_pos, strings[i]);
        cur_pos += my_len(strings[i]);
        if (i < num_str - 1) {
            result[cur_pos] = ' ';
            cur_pos++;
        }
    }
}

char *my_array_to_str(char **strings)
{
    int num_str = 0;
    int total_len = 0;
    char *result = NULL;
    int cur_pos = 0;

    while (strings[num_str] != NULL) {
        total_len += my_len(strings[num_str]);
        num_str++;
    }
    total_len += num_str - 1;
    result = (char *)malloc((total_len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    fil_str(num_str, cur_pos, strings, result);
    result[total_len] = '\0';
    return result;
}
