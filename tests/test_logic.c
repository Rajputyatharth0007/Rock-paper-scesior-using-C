#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "game_logic.h"

static void test_nine_outcome_matrix(void) {
    printf("[TEST] Testing complete 9-outcome game rules matrix...\n");

    /* Draw outcomes */
    assert(determine_round_result(ROCK, ROCK) == RESULT_DRAW);
    assert(determine_round_result(PAPER, PAPER) == RESULT_DRAW);
    assert(determine_round_result(SCISSORS, SCISSORS) == RESULT_DRAW);

    /* Player win outcomes */
    assert(determine_round_result(ROCK, SCISSORS) == RESULT_PLAYER_WIN);
    assert(determine_round_result(PAPER, ROCK) == RESULT_PLAYER_WIN);
    assert(determine_round_result(SCISSORS, PAPER) == RESULT_PLAYER_WIN);

    /* Computer win outcomes */
    assert(determine_round_result(ROCK, PAPER) == RESULT_COMPUTER_WIN);
    assert(determine_round_result(PAPER, SCISSORS) == RESULT_COMPUTER_WIN);
    assert(determine_round_result(SCISSORS, ROCK) == RESULT_COMPUTER_WIN);

    printf("  -> PASS: All 9 move outcomes verified.\n");
}

static void test_invalid_choices(void) {
    printf("[TEST] Testing rejection of invalid choices...\n");

    assert(determine_round_result(-1, ROCK) == RESULT_INVALID);
    assert(determine_round_result(ROCK, -1) == RESULT_INVALID);
    assert(determine_round_result(3, PAPER) == RESULT_INVALID);
    assert(determine_round_result(PAPER, 99) == RESULT_INVALID);
    assert(determine_round_result(-5, 10) == RESULT_INVALID);

    assert(is_valid_choice(ROCK) == 1);
    assert(is_valid_choice(PAPER) == 1);
    assert(is_valid_choice(SCISSORS) == 1);
    assert(is_valid_choice(-1) == 0);
    assert(is_valid_choice(3) == 0);
    assert(is_valid_choice(100) == 0);

    printf("  -> PASS: Invalid choice boundary conditions verified.\n");
}

static void test_choice_to_string(void) {
    printf("[TEST] Testing choice_to_string mapping...\n");

    assert(strcmp(choice_to_string(ROCK), "Rock") == 0);
    assert(strcmp(choice_to_string(PAPER), "Paper") == 0);
    assert(strcmp(choice_to_string(SCISSORS), "Scissors") == 0);
    assert(strcmp(choice_to_string(-1), "Unknown") == 0);
    assert(strcmp(choice_to_string(3), "Unknown") == 0);

    printf("  -> PASS: String conversions verified.\n");
}

static void test_parse_strict_int(void) {
    printf("[TEST] Testing strict integer parsing and error detection...\n");
    long val = -1;

    /* Valid integers */
    assert(parse_strict_int("0", &val) == PARSE_OK && val == 0);
    assert(parse_strict_int("1", &val) == PARSE_OK && val == 1);
    assert(parse_strict_int("2", &val) == PARSE_OK && val == 2);
    assert(parse_strict_int("42", &val) == PARSE_OK && val == 42);
    assert(parse_strict_int("-5", &val) == PARSE_OK && val == -5);
    assert(parse_strict_int("+10", &val) == PARSE_OK && val == 10);

    /* Valid integers with surrounding whitespace */
    assert(parse_strict_int("   0   ", &val) == PARSE_OK && val == 0);
    assert(parse_strict_int("\t1\n", &val) == PARSE_OK && val == 1);
    assert(parse_strict_int("  2  ", &val) == PARSE_OK && val == 2);

    /* Trailing non-numeric characters (must be rejected) */
    assert(parse_strict_int("2abc", &val) == PARSE_INVALID);
    assert(parse_strict_int("0x10", &val) == PARSE_INVALID);
    assert(parse_strict_int("1.5", &val) == PARSE_INVALID);
    assert(parse_strict_int("1 2", &val) == PARSE_INVALID);

    /* Pure non-numeric strings */
    assert(parse_strict_int("abc", &val) == PARSE_INVALID);
    assert(parse_strict_int("rock", &val) == PARSE_INVALID);
    assert(parse_strict_int("--", &val) == PARSE_INVALID);
    assert(parse_strict_int("-", &val) == PARSE_INVALID);
    assert(parse_strict_int("+", &val) == PARSE_INVALID);

    /* Empty or whitespace-only strings */
    assert(parse_strict_int("", &val) == PARSE_EMPTY);
    assert(parse_strict_int("   ", &val) == PARSE_EMPTY);
    assert(parse_strict_int("\t\n", &val) == PARSE_EMPTY);

    /* Overflow and underflow */
    assert(parse_strict_int("99999999999999999999999999999999", &val) == PARSE_OUT_OF_RANGE);
    assert(parse_strict_int("-99999999999999999999999999999999", &val) == PARSE_OUT_OF_RANGE);

    /* NULL parameters */
    assert(parse_strict_int(NULL, &val) == PARSE_INVALID);
    assert(parse_strict_int("1", NULL) == PARSE_INVALID);

    printf("  -> PASS: Strict input validation and rejection verified.\n");
}

static void test_computer_choice_distribution(void) {
    printf("[TEST] Testing get_computer_choice random bounds...\n");
    srand(12345);

    int seen_rock = 0;
    int seen_paper = 0;
    int seen_scissors = 0;

    for (int i = 0; i < 500; i++) {
        int choice = get_computer_choice();
        assert(choice >= ROCK && choice <= SCISSORS);

        if (choice == ROCK) seen_rock = 1;
        if (choice == PAPER) seen_paper = 1;
        if (choice == SCISSORS) seen_scissors = 1;
    }

    assert(seen_rock && seen_paper && seen_scissors);
    printf("  -> PASS: Computer choices always stay within [0, 2].\n");
}

int main(void) {
    printf("=========================================\n");
    printf("   ROCK PAPER SCISSORS AUTOMATED TESTS   \n");
    printf("=========================================\n\n");

    test_nine_outcome_matrix();
    test_invalid_choices();
    test_choice_to_string();
    test_parse_strict_int();
    test_computer_choice_distribution();

    printf("\n=========================================\n");
    printf("   ALL AUTOMATED TESTS PASSED (100%%)    \n");
    printf("=========================================\n");
    return 0;
}
