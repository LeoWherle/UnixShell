/*
** EPITECH PROJECT, 2023
** str_to_word_array
** File description:
** take a string and turns it into an array of word
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static int get_word_len(char const *str, char sep)
{
    int index = 0;

    while (str[index] != sep && str[index] != '\t' && str[index] != '\0') {
        index++;
    }
    return index;
}

static void copy_word(char const *src, char *dest, char sep)
{
    int i = 0;

    for (i = 0; src[i] != sep && src[i] != '\t' && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int my_strlen(char const *str)
{
    int index = 0;

    if (!str)
        return index;
    while (str[index] != '\0'){
        index++;
    }
    return index;
}

static int find_nb_word(char const *str, char sep)
{
    int len = 0;
    int nb_word = 0;
    int i = 0;

    len = my_strlen(str);
    while (i < len) {
        for (i = i; i < len && (str[i] == sep || str[i] == '\t'); i++);
        if (i < len && str[i] != '\0')
            nb_word++;
        for (i = i; i < len && str[i] != sep && str[i] != '\t'; i++);
    }
    return nb_word;
}

char **my_str_to_word_array(char const *str, char sep)
{
    char **word_array = NULL;
    int nb_word = 1;
    int word_len = 0;
    int index = 0;

    nb_word = find_nb_word(str, sep);
    if (nb_word == 0)
        return NULL;
    word_array = malloc((nb_word + 1) * sizeof(char *));
    for (int i = 0; i < nb_word; i++) {
        for (index = index; str[index] == sep || str[index] == '\t'; index++);
        word_len = get_word_len(&str[index], sep);
        word_array[i] = malloc((word_len + 1) * sizeof(char));
        copy_word(&str[index], word_array[i], sep);
        index += word_len + 1;
    }
    word_array[nb_word] = NULL;
    return word_array;
}
