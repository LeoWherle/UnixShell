/*
** EPITECH PROJECT, 2022
** my_str_isalpha
** File description:
** return 1 if the string only contain string
*/

#include "mystr.h"

int my_str_isalphanum(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (IS_NUM(str[i]) || IS_LOWER(str[i]) || IS_UPPER(str[i])) {
            return 0;
        }
        i = i + 1;
    }
    return 1;
}
