/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** back
*/

#ifndef BACK_H_
    #define BACK_H_

// backticks -> execute_backtick_command.c
void replace_backticks(shell_t *shell, char **array);
char *execute_backtick_command(char *command);
void handle_backticks(shell_t *shell, char **array, char *result);
bool is_backtick_duplicate(char *btick_cmd, char **cmd, int num_bticks);
void add_backtick_command(char ***cmd, char *backtick_cmd, int *num_cmds);
void update_array(char **array, char *btick_res, char **cmd, int num_cmds);

#endif /* !BACK_H_ */
