/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** minishell
*/

#pragma once
#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <dirent.h>
#include <stddef.h>
#include <string.h>
#include <signal.h>
#include <glob.h>
#include "struct.h"
#include "alias.h"
#include "fd.h"
#include "history.h"
#include "list.h"
#include "par.h"
#include "redir.h"
#include "var.h"
#include "back.h"
#include "script.h"
#include "curse.h"

int handle(shell_t *shell, char *new);
int perme_handler(shell_t *shell, char *new);
int go_back_home(shell_t *shell, char *new);
int cd_handler(shell_t *shell, char **env);
int change_pwd(shell_t *shell, char *new);

// base -> echo_command.c
int echo_command(shell_t *shell, char **env);

// base -> env.c
void handle_error(shell_t *shell);
int exec_pos(shell_t *shell, char *string, char **env, int nb_operrator);
int check_str(shell_t *shell);
void free_tab(char **fun);
void two_arg(shell_t *shell, char **env);
int set_env(shell_t *shell, char **env);
void env_pwd(shell_t *shell);
void cd_home(shell_t *shell, char *new);
void envv_sett(shell_t *shell, struct list *head,
    struct list *new_node);
void fill_env(shell_t *shell, struct list *head,
    char **fun, struct list *new_node);
int arg_count(shell_t *shell);
void env_set(shell_t *shell, char **env, char **fun);
void pwd_env(shell_t *shell, char **fun,
    char *temp_arg, struct list *head);

// base -> error_handling.c
void error_handling(shell_t *shell, char **env, char **argv, int argc);

// base -> exit.c
void free_func_for_exit_value(shell_t *shell);
int exit_func(shell_t *shell, char **env);
int cmd_env(shell_t *shell, char **env);

// base -> fork_usage.c
void cmd_handler(shell_t *shell, char **envp, char *str_z, char *str);
int exec_last(shell_t *shell, pid_t pid, char **envp, char *str);
void get_new_path(shell_t *shell, char **envp);
int last_exec(shell_t *shell, char **env);

// base -> helper.c
int helper(int argc);

// base -> init_and_find.c
void handle_opperator(shell_t *shell, char *string, char **env, int *i);
void init_cmd_line(shell_t *shell, char *string, char **env);

void display_prompt(shell_t *shell);
int look_for_parenthesis(shell_t *shell, char *string);

// base -> list_to_array.c
int len_array(shell_t *shell);
char **list_to_array(shell_t *shell, char **env);

// base -> option_handler.c
char **make_array(shell_t *shell, char **p, char *result, char **n);
char **fill_str(char *line);
char **fill_quote(shell_t *s, char *line);
char **parse_str(shell_t *s, char *line);
void option(shell_t *shell, char *string);

// base -> path_handling.c
void get_home(shell_t *shell);
void get_env(shell_t *shell);
int env_length(char **env);
void get_path(char **env, shell_t *shell);

// base -> set_env_solo.c
void alone_env(shell_t *shell, struct list *head, struct list *new_node);
int env_alone(shell_t *shell, char **env);
void alone_env(shell_t *shell, struct list *head, struct list *new_node);
// base -> shell.c
void fill_history_and_ncurses(shell_t *shell);
void free_func(shell_t *shell);
void without_a_pip(shell_t *shell, char **env);
int shell(int ac, char **av, char **env);
int null_command(shell_t *shell, int j);

// base -> unset_env.c
void unset_envv(shell_t *shell, int len, int i);
int unset_env(shell_t *shell, char **env);

// glob functions
char **no_matching(shell_t *shell);
char **handle_glob(shell_t *shell);
int perform_glob(char *pattern, char ***exp_arg, int *num_exp);

int init_screen(shell_t *shell);
void tty_user_input(shell_t *shell, char **env);
shell_t *malloc_struct(void);
void ncurses_user_input(shell_t *shell, char **env);
int builtin_clear(shell_t *shell, char *string);
