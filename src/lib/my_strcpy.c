/*
** EPITECH PROJECT, 2022
** my_strcpy
** File description:
** copies a string into another
*/

char *my_strcpy(char *dest, char const *src)
{
    int c = 0;

    if (!dest || !src)
        return dest;
    while (src[c] != '\0'){
        dest[c] = src[c];
        c = c + 1;
    }
    dest[c] = '\0';
    return (dest);
}
