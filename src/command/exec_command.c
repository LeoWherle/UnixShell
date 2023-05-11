/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec command
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
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

static bool check_binary(char *command)
{
    char arch[5] = {'\0'};
    int fd = 0;

    fd = open(command, O_RDONLY);
    read(fd, arch, 4);
    if (strcmp("ELF", arch) != 0) {
        fprintf(stderr, "%s: cannot execute binary file: Exec format error\n",
                command);
        return true;
    }
    return false;
}

int execute_command(char *command, char **arg, head_t *head)
{
    int pid = 0;
    int state = 0;
    char **c_env = NULL;

    if (check_binary(command))
        return 126;
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
