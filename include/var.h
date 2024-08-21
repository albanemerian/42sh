/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** var
*/

#ifndef VAR_H_
    #define VAR_H_

set_list_t *cwd(shell_t *shell);
void my_cwdcmd(shell_t *shell);
set_list_t *home(shell_t *shell);
void change_home_value(shell_t *shell, char *name);
int is_ignoreof(shell_t *shell);
void my_precmd(shell_t *shell);
void my_postcmd(shell_t *shell);
set_list_t *last_cmd(shell_t *shell);
set_list_t *prompt(shell_t *shell);
void display_prompt(shell_t *shell);
set_list_t *term(shell_t *shell);
void change_term_value(shell_t *shell, char *name);
void display_set(shell_t *shell);
int check_existant_var(set_list_t *begin, char *cmp);
set_list_t *add_variables(char **var, set_list_t **begin);
set_list_t *upt_variables(char **var, set_list_t **begin);
set_list_t *set_variable(char *var, set_list_t **begin);
int return_value(shell_t *shell);
int set_func(shell_t *shell, char **env);
void modif_special_variables(shell_t *shell);
char **parse_array(char **array);
void sort_set(shell_t *shell, char **env);
int unset_func(shell_t *shell, char **env);
char *last_elem(shell_t *shell);
int parse_dollar(shell_t *shell, int i, int j);
#endif /* !VAR_H_ */
