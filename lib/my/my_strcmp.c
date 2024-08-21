/*
** EPITECH PROJECT, 2023
** my_strcmp
** File description:
** my_strcmp
*/
#include "my.h"

int strcmp_my(char const *s1, char const *s2)
{
    int s1_len = my_strlen(s1);
    int s2_len = my_strlen(s2);

    if (s1_len != s2_len)
        return 0;
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i]) {
            return (0);
        }
    }
    return 1;
}

int my_cmp(char const *s1, char const *s2)
{
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] == s2[i]) {
            return (1);
        }
    }
    return 0;
}

int cmp_my(char const *s1, char const *s2)
{
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] > s2[i]) {
            return (1);
            }
        if (s1[i] < s2[i]) {
            return (-1);
        }
    }
    return 0;
}

int str_my(char const *s1, char const *s2)
{
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i]) {
            return (0);
        }
    }
    return 1;
}

bool my_str_cmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] == s2[i]) {
        if (s1[i] == '\0')
            return true;
        i++;
    }
    return false;
}
