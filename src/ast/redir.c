/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** redir
*/

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "mysh.h"
#include "errorhandling.h"

int use_in(ast_t *node, UNUSED int to_read, int to_write, head_t *head)
{
    int fd = 0;
    char **in = NULL;

    in = node->right->data;
    fd = open(in[0], O_RDONLY);
    return execute(node->left, fd, to_write, head);
}

int use_out(ast_t *node, int to_read, UNUSED int to_write, head_t *head)
{
    int fd = 0;
    char **in = NULL;

    in = node->right->data;
    fd = open(in[0], OPEN_E, 0664);
    return execute(node->left, to_read, fd, head);
}

int use_dout(ast_t *node, int to_read, UNUSED int to_write, head_t *head)
{
    int fd = 0;
    char **in = NULL;

    in = node->right->data;
    fd = open(in[0], OPEN_B, 0664);
    return execute(node->left, to_read, fd, head);
}

int use_din(ast_t *node, UNUSED int to_read, int to_write, head_t *head)
{
    int pfd[2] = {0};
    char *line = NULL;
    size_t r = 0;
    char **key = NULL;
    int len = 0;

    pipe(pfd);
    key = node->right->data;
    len = strlen(key[0]);
    key[0][len] = '\n';
    write(1, "? ", 2);
    while (getline(&line, &r, stdin) != EOF && strncmp(key[0], line, len)) {
        write(1, "? ", 2);
        write(pfd[1], line, strlen(line));
    }
    close(pfd[1]);
    return execute(node->left, pfd[0], to_write, head);
}
