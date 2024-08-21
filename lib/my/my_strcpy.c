/*
** EPITECH PROJECT, 2023
** my_strcpy
** File description:
** my_strcpy
*/

void replace(const char *src, char *dest)
{
    int i;

    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

char *my_strcpy(const char *src, char *dest)
{
    replace(src, dest);
    return (dest);
}
