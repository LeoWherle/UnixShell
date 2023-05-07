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
    #define WRITE_BAD_PLACE write(2, "Badly placed ()'s.\n", 20)

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
        void *ptr;
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
    ast_t *par_open(ast_t *node);
    ast_t *par_close(ast_t *node);

    bool check_tree(ast_t *node, int i);
    bool check_par(ast_t *node, int *open, int *close);

#endif /*AST_H*/
