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
