/*
** EPITECH PROJECT, 2023
** minishell2 [WSL: fedora]
** File description:
** my_putnbr
*/

#include <unistd.h>

void my_fputnbr(int fd, int val)
{
    char c;

    if (val < 0) {
        write(fd, "-", 1);
        val = -val;
    }
    if (val / 10) {
        my_fputnbr(fd, val / 10);
    }
    c = val % 10 + '0';
    write(fd, &c, 1);
}
