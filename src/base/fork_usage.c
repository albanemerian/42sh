/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** fork_usage
*/

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ncurses.h>

void handle_error(shell_t *shell)
{
    if (errno == ENOEXEC) {
        print("%s: Exec format error. ", shell->base->arr[0]);
        print("Wrong Architecture.\n");
        shell->base->status = 1;
        exit(1);
    }
    if (errno == EACCES) {
        print("%s: Permission denied.\n", shell->base->arr[0]);
        shell->base->status = 1;
        exit(1);
    }
    if (errno == ENOENT) {
        print("%s: Command not found.\n", shell->base->arr[0]);
        shell->base->status = 1;
        exit(1);
    }
}

static void check_path(shell_t *shell)
{
    int len = my_tablen(shell->base->path);

    if (len == 1 && strcmp_my(shell->base->path[0], "/") == 1) {
        print("%s: Command not found.\n", shell->base->arr[0]);
        shell->base->status = 1;
        exit(1);
    }
}

static void not_full_path(shell_t *shell, char **envp, char *str_z, char *str)
{
    char *dup_path = NULL;

    check_path(shell);
    for (int i = 0; shell->base->path[i] != NULL; i++) {
        dup_path = my_strdup(shell->base->path[i]);
        str = my_cat(dup_path, "/");
        str = my_cat(str, str_z);
        if (access(str, F_OK) == 0) {
            execve(str, shell->base->arr, envp);
            free(str_z);
            exit(EXIT_FAILURE);
        }
        free(dup_path);
    }
}

void cmd_handler(shell_t *shell, char **envp, char *str_z, char *str)
{
    if (execve(shell->base->arr[0], shell->base->arr, envp) != -1)
        exit(EXIT_FAILURE);
    if (errno == ENOENT)
        not_full_path(shell, envp, str_z, str);
    else
        handle_error(shell);
}

static void rest_segfault(shell_t *shell, int status)
{
    if (shell->base->status == 134) {
        print("Aborted");
        if (WCOREDUMP(status))
            print(" (core dumped)");
        print("\n");
    }
    if (shell->base->status == 135) {
        print("Bus error\n");
        if (WCOREDUMP(status))
            print(" (core dumped)");
        print("\n");
    }
}

static void segfault_handler(shell_t *shell, int status)
{
    if (shell->base->status == 139) {
        print("Segmentation fault");
        if (WCOREDUMP(status))
            print(" (core dumped)");
        print("\n");
    }
    if (shell->base->status == 136) {
        print("Floating exception");
        if (WCOREDUMP(status))
            print(" (core dumped)");
        print("\n");
    }
    rest_segfault(shell, status);
}

static void check_singal(shell_t *shell, int status)
{
    if (WIFEXITED(status))
        shell->base->status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->base->status = 128 + WTERMSIG(status);
    segfault_handler(shell, status);
}

int exec_last(shell_t *shell, pid_t pid, char **envp, char *str)
{
    struct stat path_stat;
    char *str_z = NULL;
    char **cpy = my_array_dup(shell->base->arr);

    for (int i = 0; cpy[i]; i++)
        if (handle_alias_loop(shell, i) == 1)
            return 1;
    str_z = my_strdup(shell->base->arr[0]);
    stat(shell->base->arr[0], &path_stat);
    cmd_handler(shell, envp, str_z, str);
    handle_error(shell);
    shell->base->status = EXIT_FAILURE;
    exit(EXIT_FAILURE);
    return 1;
}

void get_new_path(shell_t *shell, char **envp)
{
    for (int i = 0; envp[i] != NULL; i ++) {
        if (str_my(envp[i], "PATH=") == 1) {
            shell->base->path = tok_word_array(&envp[i][5], ":");
            return;
        }
    }
    shell->base->path[0] = my_strdup("/usr/bin");
    shell->base->path[1] = my_strdup("/bin");
    shell->base->path[2] = my_strdup("/usr/local/bin");
    shell->base->path[3] = my_strdup("/usr/sbin");
    shell->base->path[4] = NULL;
}

int last_exec(shell_t *shell, char **env)
{
    char *str = NULL;
    char **envp = list_to_array(shell, env);
    pid_t pid = fork();
    int status = 0;

    get_new_path(shell, envp);
    if (pid < 0)
        return 1;
    if (pid == 0) {
        if (exec_last(shell, pid, envp, str) == 1)
            return 1;
    } else {
        wait(&status);
        check_singal(shell, status);
    }
    return 0;
}
