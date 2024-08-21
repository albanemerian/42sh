/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** par
*/


#ifndef PAR_H_
    #define PAR_H_

// parenthesis -> find_parenthesis.c
int part_three(shell_t *shell, char *line, int i);
int part_two(shell_t *shell, char *line, int i);
int find_erno(shell_t *shell, char *line, int num_left, int num_rigth);
int look_for_parenthesis(shell_t *shell, char *line);
int pos_parenthese(shell_t *shell, char *string, int num_left);
void check_if_parenthese(shell_t *shell, char *string);
void fill_new_arr(shell_t *shell);

#endif /* !PAR_H_ */
