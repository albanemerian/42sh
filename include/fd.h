/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** fd
*/

#ifndef FD_H_
    #define FD_H_


// file_descriptor -> find_error.c
int diff_built(char *str);
int find_error_cmd(shell_t *shell, int j);
int base_pipes(shell_t *shell, char *string);
int create_piip(shell_t *shell, char *string);
bool is_found(shell_t *shell, int i);
int check_for_wrong_redir(shell_t *shell, int i, char *string);
// file_descriptor -> handle_pipes.c
int check_for_builtin(shell_t *shell, char **env, int i);
int create_and_exec(shell_t *shell, char *string);

// file_descriptor -> init_fd.c
void handle_pipes(shell_t *shell, char *string, char **env);
void init_fd(shell_t *shell, char *string, char **env);
char **parse(char *cmd, char *delim);
int nbw(char *str, char *delim);


// priorities -> delim_tok.c
tok_delim_t *fill_token(tok_delim_t *result, char *delim_found, char *ret);
char *find_delimiter(char *p, char *delimiters);
void update_source(char **src, char *p, tok_delim_t *result);
tok_delim_t *strtok_custom(char *str, char *delimiters);
int find_posibilities(shell_t *shell, char *string, int nb_operrator);
int check_for_operators(shell_t *shell, char **envp, char *string);
void init_commands(shell_t *shell, char *string, int nb_operrator);
tok_delim_t *tok_delims(char *str, char **delimiters);

#endif /* !FD_H_ */
