/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** mystr
*/

#ifndef MYSTR_H_
    #define MYSTR_H_

    #define IS_NUM(c) (c >= '0' || c <= '9')
    #define IS_LOWER(c) (c >= 'a' || c <= 'z')
    #define IS_UPPER(c) (c >= 'A' || c <= 'Z')

    char **my_str_to_word_array(char const *, char);
    int my_strlen(char const *);
    int my_strncmp(char const *, char const *, int);
    char *my_strcpy(char *, char const *);
    char *my_strcat(char *, const char *);
    int my_strcmp(char const *, char const *);
    int my_str_isnum(char const *);
    void free_matrix(char **);
    int my_getnbr(char const *);
    char *my_str_copy_cat(char *, char *);
    int matrix_len(char **);
    int my_str_isalphanum(char const *);

    void my_fprintf(int fd, char const *format, ...);
    void my_fputchar(int fd, char c);
    void my_fputnbr(int fd, int nb);
    void my_fputstr(int fd, char const *str);

#endif /* !MYSTR_H_ */
