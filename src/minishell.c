/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** main
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mysh.h"
#include "prompt.h"
#include "rcfile.h"

char **find_path(env_t *env)
{
    char **e_path = NULL;
    int len = 0;

    for (env = env; env->line != NULL; env = env->next)
        if (my_strncmp(env->line, "PATH=", 4) == 0)
            break;
    if (env->line) {
        len = my_strlen(&env->line[5]);
        if (len >= 1)
            e_path = my_str_to_word_array(&env->line[5], ':');
    }
    return e_path;
}

void free_matrix(char **matrix)
{
    if (!matrix)
        return;
    for (int i = 0; matrix[i] != NULL; i++)
        free(matrix[i]);
    free(matrix);
}

void remove_line_break(char *src)
{
    int i = 0;

    for (i = 0; src[i] != '\0' && src[i] != '\n'; i++);
    src[i] = '\0';
}

static int loop(int state, head_t *head)
{
    char *read = NULL;

    if (state)
        print_shell();
    while (head->keep && read_line(&read) != EOF) {
        remove_line_break(read);
        if (read[0] != '\0')
            head->lr = separator_handler(read, head);
        if (state && head->keep)
            print_shell();
        free(read);
        read = NULL;
    }
    free(read);
    return head->lr;
}

int main(int ac, char const**, char * const *e)
{
    head_t head = {0};
    int state = 0;
    int r = 0;

    if (ac != 1 || !e[0])
        return 84;
    state = isatty(0);
    if (!create_head(&head, e))
        return 84;
    r = loop(state, &head);
    free_head(&head);
    list_end();
    if (state)
        write(1, "exit\n", 5);
    return r;
}
