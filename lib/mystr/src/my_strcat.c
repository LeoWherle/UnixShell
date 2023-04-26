/*
** EPITECH PROJECT, 2022
** my_strcat
** File description:
** concatenates two strings
*/

#include "mystr.h"

char *my_strcat(char *dest, const char *src)
{
    int len = 0;
    int m = 0;

    if (!dest || !src)
        return dest;
    len = my_strlen(dest);
    for (m = 0 ; src[m] != '\0' ; m++){
        dest[len + m] = src[m];
    }
    dest[len + m] = '\0';
    return (dest);
}
