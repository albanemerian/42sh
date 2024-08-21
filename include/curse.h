/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** curse
*/

#ifndef CURSE_H_
    #define CURSE_H_

// ncurses.c
void get_prompt_entered(shell_t *shell);
void display_execution(shell_t *shell);
void prompt_moves(shell_t *shell);
int key_left_pressed(shell_t *shell, int *i);
int key_right_pressed(shell_t *shell, int *i);

#endif /* !CURSE_H_ */
