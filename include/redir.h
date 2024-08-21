/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** redir
*/


#ifndef REDIR_H_
    #define REDIR_H_

// redirections -> double_left.c
int double_left_redir(shell_t *shell, int *i, char *line);
int single_left_redir(shell_t *shell, int *i, char *line);
int look_for_left_chev(shell_t *shell, int *i, char *line);
void handle_file(int output_fd, char *output_filename, shell_t *shell);
void execute_simp_dir(shell_t *shell, char *string, char *output_filename);
int look_for_chev(shell_t *shell, int *i, char *line);
int look_for_dir(shell_t *shell, char *line);
void get_lines(shell_t *shell, char *line1, char *line2);
int single_left_two(shell_t *shell, int input_fd, char *line, int *i);
int double_redir(shell_t *shell, int *i, char *line);
int single_redir(shell_t *shell, int *i, char *line);

#endif /* !REDIR_H_ */
