/*
** EPITECH PROJECT, 2023
** minishell2 [WSL: fedora]
** File description:
** my_fputchar
*/

#include <unistd.h>

void my_fputchar(int fd, char c)
{
    write(fd, &c, 1);
}
