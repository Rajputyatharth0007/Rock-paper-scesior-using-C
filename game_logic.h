#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stddef.h>

/* Constants representing game choices */
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

/* Constants representing round outcomes */
#define RESULT_DRAW 0
#define RESULT_PLAYER_WIN 1
#define RESULT_COMPUTER_WIN 2
#define RESULT_INVALID -1

/* Status codes for strict integer parsing */
typedef enum {
    PARSE_OK = 0,
    PARSE_EMPTY,
    PARSE_INVALID,
    PARSE_OUT_OF_RANGE
} ParseStatus;

/**
 * Validates whether a choice is within the allowed range [0, 2].
 * Returns 1 if valid, 0 otherwise.
 */
int is_valid_choice(int choice);

/**
 * Convert numerical choice to a human-readable string.
 * Returns "Rock", "Paper", "Scissors", or "Unknown".
 */
const char *choice_to_string(int choice);

/**
 * Determine the outcome of a round based on player and computer choices.
 * Returns:
 *   RESULT_DRAW (0)         - both picked the same valid choice
 *   RESULT_PLAYER_WIN (1)   - player wins
 *   RESULT_COMPUTER_WIN (2) - computer wins
 *   RESULT_INVALID (-1)     - player or computer choice is invalid
 */
int determine_round_result(int player_choice, int computer_choice);

/**
 * Strict integer parser using strtol.
 * Validates that the entire string (after trimming whitespace) is a valid integer.
 * Rejects "2abc", "1.5", "", "abc", and overflows/underflows.
 * Returns PARSE_OK on success and sets *out_val.
 */
ParseStatus parse_strict_int(const char *str, long *out_val);

/**
 * Reads a line of input from stdin into buffer.
 * Strips trailing newline if present.
 * If the input was longer than buffer, flushes the remainder of the line.
 * Returns 1 on success, 0 on EOF.
 */
int read_input_line(char *buffer, size_t size);

/**
 * Generate a pseudo-random choice for the computer (0: Rock, 1: Paper, 2: Scissors).
 */
int get_computer_choice(void);

#endif /* GAME_LOGIC_H */
