/*
** EPITECH PROJECT, 2022
** my_str_isnum
** File description:
** check if the string is composed of number
*/

int my_str_isnum(char const *str)
{
    int i = 0;

    for (i = i; str[i] == '-'; i++);
    for (i = i; str[i] != '\0'; i++)
        if (str[i] < 48 || str[i] > 57)
            return (0);
    return (1);
}
