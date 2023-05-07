/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history parse
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "clist.h"
#include "history.h"
#include "mysh.h"

static int remake_str(char **d_command, char *match, int i, int j)
{
    char *new = NULL;

    if (!match) return 0;
    new = malloc((strlen(d_command[i]) - strlen(&d_command[i][j]) +
                    strlen(match) + 1) * sizeof(char));
    ASSERT_MALLOC(new, -1);
    new[0] = '\0';
    strncpy(new, d_command[i], j);
    new[j] = '\0';
    strcat(new, match);
    free(d_command[i]);
    d_command[i] = new;
    return 1;
}

static int last_command(char **d_command, int i, list_t *history)
{
    char *new = NULL;
    history_t *line = NULL;
    line = (history->tail) ? history->tail->data : NULL;
    for (int j = 0; d_command[i][j] != '\0' && line; j++) {
        if (strncmp(&d_command[i][j], "!!", 2) == 0) {
            new = malloc((strlen(d_command[i]) +
                strlen(line->command) - 1) * sizeof(char));
            ASSERT_MALLOC(new, -1);
            new[0] = '\0';
            strncpy(new, d_command[i], j);
            new[j] = '\0';
            strcat(new, line->command);
            strcat(new, &d_command[i][j + 2]);
            free(d_command[i]);
            d_command[i] = new;
            return 1;
        }
        if (d_command[i][j] == '!' && d_command[i][j + 1] != '!') return 0;
    }
    return 0;
}

static int recall(char **d_command, int i, list_t *history, bool *error)
{
    char *match = NULL;
    bool rec = false;
    int j = 0;
    int r = 0;

    r = last_command(d_command, i, history);
    if (r == -1)
        return -1;
    for (j = 0; d_command[i][j + 1] != '\0' && !rec; j++) {
        if (d_command[i][j] == '!') {
            match = find_com_in_history(history, &d_command[i][j + 1]);
            r = remake_str(d_command, match, i, j);
            rec = true;
        }
    }
    if (rec && r == 0)
        recall_error(d_command, i, j, error);
    return r;
}

static char *check_recall(char **d_command, list_t *history, bool *error)
{
    char *new = NULL;
    int len = 0;
    int r = 0;
    int hold = 0;
    for (int i = 0; d_command[i]; i++) {
        hold = recall(d_command, i, history, error);
        if (hold == 1) r = hold;
        if (hold == -1) return NULL;
    }
    for (int j = 0; d_command[j]; j++)
        len += strlen(d_command[j]);
    new = malloc((len + matrix_len(d_command) + 1) * sizeof(char));
    ASSERT_MALLOC(new, NULL);
    strcpy(new, d_command[0]);
    for (int i = 1; d_command[i]; i++) {
        strcat(new, " ");
        strcat(new, d_command[i]);
    }
    if (r == 1) printf("%s\n", new);
    return new;
}

char *pick_history(char *command_line, head_t *head)
{
    char **d_command = NULL;
    char *new_command = NULL;
    bool error = false;

    d_command = my_str_to_word_array(command_line, ' ');
    new_command = check_recall(d_command, head->history, &error);
    free_matrix(d_command);
    if (error) {
        head->lr = 1;
        return NULL;
    }
    return add_to_history(new_command, head);
}
