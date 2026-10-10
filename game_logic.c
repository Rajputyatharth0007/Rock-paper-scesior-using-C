#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

int is_valid_choice(int choice) {
    return (choice >= ROCK && choice <= SCISSORS);
}

const char *choice_to_string(int choice) {
    switch (choice) {
        case ROCK:
            return "Rock";
        case PAPER:
            return "Paper";
        case SCISSORS:
            return "Scissors";
        default:
            return "Unknown";
    }
}

int determine_round_result(int player_choice, int computer_choice) {
    if (!is_valid_choice(player_choice) || !is_valid_choice(computer_choice)) {
        return RESULT_INVALID;
    }

    if (player_choice == computer_choice) {
        return RESULT_DRAW;
    }

    if ((player_choice == ROCK && computer_choice == SCISSORS) ||
        (player_choice == PAPER && computer_choice == ROCK) ||
        (player_choice == SCISSORS && computer_choice == PAPER)) {
        return RESULT_PLAYER_WIN;
    }

    return RESULT_COMPUTER_WIN;
}

ParseStatus parse_strict_int(const char *str, long *out_val) {
    if (str == NULL || out_val == NULL) {
        return PARSE_INVALID;
    }

    const char *p = str;
    while (*p != '\0' && isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '\0') {
        return PARSE_EMPTY;
    }

    errno = 0;
    char *endptr = NULL;
    long val = strtol(p, &endptr, 10);

    if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        return PARSE_OUT_OF_RANGE;
    }

    if (endptr == p) {
        return PARSE_INVALID;
    }

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return PARSE_INVALID;
    }

    *out_val = val;
    return PARSE_OK;
}

int read_input_line(char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0; /* EOF or read error */
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        /* Line was longer than buffer, flush remainder of line from stdin */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* discard characters */
        }
    }

    return 1;
}

int get_computer_choice(void) {
    return rand() % 3;
}
