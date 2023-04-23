/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** ast
*/

#include "mysh.h"

#ifndef AST_H
    #define AST_H

    enum type {
        COMMAND,
        SEP,
    };

    typedef struct ast {
        enum type type;
        void *data;
        struct ast *left;
        struct ast *right;
    } ast_t;

    typedef struct sep {
        char *sep;
        int (*ptr)(ast_t *, int, int, head_t *);
    } sep_t;

    ast_t *build_ast(char *text, int i);
    void free_ast(ast_t *ast);

    int use_din(ast_t *node, int to_read, int to_write, head_t *head);
    int use_dout(ast_t *node, int to_read, int to_write, head_t *head);
    int use_in(ast_t *node, int to_read, int to_write, head_t *head);
    int use_out(ast_t *node, int to_read, int to_write, head_t *head);
    int use_pipe(ast_t *node, int to_read, int to_write, head_t *head);
    int use_or(ast_t *node, int to_read, int to_write, head_t *head);
    int use_and(ast_t *node, int to_read, int to_write, head_t *head);
    int use_semi_colon(ast_t *node, int to_read, int to_write, head_t *head);
    int execute(ast_t *node, int to_read, int to_write, head_t *head);

#endif /*AST_H*/
