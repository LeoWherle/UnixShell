/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** ast
*/

#include <unistd.h>
#include "mysh.h"

#ifndef AST_H
    #define AST_H

    #define NB_SEP 10
    #define WRITE_NULL_R write(2, "Missing name for redirect.\n", 27)
    #define WRITE_NULL_S write(2, "Invalid null command.\n", 22)
    #define WRITE_AMB_R write(2, "Ambiguous output redirect.\n", 27)
    #define WRITE_MUCH_OPEN write(2, "Too many ('s.\n", 14)
    #define WRITE_MUCH_CLOSE write(2, "Too many )'s.\n", 14)

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

    int use_in(ast_t *node, UNUSED int to_read, int to_write, head_t *head);
    int use_out(ast_t *node, int to_read, UNUSED int to_write, head_t *head);
    int use_dout(ast_t *node, int to_read, UNUSED int to_write, head_t *head);
    int use_din(ast_t *node, UNUSED int to_read, int to_write, head_t *head);
    int use_pipe(ast_t *node, int to_read, int to_write, head_t *head);
    int use_or(ast_t *node, int to_read, int to_write, head_t *head);
    int use_and(ast_t *node, int to_read, int to_write, head_t *head);
    int use_semi_colon(ast_t *node, int to_read, int to_write, head_t *head);
    int execute(ast_t *node, int to_read, int to_write, head_t *head);
    int par_open(ast_t *node, int to_read, int to_write, head_t *head);
    int par_close(ast_t *node, int to_read, int to_write, head_t *head);

    bool check_tree(ast_t *node, int i);

#endif /*AST_H*/
