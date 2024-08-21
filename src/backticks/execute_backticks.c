/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** execute_backticks
*/

#include "minishell.h"

char *execute_backtick_command(char *command)
{
    FILE *cmd = popen(command, "r");
    char buffer[1024];
    size_t result_size = 0;
    char *result = NULL;

    if (!cmd) {
        print("Error executing command: '%s'\n", command);
        return NULL;
    }
    while (fgets(buffer, sizeof(buffer), cmd)) {
        result = realloc(result, result_size + strlen(buffer) + 1);
        strcpy(result + result_size, buffer);
        result_size += strlen(buffer);
    }
    if (pclose(cmd) != 0) {
        print(": Command not found\n");
        free(result);
        return NULL;
    }
    return result;
}
