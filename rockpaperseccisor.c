#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_logic.h"

/**
 * Safely prompt the user for the number of rounds.
 * Returns a positive integer, or -1 if EOF occurs.
 */
int get_positive_rounds(void) {
    char buffer[64];
    long rounds = 0;

    while (1) {
        printf("Enter the number of rounds: ");
        if (!read_input_line(buffer, sizeof(buffer))) {
            return -1;
        }

        ParseStatus status = parse_strict_int(buffer, &rounds);
        if (status == PARSE_EMPTY) {
            printf("Input cannot be empty. Please enter a positive integer.\n");
            continue;
        }

        if (status == PARSE_OUT_OF_RANGE) {
            printf("Value is out of valid integer range. Please try again.\n");
            continue;
        }

        if (status != PARSE_OK) {
            printf("Invalid input. Please enter a valid positive integer.\n");
            continue;
        }

        if (rounds <= 0) {
            printf("Number of rounds must be greater than 0. Please try again.\n");
            continue;
        }

        return (int)rounds;
    }
}

/**
 * Safely prompt the player for a choice: Rock(0), Paper(1), or Scissors(2).
 * Returns the choice (0, 1, or 2), or -1 if EOF occurs.
 */
int get_player_choice(void) {
    char buffer[64];
    long choice = -1;

    while (1) {
        printf("Enter your choice - Rock(0), Paper(1), Scissors(2): ");
        if (!read_input_line(buffer, sizeof(buffer))) {
            return -1;
        }

        ParseStatus status = parse_strict_int(buffer, &choice);
        if (status == PARSE_EMPTY) {
            printf("Input cannot be empty. Please enter 0, 1, or 2.\n");
            continue;
        }

        if (status != PARSE_OK || !is_valid_choice((int)choice)) {
            printf("Invalid choice. Please enter 0, 1, or 2.\n");
            continue;
        }

        return (int)choice;
    }
}

/**
 * Display final game summary and overall winner.
 * Distinguishes between normally completed and interrupted matches.
 */
void display_summary(int player_wins, int computer_wins, int ties,
                     int completed_rounds, int total_rounds, int is_interrupted) {
    if (is_interrupted) {
        printf("\n----- MATCH INTERRUPTED -----\n");
        printf("Notice: The match ended early due to input termination.\n");
        printf("------ Completed rounds: %d of %d ------\n", completed_rounds, total_rounds);
    } else {
        printf("\n----- GAME OVER -----\n");
        printf("------ Completed rounds: %d of %d ------\n", completed_rounds, total_rounds);
    }

    printf("------ Total number of wins by player: %d ------\n", player_wins);
    printf("------ Total number of wins by computer: %d ------\n", computer_wins);
    printf("------ Total number of tied rounds: %d ------\n", ties);

    if (completed_rounds == 0) {
        printf("======= No rounds were completed. =======\n");
    } else if (player_wins > computer_wins) {
        if (is_interrupted) {
            printf("===== Current leader is player by %d round(s)! =====\n", player_wins - computer_wins);
        } else {
            printf("===== Overall winner is player by %d round(s)! =====\n", player_wins - computer_wins);
        }
    } else if (computer_wins > player_wins) {
        if (is_interrupted) {
            printf("======= Current leader is computer by %d round(s)! =======\n", computer_wins - player_wins);
        } else {
            printf("======= Overall winner is computer by %d round(s)! =======\n", computer_wins - player_wins);
        }
    } else {
        if (is_interrupted) {
            printf("======= Current standings: Tie! =======\n");
        } else {
            printf("======= Overall match is a Tie! =======\n");
        }
    }
}

int main(void) {
    /* Seed the pseudo-random number generator once per program run */
    srand((unsigned int)time(NULL));

    int player_wins = 0;
    int computer_wins = 0;
    int ties = 0;
    int completed_rounds = 0;
    int is_interrupted = 0;

    printf("-----! HELLO PLAYER !-----\n");
    printf("------ Welcome to Game Rock(0), Paper(1), Scissors(2) -----\n");

    int total_rounds = get_positive_rounds();
    if (total_rounds == -1) {
        printf("\nInput terminated. Exiting game.\n");
        return 0;
    }

    for (int round_num = 1; round_num <= total_rounds; round_num++) {
        printf("\n---- Round %d of %d start -----\n", round_num, total_rounds);

        int player_choice = get_player_choice();
        if (player_choice == -1) {
            printf("\nInput terminated during round %d. Ending match early.\n", round_num);
            is_interrupted = 1;
            break;
        }

        int computer_choice = get_computer_choice();

        printf("Player choice: %s\n", choice_to_string(player_choice));
        printf("Computer Choice is %s\n", choice_to_string(computer_choice));

        int outcome = determine_round_result(player_choice, computer_choice);

        switch (outcome) {
            case RESULT_DRAW:
                printf("Match is tied\n");
                ties++;
                break;
            case RESULT_PLAYER_WIN:
                printf("Match is win by Player\n");
                player_wins++;
                break;
            case RESULT_COMPUTER_WIN:
                printf("Match is win by Computer\n");
                computer_wins++;
                break;
            default:
                break;
        }

        completed_rounds++;
    }

    display_summary(player_wins, computer_wins, ties,
                    completed_rounds, total_rounds, is_interrupted);

    return 0;
}
