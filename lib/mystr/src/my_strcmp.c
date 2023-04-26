/*
** EPITECH PROJECT, 2022
** my_strcmp
** File description:
** tell what chain is the biggest by adding the ascii valor
*/

int my_strcmp(char const *s1, char const *s2)
{
    int t = 0;

    while (s1[t] == s2[t] && s1[t] != '\0' && s2[t] != '\0'){
        t = t + 1;
    }
    if (s1[t] > s2[t]){
        return (1);
    } else if (s1[t] < s2[t]){
        return (-1);
    }
    return (0);
}
