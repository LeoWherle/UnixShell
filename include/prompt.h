/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** prompt
*/

#ifndef PROMPT_H_
    #define PROMPT_H_

    #define MAX_INPUTLINE 4096

    #define TAB_SIZE(tab) (sizeof(tab) / sizeof(typeof(*tab)))

    typedef struct textfield_s {
        unsigned short bf_size;
        unsigned short cursor_pos;
        char buffer[MAX_INPUTLINE];
    } textfield_t;

    typedef struct chartype_s {
        char type;
        int (*handler)(struct textfield_s *field);
    } chartype_t;

    typedef struct escchartype_s {
        char type;
        int (*handler)(struct textfield_s *field, char seq[]);
    } escchartype_t;

    void terminal_loop(textfield_t *field);

    void newline(textfield_t *field);
    void tabulation(textfield_t *field);
    void backspace(textfield_t *field);
    void escape(textfield_t *field);
    void standart_char(textfield_t *field);


    /*pretty promt print*/
    int print_shell(void);

#endif /* !PROMPT_H_ */
