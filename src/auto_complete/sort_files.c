/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** sort files for auto complete
*/

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "auto_complete.h"

bool is_in(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return (true);
    }
    return (false);
}

static void bubble_sort_files(char **file_list, int i, int j)
{
    char *tmp = NULL;
    int k = 0;
    char *str1 = NULL;
    char *str2 = NULL;

    str1 = strdup(file_list[i]);
    str2 = strdup(file_list[j]);
    for (; str1[k]; k++)
        str1[k] = tolower(str1[k]);
    for (k = 0; str2[k]; k++)
        str2[k] = tolower(str2[k]);
    if (strcmp(str1, str2) > 0) {
        tmp = file_list[i];
        file_list[i] = file_list[j];
        file_list[j] = tmp;
    }
    free(str1);
    free(str2);
}

void sort_files(char **file_list)
{
    int i = 0;
    int j = 0;

    for (i = 0; file_list[i]; i++) {
        for (j = i + 1; file_list[j]; j++) {
            bubble_sort_files(file_list, i, j);
        }
    }
}
