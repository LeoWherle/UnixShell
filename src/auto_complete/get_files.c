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
#include "mystr.h"

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

static int count_corresponding_files(char **file_list, char *field)
{
    char *tmp = NULL;
    int i = 0;
    int k = 0;

    for (i = 0; file_list[i]; i++) {
        tmp = file_list[i];
        if (strncmp(tmp, field, strlen(field)) == 0) {
            k++;
        }
    }
    return (k);
}

char **get_corresponding_files(char **file_list, char *field)
{
    char *tmp = NULL;
    int i = 0; int k = 0;
    char **tmp_list = NULL;

    k = count_corresponding_files(file_list, field);
    tmp_list = malloc(sizeof(char *) * (k + 1));
    ASSERT_MALLOC(tmp_list, NULL);
    k = 0;
    for (i = 0; file_list[i]; i++) {
        tmp = file_list[i];
        if (strncmp(tmp, field, strlen(field)) == 0) {
            tmp_list[k] = strdup(file_list[i]);
            k++;
        }
    }
    tmp_list[k] = NULL;
    free_matrix(file_list);
    return (tmp_list);
}
