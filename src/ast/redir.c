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
#include <stdlib.h>
#include "ast.h"
#include "mysh.h"
#include "errorh.h"

void order_redir(ast_t *command, ast_t *redir)
{
    int command_len = 0;
    int redir_len = 0;
    int i = 0;
    int j = 1;
    char **c_text = command->data;
    char **r_text = redir->data;
    char **new_text = NULL;

    command_len = matrix_len(c_text);
    redir_len = matrix_len(r_text);
    if (redir_len == 1) return;
    new_text = malloc((command_len + redir_len) * sizeof(char *));
    for (; c_text && c_text[i]; i++)
        new_text[i] = c_text[i];
    for (; r_text[j]; j++) {
        new_text[i + j - 1] = r_text[j];
        r_text[j] = NULL;
    }
    new_text[i + j - 1] = NULL;
    free(c_text);
    command->data = new_text;
}

int use_in(ast_t *node, UNUSED int to_read, int to_write, head_t *head)
{
    int fd = 0;
    char **in = NULL;

    order_redir(node->left, node->right);
    in = node->right->data;
    fd = open(in[0], O_RDONLY);
    return execute(node->left, fd, to_write, head);
}

int use_out(ast_t *node, int to_read, UNUSED int to_write, head_t *head)
{
    int fd = 0;
    char **out = NULL;

    order_redir(node->left, node->right);
    out = node->right->data;
    fd = open(out[0], OPEN_E, 0664);
    return execute(node->left, to_read, fd, head);
}

int use_dout(ast_t *node, int to_read, UNUSED int to_write, head_t *head)
{
    int fd = 0;
    char **out = NULL;

    order_redir(node->left, node->right);
    out = node->right->data;
    fd = open(out[0], OPEN_B, 0664);
    return execute(node->left, to_read, fd, head);
}

int use_din(ast_t *node, UNUSED int to_read, int to_write, head_t *head)
{
    int pfd[2] = {0};
    char *line = NULL;
    size_t r = 0;
    char **key = NULL;
    int len = 0;

    order_redir(node->left, node->right);
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
