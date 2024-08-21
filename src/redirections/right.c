/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** right
*/

#include "minishell.h"
#include <fcntl.h>

static void is_move(char *str)
{
    int i = 0;
    int j = 0;
    int len = my_strlen(str);

    for (; i < len; i++) {
        if (str[i] != ' ')
            break;
    }
    if (i > 0) {
        for (; j < len - i; j++)
            str[j] = str[j + i];
        str[j] = '\0';
        len = my_strlen(str);
    }
    for (i = len - 1; i >= 0; i--) {
        if (str[i] != ' ')
            break;
    }
    if (i < len - 1)
        str[i + 1] = '\0';
}

static char *handle_input_redir(shell_t *shell, char *string)
{
    char *output_file = NULL;
    int i = 0;
    int len = strlen(string);

    for (; string[i] != '\0'; i++) {
        if (string[i] == '<')
            break;
    }
    if (i == len)
        return string;
    output_file = my_strndup(string, i);
    return output_file;
}

static int look_for_error(shell_t *shell, int output_fd,
    char *output_filename)
{
    if (output_fd == -1) {
        print("Missing name for redirect.\n");
        shell->redirections->status = 2;
        shell->base->status = 1;
        return 84;
    }
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        shell->base->status = 1;
        return 84;
    }
    close(output_fd);
    return 1;
}

void handle_file(int output_fd, char *output_filename, shell_t *shell)
{
    int open_flags = 0;

    output_filename = handle_input_redir(shell, output_filename);
    if (output_filename != NULL) {
        is_move(output_filename);
        open_flags = O_WRONLY | O_CREAT |
            (shell->redirections->is_double ? O_APPEND : O_TRUNC);
        output_fd = open(output_filename, open_flags, S_IRUSR | S_IWUSR);
        if (look_for_error(shell, output_fd, output_filename) == 84) {
            exit(1);
        }
    } else {
        print("%s: No such file or directory.\n", output_filename);
        shell->base->status = 1;
        exit(1);
    }
}

void execute_simp_dir(shell_t *shell, char *string, char *output_filename)
{
    pid_t pid = fork();
    int output_fd = 0;

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        handle_file(output_fd, output_filename, shell);
        option(shell, string);
        shell->base->status = 1;
        exit(1);
    } else
        waitpid(pid, &shell->base->status, 0);
}

int single_redir(shell_t *shell, int *i, char *line)
{
    char *line1 = NULL;
    char *line2 = NULL;

    *i -= 1;
    line1 = my_strndup(line, *i);
    line2 = my_strdup(line + *i + 1);
    if (line2 == NULL) {
        print("Missing name for redirect.\n");
        shell->redirections->status = 2;
        shell->base->status = 1;
        exit(1);
    }
    shell->redirections->is_double = 0;
    execute_simp_dir(shell, line1, line2);
    return 1;
}

int look_for_chev(shell_t *shell, int *i, char *line)
{
    if (line[*i] == '>') {
        (*i)++;
        if (line[*i] != '>') {
            return single_redir(shell, i, line);
        }
        if (line[*i] == '>') {
            return double_redir(shell, i, line);
        }
    }
    return 0;
}

int look_for_dir(shell_t *shell, char *line)
{
    char *temp = my_strdup(line);

    for (int i = 0; line[i] != '\0'; i++) {
        if (look_for_chev(shell, &i, line) == 1) {
            shell->redirections->is_double = 2;
            return 1;
        }
    }
    for (int j = 0; temp[j] != '\0'; j++) {
        if (look_for_left_chev(shell, &j, temp) == 1) {
            return 1;
        }
    }
    shell->redirections->is_double = 2;
    return 0;
}
