/*
** EPITECH PROJECT, 2023
** matrix_len
** File description:
** return the len of a matrix
*/

#include <stddef.h>

int matrix_len(char **m)
{
    int i = 0;

    if (!m)
        return 0;
    while (m[i] != NULL)
        i++;
    return i;
}
