/*
** EPITECH PROJECT, 2022
** my_str_isnum
** File description:
** check if the string is composed of number
*/

#include "mystr.h"

int my_str_isnum(char const *str)
{
    int i = 0;

    for (i = i; str[i] == '-'; i++);
    for (i = i; str[i] != '\0'; i++)
        if (IS_NUM(str[i]))
            return (0);
    return (1);
}
