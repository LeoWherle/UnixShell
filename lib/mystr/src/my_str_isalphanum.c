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
        if (str[0] < '0' || (str[0] > '9' && str[0] < 'A') ||
            (str[0] > 'Z' && str[0] < 'a') || str[0] > 'z') {
            return 0;
        }
        str++;
    }
    return 1;
}
