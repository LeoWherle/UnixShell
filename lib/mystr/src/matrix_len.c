/*
** EPITECH PROJECT, 2023
** matrix_len
** File description:
** return the len of a matrix
*/

#include <stddef.h>
#include <stdlib.h>

int matrix_len(char **m)
{
    int i = 0;

    if (!m)
        return 0;
    while (m[i] != NULL)
        i++;
    return i;
}

void free_matrix(char **matrix)
{
    if (!matrix)
        return;
    for (int i = 0; matrix[i] != NULL; i++)
        free(matrix[i]);
    free(matrix);
}
