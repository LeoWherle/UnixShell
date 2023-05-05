/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get files for autocomplete
*/

#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "errorh.h"

int get_file_nb(char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    int i = 0;

    dir = opendir(path);
    if (dir == NULL) return (-1);
    entry = readdir(dir);
    while (entry) {
        if (entry->d_name[0] == '.') {
            entry = readdir(dir);
            continue;
        }
        i++;
        entry = readdir(dir);
    }
    closedir(dir);
    return (i);
}

char **get_file_list(char **file_list, char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    int i = 0;

    for (i = 0; file_list[i]; i++);
    dir = opendir(path);
    ASSERT_MALLOC(dir, NULL);
    entry = readdir(dir);
    while (entry) {
        if (entry->d_name[0] == '.') {
            entry = readdir(dir);
            continue;
        }
        file_list[i] = strdup(entry->d_name);
        i++;
        entry = readdir(dir);
    }
    closedir(dir);
    file_list[i] = NULL;
    return (file_list);
}

void print_fake_ls(char **file_list)
{
    int i = 1;

    write(1, "\n", 1);
    write(1, file_list[0], strlen(file_list[0]));
    write(1, "*", 1);
    while (file_list[i]) {
        write(1, "\t", 1);
        write(1, file_list[i], strlen(file_list[i]));
        i++;
    }
    write(1, "\n", 1);
}

char *get_command(char *field)
{
    char *command = NULL;
    int i = 0;

    for (i = strlen(field) - 1; i >= 0; i--) {
        if (field[i] == ' ' || field[i] == '\t') {
            command = &field[i + 1];
            break;
        }
    }
    if (command == NULL)
        command = field;
    return (command);
}

void get_corresponding_files(char **file_list, char *field)
{
    char *tmp = NULL;
    int i = 0;
    int k = 0;

    for (i = 0; file_list[i]; i++) {
        tmp = strdup(file_list[i]);
        if (strncmp(tmp, field, strlen(field)) == 0) {
            file_list[k] = strdup(file_list[i]);
            k++;
        }
        free(tmp);
    }
    i = k;
    if (file_list[k]) {
        while (file_list[k]) {
            free(file_list[k]);
            k++;
        }
    }
    file_list[i] = NULL;
}
