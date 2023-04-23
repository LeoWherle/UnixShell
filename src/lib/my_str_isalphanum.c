/*
** EPITECH PROJECT, 2022
** my_str_isalpha
** File description:
** return 1 if the string only contain string
*/

int my_str_isalphanum(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] < '0' || (str[i] > '9' && str[i] < 'A') ||
            (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z')
            return 0;
        i = i + 1;
    }
    return 1;
}
