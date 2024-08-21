/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** script
*/

#ifndef SCRIPT_H_
    #define SCRIPT_H_

// shell_scripting -> execute.c
shell_t *read_42shrc(shell_t *s, char **env);
bool check_line(shell_t *s, char **env);
int shell_scripting(char *path, shell_t *shell, char **env);

#endif /* !SCRIPT_H_ */
