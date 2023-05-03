/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history builtin
*/

#include <unistd.h>
#include <stdbool.h>
#include "mysh.h"
#include "history.h"
#include "mystr.h"

static bool add_flag(char *command, h_flag_t *flag)
{
    bool keep = true;

    for (int i = 1; command[i] != '\0' && keep; i++) {
        keep = true;
        if (command[i] == 'T')
            flag->horodates = true;
        if (command[i] == 'h')
            flag->simple = true;
        if (command[i] == 'r')
            flag->reverse = true;
        if (command[i] == 'c')
            flag->clear = true;
        if (command[i] != 'T' && command[i] != 'h' && 
            command[i] != 'r' && command[i] == 'c')
            keep = false;
    }
    return keep;
}

static bool find_flag(char **command, h_flag_t *flag)
{
    bool r = true;

    for (int i = 1; command[i] && r; i++) {
        if (command[i][0] == '-') {
            r = add_flag(command[i], flag);
        }
    }
    return r;
}

static int find_n(char **command)
{
    for (int i = 0; command[i]; i++) {
        if (my_str_isnum(command[i]) == 1)
            return my_getnbr(command[i]);
        if (command[i][0] != '-')
            return -1;
    }
    return 100;
}

int my_history(char **command, head_t *head, int *return_value)
{
    int n = 0;
    h_flag_t flag = {false};

    if (matrix_len(command) > 2)
        return 1;
    if (!find_flag(command, &flag)) {
        write(2, "Usage: history [-chrT] [# number of events].\n", 45);
        return 1;
    }
    n = find_n(command);
    if (n == -1) {
        write(2, "history: Badly formed number.\n", 30);
        return 1;
    }
    print_history(head->history, n, &flag);
    return 1;
}
