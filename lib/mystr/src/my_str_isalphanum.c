/*
** EPITECH PROJECT, 2022
** my_str_isalpha
** File description:
** return 1 if the string only contain string
*/

#include "mystr.h"

int my_str_isalphanum(char const *str)
{
    while (*str != '\0') {
        if (!IS_NUM(*str) && !IS_LOWER(*str) && !IS_UPPER(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}
