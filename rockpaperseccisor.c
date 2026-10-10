#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants representing game choices */
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

/* Constants representing round outcomes */
#define RESULT_DRAW 0
#define RESULT_PLAYER_WIN 1
#define RESULT_COMPUTER_WIN 2

/**
 * Clear remaining characters from stdin to prevent infinite loops on invalid input.
 */
void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Discard characters until newline or EOF */
    }
}

/**
 * Convert numerical choice to a human-readable string.
 */
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

/**
 * Generate a random choice for the computer (0: Rock, 1: Paper, 2: Scissors).
 */
int get_computer_choice(void) {
    return rand() % 3;
}

/**
 * Determine the outcome of a round based on player and computer choices.
 * Returns:
 *   RESULT_DRAW (0)         - both picked the same choice
 *   RESULT_PLAYER_WIN (1)   - player wins
 *   RESULT_COMPUTER_WIN (2) - computer wins
 */
int determine_round_result(int player_choice, int computer_choice) {
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

/**
 * Safely prompt the user for the number of rounds.
 * Returns a positive integer, or -1 if EOF / input failure occurred.
 */
int get_positive_rounds(void) {
    int rounds = 0;
    while (1) {
        printf("Enter the number of rounds: ");
        int status = scanf("%d", &rounds);

        if (status == EOF) {
            return -1;
        }

        if (status != 1) {
            printf("Invalid input. Please enter a valid positive integer.\n");
            clear_input_buffer();
            continue;
        }

        clear_input_buffer();

        if (rounds <= 0) {
            printf("Number of rounds must be greater than 0. Please try again.\n");
            continue;
        }

        return rounds;
    }
}

/**
 * Safely prompt the player for a choice: Rock(0), Paper(1), or Scissors(2).
 * Returns the choice (0, 1, or 2), or -1 on EOF.
 */
int get_player_choice(void) {
    int choice = -1;
    while (1) {
        printf("Enter your choice - Rock(0), Paper(1), Scissors(2): ");
        int status = scanf("%d", &choice);

        if (status == EOF) {
            return -1;
        }

        if (status != 1) {
            printf("Invalid choice. Please enter 0, 1, or 2.\n");
            clear_input_buffer();
            continue;
        }

        clear_input_buffer();

        if (choice < 0 || choice > 2) {
            printf("Invalid choice. Please enter 0, 1, or 2.\n");
            continue;
        }

        return choice;
    }
}

/**
 * Display final game summary and overall winner.
 */
void display_summary(int player_wins, int computer_wins, int ties) {
    printf("\n----- GAME OVER -----\n");
    printf("------ Total number of wins by player: %d ------\n", player_wins);
    printf("------ Total number of wins by computer: %d ------\n", computer_wins);
    printf("------ Total number of tied rounds: %d ------\n", ties);

    if (player_wins > computer_wins) {
        printf("===== Overall winner is player by %d round(s)! =====\n", player_wins - computer_wins);
    } else if (computer_wins > player_wins) {
        printf("======= Overall winner is computer by %d round(s)! =======\n", computer_wins - player_wins);
    } else {
        printf("======= Overall match is a Tie! =======\n");
    }
}

int main(void) {
    /* Seed the pseudo-random number generator with the current time */
    srand((unsigned int)time(NULL));

    int player_wins = 0;
    int computer_wins = 0;
    int ties = 0;

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
            printf("\nInput terminated during round %d. Ending game early.\n", round_num);
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
    }

    display_summary(player_wins, computer_wins, ties);

    return 0;
}
