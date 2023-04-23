/*
** EPITECH PROJECT, 2022
** my_strncmp
** File description:
** strcmp but with an n in the middle
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int t = 0;

    while (s1[t] != '\0' && s2[t] != '\0' && s1[t] == s2[t] && t < n) {
        t = t + 1;
    }
    if (s1[t] > s2[t]){
        return (1);
    } else if (s1[t] < s2[t]){
        return (-1);
    }
    return (0);
}
