/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** segfault
*/

#include <stdio.h>
#include <stddef.h>

int main() {
    int *ptr = NULL; // Initialize a pointer to NULL
    *ptr = 10;       // Attempt to dereference the NULL pointer
    return 0;
}
