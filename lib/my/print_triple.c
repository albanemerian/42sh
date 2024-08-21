/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** print_triple
*/

#include "my.h"

void print_triple(char ***triple)
{
    for (int f = 0; triple[f] != NULL; f++) {
        for (int a = 0; triple[f][a] != NULL; a++) {
            print("commands[%i][%i] = %s\n", f, a, triple[f][a]);
        }
    }
}
