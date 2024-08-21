/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** set parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int my_tablen(char **array)
{
    int size = 0;

    if (array == NULL)
        return 0;
    for (int i = 0; array[i] != NULL; i++)
        size++;
    return size;
}

static bool first_part_equal(char **array, int *i, char **final, int x)
{
    if (array[*i + 1] != NULL) {
        if (array[*i + 1][0] == '=') {
            printf("set: Variable name must begin with a letter.\n");
            return false;
        }
        final[x] = calloc(1, sizeof(char) * (strlen(array[*i]) +
            strlen(array[*i + 1]) + 1));
        sprintf(final[x], "%s%s", array[*i], array[*i + 1]);
        *i += 2;
    } else {
        final[x] = strdup(array[*i]);
        *i += 1;
    }
    return true;
}

static bool three_arguments(char **array, int *i, char **final, int x)
{
    if (array[*i + 2] != NULL) {
        if (array[*i + 2][0] == '=') {
            printf("set: Variable name must begin with a letter.\n");
            return false;
        } else {
            final[x] = calloc(1, sizeof(char) * (strlen(array[*i]) +
                strlen(array[*i + 2]) + 2));
            sprintf(final[x], "%s=%s", array[*i], array[*i + 2]);
            *i += 3;
        }
    } else {
        final[x] = strdup(array[*i]);
        *i += 1;
    }
    return true;
}

static bool handle_equality(char **array, int *i, char **final, int x)
{
    if (strcmp(array[*i + 1], "=") == 0) {
        if (three_arguments(array, i, final, x) == false)
            return false;
    } else {
        printf("set: Variable name must begin with a letter.\n");
        return false;
    }
    return true;
}

static bool is_equal(char **array, int *i, char **final, int x)
{
    if (strncmp(array[*i + 1], "=", 1) == 0) {
        if (handle_equality(array, i, final, x) == false)
            return false;
    } else {
        final[x] = strdup(array[*i]);
        *i += 1;
    }
    return true;
}

static bool parse_equal(char **array, int *i, char **final, int x)
{
    if (array[*i + 1] != NULL) {
        if (is_equal(array, i, final, x) == false)
            return false;
    } else {
        final[x] = strdup(array[*i]);
        *i += 1;
    }
    return true;
}

static bool set_parsing(char **array, int *i, char **final, int x)
{
    if (array[*i][strlen(array[*i]) - 1] == '=') {
        if (first_part_equal(array, i, final, x) == false)
            return false;
        x++;
        return true;
    }
    if (parse_equal(array, i, final, x) == false)
        return false;
    return true;
}

char **parse_array(char **array)
{
    char **final = calloc(1, sizeof(char *) * (my_tablen(array) + 1));
    int x = 0;

    if (array == NULL)
        return NULL;
    for (int i = 0; i < my_tablen(array);) {
        if (array[i][0] == '=') {
            printf("set: Variable name must begin with a letter.\n");
            return NULL;
        }
        if (set_parsing(array, &i, final, x) == false)
            return NULL;
        x++;
    }
    return final;
}
