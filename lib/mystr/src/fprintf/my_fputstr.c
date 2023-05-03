/*
** EPITECH PROJECT, 2023
** minishell2 [WSL: fedora]
** File description:
** my_fputstr
*/

#include <unistd.h>
#include "mystr.h"

static int my_fputstrlen(char const *str)
{
    int i = 0;

    if (!str)
        return 0;
    while (str[i] != '\0')
        i++;
    return i;
}

void my_fputstr(int fd, char const *str)
{
    write(fd, str, my_fputstrlen(str));
}
