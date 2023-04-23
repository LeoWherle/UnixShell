/*
** EPITECH PROJECT, 2023
** my_cd2
** File description:
** rebuild of cd 2.0 you will (not) change of directorie
*/

#include <stddef.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "mysh.h"

static int new_oldpwd(env_t *oldpwd, env_t *pwd)
{
    if (oldpwd->line && oldpwd->line[7] != '\0' && pwd->line
        && pwd->line[4] != '\0') {
        free(oldpwd->line);
        oldpwd->line = my_str_copy_cat("OLD", pwd->line);
        if (!oldpwd->line)
            return -2;
    }
    return 0;
}

int new_pwd(env_t *pwd, head_t *head)
{
    char *path = NULL;

    if (pwd->line)
        free(pwd->line);
    else {
        head->size++;
        pwd->next = add_env(NULL);
    }
    path = getcwd(path, 0);
    if (path == NULL)
        return -2;
    pwd->line = my_str_copy_cat("PWD=", path);
    if (!pwd->line)
        return -2;
    free(path);
    return 0;
}

static int error_cd(char *go_to, head_t *head, char misc)
{
    struct stat extract = {0};
    if (go_to == head->home) {
        if (misc == ' ')
            write(2, "cd: No home directory.\n", 23);
        if (misc == '~')
            write(2, "No $home variable set.\n", 23);
        return 1;
    }
    if (my_strcmp(go_to, "-") != 0)
        write(2, go_to, my_strlen(go_to));
    if (lstat(go_to, &extract) != -1 && !S_ISDIR(extract.st_mode)) {
        write(2, ": Not a directory.\n", 19);
        return 1;
    }
    if (access(go_to, F_OK) == 0 && access(go_to, X_OK) != 0) {
        write(2, ": Permission denied.\n", 21);
        return 1;
    }
    write(2, ": No such file or directory.\n", 29);
    return 1;
}

static int change_var(char *go_to, head_t *head, char misc)
{
    env_t *pwd = find_env(head->first, "PWD");
    env_t *oldpwd = find_env(head->first, "OLDPWD");
    char *path = NULL;

    path = getcwd(path, 0);
    if (head->old)
        free(head->old);
    if (!go_to || chdir(go_to) == -1) {
        return error_cd(go_to, head, misc);
    }
    head->old = malloc((my_strlen(path) + 1) * sizeof(char));
    my_strcpy(head->old, path);
    free(path);
    new_oldpwd(oldpwd, pwd);
    new_pwd(pwd, head);
    return 0;
}

int find_cd_type(char **command_line, head_t *head, int i)
{
    char *old = NULL;
    int r = 0;

    if (!command_line[i])
        return change_var(head->home, head, ' ');
    if (command_line[i] && !command_line[i + 1]) {
        if (my_strcmp(command_line[i], "~") == 0)
            return change_var(head->home, head, '~');
        if (my_strcmp(command_line[i], "-") == 0 && head) {
            old = malloc((my_strlen(head->old) + 1) * sizeof(char));
            my_strcpy(old, head->old);
            r = change_var(old, head, '\0');
            free(old);
            return r;
        }
        return change_var(command_line[i], head, '\0');
    }
    write(2, "cd: Too many arguments.\n", 24);
    return 1;
}
