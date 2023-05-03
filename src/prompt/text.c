#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

// Function prototypes
void enable_raw_mode(struct termios *orig_termios);
void disable_raw_mode(struct termios *orig_termios);
void process_keypress(char *buffer, int *cursor_pos, const char *prompt);

int text(char **output) {
    struct termios orig_termios;
    char buffer[MAX_INPUT_SIZE] = {0};
    int cursor_pos = 0;
    const char *prompt = "Your input: ";

    enable_raw_mode(&orig_termios);

    printf("%s", prompt);
    while (1) {
        process_keypress(buffer, &cursor_pos, prompt);
    }
    disable_raw_mode(&orig_termios);
    return 0;
}

void enable_raw_mode(struct termios *orig_termios) {
    tcgetattr(STDIN_FILENO, orig_termios);

    struct termios raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios *orig_termios) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

void process_keypress(char *buffer, int *cursor_pos, const char *prompt) {
    char c = getchar();

    if (c == 27) { // Escape character
        char seq[3];
        if (getchar() == '[') {
            seq[0] = getchar();
            if (seq[0] >= '0' && seq[0] <= '9') {
                seq[1] = getchar();
            }
        }

        switch (seq[0]) {
            case 'A': // Up arrow
                break;
            case 'B': // Down arrow
                break;
            case 'C': // Right arrow
                if (*cursor_pos < strlen(buffer)) {
                    putchar(c);
                    putchar('[');
                    putchar(seq[0]);
                    (*cursor_pos)++;
                }
                break;
            case 'D': // Left arrow
                if (*cursor_pos > 0) {
                    putchar(c);
                    putchar('[');
                    putchar(seq[0]);
                    (*cursor_pos)--;
                }
                break;
        }
    } else if (c == 127) { // Backspace
        if (*cursor_pos > 0) {
            memmove(buffer + *cursor_pos - 1, buffer + *cursor_pos, strlen(buffer) - *cursor_pos + 1);
            (*cursor_pos)--;
        }
    } else if (c == '\n') { // Enter
        putchar('\n');
        printf("Your entry: %s\n", buffer);
        memset(buffer, 0, MAX_INPUT_SIZE);
        *cursor_pos = 0;
    } else {
        memmove(buffer + *cursor_pos + 1, buffer + *cursor_pos, strlen(buffer) - *cursor_pos);
        buffer[*cursor_pos] = c;
        (*cursor_pos)++;
    }

    // Clear the line, print the prompt, and rewrite the buffer
    printf("\033[2K\r%s%s", prompt, buffer);

    // Move the cursor back to the correct position
    printf("\033[%dG", (int)strlen(prompt) + *cursor_pos + 1);
}
