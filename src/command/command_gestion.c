/*
** EPITECH PROJECT, 2023
** command_gestion
** File description:
** handle the different types of command
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "mysh.h"

static char **convert_env(head_t *head)
{
    char **c_env = NULL;
    int i = 0;

    c_env = malloc((head->size + 1) * sizeof(char *));
    for (env_t *e = head->first; e->line != NULL; e = e->next) {
        c_env[i] = e->line;
        i++;
    }
    c_env[i] = NULL;
    return c_env;
}

int command_exit_gestion(int state)
{
    int sig = 0;

    if (WIFEXITED(state))
        return WEXITSTATUS(state);
    sig = WTERMSIG(state);
    write(2, strsignal(sig), my_strlen(strsignal(sig)));
    write(2, "\n", 1);
    return state;
}

static int execute_command(char *command, char **arg, head_t *head)
{
    int pid = 0;
    int state = 0;
    char **c_env = NULL;

    c_env = convert_env(head);
    pid = fork();
    if (pid < 0) {
        head->keep = false;
        return 84;
    }
    if (pid == 0)
        execve(command, arg, c_env);
    if (pid > 0)
        waitpid(pid, &state, 0);
    free(c_env);
    return command_exit_gestion(state);
}

bool path_command(char **c, head_t *head, int *r)
{
    char *file_path = NULL;

    for (int i = 0; head->path && head->path[i] != NULL; i++) {
        file_path = malloc(my_strlen(c[0]) + my_strlen(head->path[i]) + 2);
        if (!file_path) {
            head->lr = 84;
            head->keep = false;
            return true;
        }
        my_strcpy(file_path, head->path[i]);
        my_strcat(file_path, "/");
        my_strcat(file_path, c[0]);
        if (access(file_path, X_OK) == 0) {
            *r = execute_command(file_path, c, head);
            free(file_path);
            return true;
        }
        free(file_path);
    }
    return false;
}

int use_command(char **command_line, head_t *head)
{
    struct stat extract = {0};
    int r = 0;

    if (command_line[0] == NULL)
        return head->lr;
    if (exec_special_case(command_line, head, &r))
        return r;
    if (path_command(command_line, head, &r))
        return r;
    if (access(command_line[0], F_OK) == 0) {
        if (access(command_line[0], X_OK) == 0 &&
        lstat(command_line[0], &extract) != -1 && !S_ISDIR(extract.st_mode))
            return execute_command(command_line[0], command_line, head);
        write(2, command_line[0], my_strlen(command_line[0]));
        write(2, ": Permission denied.\n", 21);
        return 1;
    }
    write(2, command_line[0], my_strlen(command_line[0]));
    write(2, ": Command not found.\n", 21);
    return 1;
}