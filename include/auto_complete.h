/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** auto complete
*/

#include <stdbool.h>

#ifndef AUTO_COMPLETE_H
    #define AUTO_COMPLETE_H

    void print_fake_ls(char **file_list);
    char **get_file_list(char **file_list, char *path);
    void sort_files(char **file_list);
    char *get_command(char *field);
    void get_corresponding_files(char **file_list, char *field);
    bool is_in(char c, char *str);
    int get_file_nb(char *path);

#endif /* AUTO_COMPLETE_H */
