/*
** EPITECH PROJECT, 2023
** my_cd1
** File description:
** rebuild of cd 1.0 you will (maybe) find the flag
*/

#include <stdbool.h>
#include <unistd.h>
#include "mysh.h"

static bool what_flag(char *command, char flag[2])
{
    for (int i = 1; command[i] != '\0'; i++) {
        if (command[i] == 'l') {
            flag[1] = 'l';
            continue;
        }
        if (command[i] == 'n' || command[i] == 'p') {
            flag[1] = (flag[1] == 'l') ? 'l' : 'n';
            continue;
        }
        if (command[i] == 'v') {
            flag[0] = 'v';
            flag[1] = (flag[1] == 'l') ? 'l' : 'n';
            continue;
        }
        write(2, "Usage: cd [-plvn][-|<dir>].\n", 28);
        return true;
    }
    return false;
}

static int find_flag(char **command, char flag[2])
{
    int i = 1;

    for (i = 1; command[i] && command[i][0] == '-'; i++) {
        if (my_strcmp(command[i], "-") == 0)
            return 1;
        if (what_flag(command[i], flag))
            return -1;
    }
    return i;
}

static void activate_flag(head_t *head, char flag[2])
{
    int len = 0;

    if (head->home)
        len = my_strlen(head->home);
    if (flag[0] == 'v')
        write(1,"0\t", 2);
    if (flag[1] == 'l') {
        write(1, &head->pwd->line[4], my_strlen(&head->pwd->line[4]));
    }
    if (flag[1] == 'n') {
        if (head->home)
            write(1, "~", 1);
        write(1, &head->pwd->line[4 + len],
                my_strlen(&head->pwd->line[4 + len]));
    }
    write(1, "\n", 1);
}

int change_dir(char **command_line, head_t *head, int *ret)
{
    int i = 1;
    int r = 0;
    char flag[2] = {'\0', '\0'};

    i = find_flag(command_line ,flag);
    if (i >= 1)
        r = find_cd_type(command_line, head, i);
    if (r == 0 && (flag[0] || flag[1])) {
        activate_flag(head, flag);
    }
    (*ret) = r;
    return r;
}
