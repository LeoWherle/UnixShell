/*
** EPITECH PROJECT, 2023
** my_str_copy_cat
** File description:
** copy and cat
*/

#include <stdbool.h>
#include <stdlib.h>
#include "mystr.h"

char *my_str_copy_cat(char *copy, char *cat)
{
    char *dest = NULL;

    if (!copy || !cat)
        return NULL;
    dest = malloc((my_strlen(copy) + my_strlen(cat) + 2) * sizeof(char));
    if (!dest)
        return NULL;
    my_strcpy(dest, copy);
    my_strcat(dest, cat);
    return dest;
}
