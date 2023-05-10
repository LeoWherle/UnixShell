/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** prompt
*/

#include "errorh.h"

#ifndef PROMPT_H_
    #define PROMPT_H_

    #define MAX_INPUTLINE 4096

    #define TAB_SIZE(tab) (sizeof(tab) / sizeof(typeof(*tab)))

    typedef struct head head_t;
    typedef struct textfield_s {
        unsigned short bf_size;
        unsigned short cursor_pos;
        unsigned int history_pos;
        char buffer[MAX_INPUTLINE];
    } textfield_t;

    typedef struct chartype_s {
        char type;
        int (*handler)(struct textfield_s *field, head_t *head);
    } chartype_t;

    typedef struct escchartype_s {
        char type;
        int (*handler)(struct textfield_s *field, char seq[], head_t *head);
    } escchartype_t;

    typedef struct escchartypetype_s {
        char type;
        escchartype_t const *handler;
    } escchartypetype_t;

    /*pretty promt print*/
    int print_shell(void);

    /**
     * @brief function to read a line from stdin and handle special characters
     * (backspace, tabulation, escape_sequences, newline)
     *
     * @param output a pointer to a string that will be allocated and filled
     * @return int length of the string read or EOF if the end of file is
     * reached
     */
    int read_line(char **output, head_t *head);

    /**
     * @brief function to execute the right handler for the given character
     * ASCII code
     * @param field the textfield to handle
     * @param c the character to handle
     * @return int 1 if the character is a newline, 0 otherwise
     */
    int handle_char(textfield_t *field, char c, head_t *head);


    ///////////////////////// SPECIAL HANDLERS /////////////////////////
    /// these functions are called when the character is a special one ///
    /// (newline, tabulation, backspace, escape)                       ///
    /// the function returns 1 if the character is a newline, 0        ///
    /// otherwise                                                      ///
    /// the function takes a pointer to the textfield as parameter     ///
    /// they are used in the handle_char function as a callback        ///
    ///////////////////////// SPECIAL HANDLERS /////////////////////////

    /**
     * @brief function to handle the newline character
     *
     * @param field the textfield to handle
     * @return int 1 (always) because the character is a newline
     */
    int enter_key(textfield_t *field, head_t *head);

    //:TODO: implement tab_key
    int tab_key(textfield_t *field, head_t *head);

    /**
     * @brief function to delete the character before the cursor
     * @param field the textfield to handle
     * @return int 0
     */
    int backspace_key(textfield_t *field, head_t *head);
    /**
     * @brief function to handle the escape sequence characters
     * @param field the textfield to handle
     * @return int 0
     */
    int esc_key(textfield_t *field, head_t *head);

    ///////////////////////// ESCAPE HANDLERS /////////////////////////
    /// these functions are called when the character is an escape     ///
    /// sequence                                                       ///
    /// the function returns 1 if the character is a newline, 0        ///
    /// otherwise                                                      ///
    /// the function takes a pointer to the textfield as parameter     ///
    /// they are used in the esc_key function as a callback            ///
    ///////////////////////// ESCAPE HANDLERS /////////////////////////

    //:TODO: implement history
    int up_arrow(textfield_t *field, char seq[], head_t *head);
    int down_arrow(textfield_t *field, char seq[], head_t *head);

    /**
     * @brief function to move the cursor to the right
     * @param field the textfield to handle
     * @param seq the escape sequence
     * @return int 0
     */
    int right_arrow(textfield_t *field, char seq[], head_t *head);
    /**
     * @brief function to move the cursor to the left
     * @param field the textfield to handle
     * @param seq the escape sequence
     * @return int 0
     */
    int left_arrow(textfield_t *field, char seq[], head_t *head);
    /**
     * @brief function to delete the character under the cursor
     * @param field the textfield to handle
     * @param seq the escape sequence
     * @return int 0
     */
    int delete_key(textfield_t *field, char seq[], head_t *head);
    int ctrl_right_arrow(textfield_t *field, UNUSED char seq[],
    UNUSED head_t *head);
    int ctrl_left_arrow(textfield_t *field, UNUSED char seq[],
    UNUSED head_t *head);
#endif /* !PROMPT_H_ */
