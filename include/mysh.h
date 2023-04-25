/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** all minishell related things
*/

#include <fcntl.h>
#include <stdbool.h>

#ifndef MYSH_H
    #define MYSH_H

    #include "errorhandling.h"
    #include "clist.h"

    #define OPEN_E O_CREAT | O_WRONLY | O_TRUNC
    #define OPEN_B O_CREAT | O_WRONLY | O_APPEND
    #define E_REDIRECT "Ambiguous input redirect.\n"
    #define N_COMMAND "Invalid null command.\n"
    #define NO_NAME "Missing name for redirect.\n"

    typedef struct env {
        char *line;
        struct env *next;
    } env_t;

    typedef struct head {
        env_t *first;
        env_t *pwd;
        env_t *oldpwd;
        list_t *alias;
        list_t *history;
        list_t *job_control;
        char *home;
        char *old;
        char **path;
        int size;
        bool keep;
        int lr;
        int stdin_copy;
        int stdout_copy;
    } head_t;

    /*lib*/
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

    /*env*/
    env_t *add_env(char const *);
    void make_env(char * const *, head_t *);
    void free_env(env_t *);
    void restore_env(head_t *);
    char **restore_path(void);
    char **find_path(env_t *);
    env_t *find_env(env_t *, char *);
    int my_env(char **, head_t *);

    /*command_gestion*/
    int use_command(char **, head_t *);
    int path_command(char **, head_t *);

    /*special_command*/
    int change_dir(char **, head_t *);
    int find_cd_type(char **, head_t *, int);
    int my_setenv(char **, head_t *);
    int my_unsetenv(char **, head_t *);
    void my_exit(char **, head_t *, int *);
    int new_pwd(env_t *, head_t *);

    int separator_handler(char *command_line, head_t *head);

#endif /*MYSH_H*/
