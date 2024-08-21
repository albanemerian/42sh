/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** struct
*/

#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef STRUCT_H_
    #define STRUCT_H_

//linked list structure
typedef struct node_s {
    void *data;
    struct node_s *next;
    struct node_s *prev;
} node_t;

typedef struct list_s {
    node_t *first;
    bool loop;
} list_t;

//alias structure
typedef struct alias_s {
    char *name;
    char **command;
} alias_t;

//history strucutre
struct hist {
    char *str;
    int hour;
    int min;
    int id;
    struct hist *prev;
    struct hist *next;
};

typedef struct history_s {
    FILE *file;
    int cmd_num;
    struct hist *hist;
    char *line;
    size_t len;
    ssize_t read;
} history_t;

//queue structure to handle || && ; operators
typedef struct tok_delim_s {
    char *token;
    char *delimiter;
} tok_delim_t;

typedef struct queue_s {
    int priority;
    char **str;
    int status;
    int type;
    bool semicolon;
    bool and_op;
    bool pipe;
    char ***commands;
} queue_t;

//pipe structure
typedef struct pipe_s {
    bool pipe;
    int input;
    int output;
    int nb_pipe;
    char ***arr;
    bool error;
} pipe_t;

typedef struct par_s {
    int num_par;
    int *pos;
    char **array;
    char ***commands;
    bool is_par;
} par_t;

//redirections structure
typedef struct redirection_s {
    int fd;
    char **arr;
    int input;
    int output;
    int is_double;
    int status;
} redirection_t;

//ncurses structure
typedef struct ncurses_s {
    int line;
    int col;
    int ch;
    int fd;
    int out;
    int err;
    int hist_num;
    int prompt;
    int size_input;
    char *input;
    WINDOW *win;
} ncurses_t;

//set linked list
typedef struct set_list_s {
    char *var;
    char *content;
    struct set_list_s *next;
} set_list_t;

typedef struct bticks_s {
    char **keep_bticks;
    int nb_bticks;
    char quote;
    char *l;
} bticks_t;

//main structure of Minishell1
typedef struct base_s {
    char **env;
    char **path;
    char *l;
    char *home;
    char *oldpwd;
    char **arr;
    size_t len;
    ssize_t read;
    int status;
    int env_len;
    int result;
    char **fun;
    char *arg;
    char *temp;
} base_t;

//shell structure
typedef struct shell_s {
    base_t *base;
    pipe_t *pipe;
    history_t *history;
    queue_t *queue;
    ncurses_t *ncurses;
    set_list_t *variables;
    redirection_t *redirections;
    list_t *alias;
    par_t *par;
    bticks_t *bticks;
    struct list *current;
    int (*disp) (const char *restrict format, ...);
    bool tty;
} shell_t;

//env linked list
struct list {
    char *str;
    struct list *next;
};

int helper(int argc);
#endif /* !STRUCT_H_ */
