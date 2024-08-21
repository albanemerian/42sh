/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_helper
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

void base(void)
{
    cr_redirect_stdout();
}

Test(error_handling, two_arguments_help, .init = base)
{
    shell_t shell;
    shell.history = malloc(sizeof(*shell.history));
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;

    char *env[] = {NULL};
    char *av[] = {"./42sh", "-h", NULL};
    int ac = 2;

    error_handling(&shell, env, av, 2);

    cr_assert_eq(shell.base->status, 0, "Expected shell status to be 0");

    free(shell.history);
    free(shell.base);
}

Test(exec_pos, no_operators_no_pipes)
{
    shell_t shell;
    shell.pipe = malloc(sizeof(*shell.pipe));
    shell.pipe->nb_pipe = 0;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;
    shell.par = malloc(sizeof(*shell.par));
    shell.par->is_par = false;

    char *string = strdup("command");
    char *env[] = {NULL};

    cr_assert_eq(exec_pos(&shell, string, env, 0), 1, "Expected 1 for no operators and no pipes");
}

Test(init_cmd_line, no_parenthesis)
{
    shell_t shell;
    shell.par = malloc(sizeof(*shell.par));
    shell.par->is_par = false;
    shell.pipe = malloc(sizeof(*shell.pipe));
    shell.pipe->nb_pipe = 0;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;
    shell.base->env = NULL;
    shell.queue = malloc(sizeof(*shell.queue));
    shell.queue->commands = NULL;

    char *string = strdup("command");
    char *env[] = {NULL};

    init_cmd_line(&shell, string, env);
    cr_assert_eq(shell.base->status, 0, "Expected shell status to be 0");
}

Test(fill_token, delimiter_found)
{
    tok_delim_t *result = calloc(1, sizeof(tok_delim_t));
    char *delim_found = ",";
    char *ret = "token";

    result = fill_token(result, delim_found, ret);

    cr_assert_str_eq(result->token, "token", "Expected token to be 'token'");
    cr_assert_str_eq(result->delimiter, ",", "Expected delimiter to be ','");

    free(result->delimiter);
    free(result);
}

Test(find_delimiter, delimiter_in_string)
{
    char *p = "token , token";
    char *delimiters = ",";

    char *delim_found = find_delimiter(p, delimiters);

}

Test(update_source, null_pointer)
{
    char *src = strdup("token");
    char *p = NULL;
    tok_delim_t *result = calloc(1, sizeof(tok_delim_t));

    update_source(&src, p, result);

    cr_assert_null(src, "Expected src to be NULL");
    cr_assert_str_eq(result->delimiter, "\0", "Expected delimiter to be '\0'");

    free(src);
    free(result->delimiter);
    free(result);
}

Test(strtok_custom, valid_string_and_delimiters)
{
    char *str = strdup("token,token");
    char *delimiters = ",";

    tok_delim_t *result = strtok_custom(str, delimiters);

    cr_assert_str_eq(result->token, "token", "Expected token to be 'token'");
    cr_assert_str_eq(result->delimiter, ",", "Expected delimiter to be ','");

    free(str);
    free(result->delimiter);
    free(result);
}

Test(single_left_redir, fork_error)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;

    int i = 4;
    char *line = strdup("command\n");

    int result = look_for_left_chev(&shell, &i, line);
    cr_assert_eq(result, 0, "Expected 0");
}

Test(look_for_left_chev, left_chevron_found)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;

    int i = 4;
    char *line = strdup("command <");
    int single_left_redir(shell_t *shell, int *i, char *line) {
        return 1;
    }
}

Test(look_for_dir, chevron_found)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->status = 0;
    shell.redirections = malloc(sizeof(*shell.redirections));
    shell.redirections->is_double = 0;

    char *line = strdup("command >");

    int look_for_chev(shell_t *shell, int *i, char *line) {
        return 1;
    }
    int look_for_left_chev(shell_t *shell, int *i, char *line) {
        return 0;
    }
    cr_assert_eq(look_for_dir(&shell, line), 1, "Expected 1 for chevron found");
    cr_assert_eq(shell.redirections->is_double, 2, "Expected is_double to be 2");
}

Test(len_array, valid_list)
{
    shell_t shell;
    shell.current = malloc(sizeof(struct list));
    shell.current->str = strdup("command");
    shell.current->next = malloc(sizeof(struct list));
    shell.current->next->str = strdup("command");
    shell.current->next->next = NULL;

    cr_assert_eq(len_array(&shell), 2, "Expected length of list to be 2");
}

Test(list_to_array, valid_list_and_env)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->env_len = 2;
    shell.current = malloc(sizeof(struct list));
    shell.current->str = strdup("command");
    shell.current->next = malloc(sizeof(struct list));
    shell.current->next->str = strdup("command");
    shell.current->next->next = NULL;

    char *env[] = {"ENV1=value1", "ENV2=value2", NULL};

    char **array = list_to_array(&shell, env);

    cr_assert_str_eq(array[0], "command", "Expected first element of array to be 'command'");
    cr_assert_str_eq(array[1], "command", "Expected second element of array to be 'command'");
    cr_assert_null(array[2], "Expected third element of array to be NULL");
}

Test(get_env, valid_env)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->env = malloc(sizeof(char *) * 3);
    shell.base->env[0] = strdup("ENV1=value1");
    shell.base->env[1] = strdup("ENV2=value2");
    shell.base->env[2] = NULL;
    shell.current = NULL;

    get_env(&shell);

    cr_assert_str_eq(shell.current->str, "ENV1=value1", "Expected first element of list to be 'ENV1=value1'");
    cr_assert_str_eq(shell.current->next->str, "ENV2=value2", "Expected second element of list to be 'ENV2=value2'");
    cr_assert_null(shell.current->next->next, "Expected third element of list to be NULL");
}

Test(get_home, valid_env)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->env = malloc(sizeof(char *) * 3);
    shell.base->env[0] = strdup("HOME=/home/user");
    shell.base->env[1] = strdup("PATH=/bin:/usr/bin");
    shell.base->env[2] = NULL;
    shell.base->home = NULL;
    shell.base->path = NULL;

    char **array = malloc(sizeof(char *) * 3);
    array[0] = strdup("/bin");
    array[1] = strdup("/usr/bin");
    array[2] = NULL;

    get_home(&shell);

    cr_assert_str_eq(shell.base->home, "/home/user", "Expected home to be '/home/user'");
    cr_assert_str_eq(shell.base->path[0], "/bin", "Expected first element of path to be '/bin'");
    cr_assert_str_eq(shell.base->path[1], "/usr/bin", "Expected second element of path to be '/usr/bin'");
    cr_assert_null(shell.base->path[2], "Expected third element of path to be NULL");
}

Test(env_length, valid_env)
{
    char *env[] = {"ENV1=value1", "ENV2=value2", NULL};

    cr_assert_eq(env_length(env), 2, "Expected length of env to be 2");
}

Test(get_path, valid_env)
{
    shell_t shell;
    shell.base = malloc(sizeof(*shell.base));
    shell.base->env = NULL;
    shell.base->path = NULL;
    shell.base->env_len = 0;

    char *env[] = {"ENV1=value1", "ENV2=value2", NULL};

    get_path(env, &shell);

    cr_assert_str_eq(shell.base->env[0], "ENV1=value1", "Expected first element of env to be 'ENV1=value1'");
    cr_assert_str_eq(shell.base->env[1], "ENV2=value2", "Expected second element of env to be 'ENV2=value2'");
    cr_assert_null(shell.base->env[2], "Expected third element of env to be NULL");
}
