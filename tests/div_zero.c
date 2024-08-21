/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** div_zero
*/

#include <stdio.h>

int main() {
    int numerator = 10;
    int denominator = 0;
    int result = numerator / denominator;  // Division by zero
    printf("Result: %d\n", result); 
    return 0;
}
