/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** alias
*/

#ifndef ALIAS_H_
    #define ALIAS_H_

alias_t *create_alias(shell_t *shell);
int alias_handler(shell_t *shell, char **env);
int unalias_handler(shell_t *shell, char **env);
char **alias_command_line(shell_t *shell, int alias_i);
alias_t *find_alias(shell_t *shell, int alias_i);
int handle_alias_loop(shell_t *shell, int i);
char **complex_case(int alias_i, char **alias_commands, shell_t *shell);
char **simple_cases(char **alias_commands, int alias_i, shell_t *shell);
void split_command(char *command_str, alias_t *new_alias);

#endif /* !ALIAS_H_ */
