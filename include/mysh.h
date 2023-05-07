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

    #include "errorh.h"
    #include "clist.h"
    #include "rcfile.h"
    #include "mystr.h"

    #define OPEN_E O_CREAT | O_WRONLY | O_TRUNC
    #define OPEN_B O_CREAT | O_WRONLY | O_APPEND
    #define E_REDIRECT "Ambiguous input redirect.\n"
    #define N_COMMAND "Invalid null command.\n"
    #define NO_NAME "Missing name for redirect.\n"

    #define MAX_BUFFER_SIZE 1024
    /*usefull for the prompt to get the current branch*/
    #define BRANCH_COMMAND "git rev-parse --abbrev-ref HEAD 2> /dev/null"

    typedef struct head head_t;
    typedef struct env env_t;
    typedef int pid_t;

    typedef struct env {
        char *line;
        struct env *next;
    } env_t;

    typedef struct builtin_cmd {
        char *name;
        int (*func)(char **, head_t *);
    } builtin_cmd_t;

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
    void create_rc_file(head_t *);
    int use_command(char **, head_t *);
    bool path_command(char **, head_t *, int *);
    bool exec_special_case(char **, head_t *, int *);
    char *change_command(char *, head_t *);
    int globbings_change_command(char ***);

    /*special_command*/
    int change_dir(char **, head_t *);
    int find_cd_type(char **, head_t *, int);
    int my_setenv(char **, head_t *);
    int my_unsetenv(char **, head_t *);
    int my_exit(char **, head_t *);
    int new_pwd(env_t *, head_t *);
    int alias_builtin(char **, head_t *);
    int change_alias(char **command, head_t *head);
    int my_echo(char **command_line, head_t *head);

    int separator_handler(char *command_line, head_t *head);


    /*free functions*/
    void free_alias(void *);
    bool create_head(head_t *head, char * const *e);
    void free_head(head_t *head);
    void list_end(void);

#endif /*MYSH_H*/
