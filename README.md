# Rock Paper Scissors in C

A robust, modular, and interactive console-based implementation of the classic **Rock, Paper, Scissors** game written in C (C11 standard). The project features strict input validation, comprehensive score tracking with early-termination detection, modular game logic, and an automated test suite.

---

## Table of Contents

- [Overview](#overview)
- [Objective](#objective)
- [Features](#features)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [Compilation & Execution](#compilation--execution)
- [Automated Testing](#automated-testing)
- [Strict Input Validation](#strict-input-validation)
- [Game Logic & Rules Matrix](#game-logic--rules-matrix)
- [Early Termination & Match Interruption](#early-termination--match-interruption)
- [Sample Gameplay](#sample-gameplay)
- [Test Coverage & Observed Results](#test-coverage--observed-results)
- [Possible Future Improvements](#possible-future-improvements)

---

## Overview

This project provides a clean, student-friendly C implementation of Rock, Paper, Scissors. The architecture cleanly decouples deterministic game rules and input parsing (`game_logic.c`) from interactive terminal handling (`rockpaperseccisor.c`), enabling isolated unit testing without sacrificing simplicity or readability.

---

## Objective

The objective of the game is to score more round victories than the computer across a series of rounds. In each round, both players simultaneously select one of three moves:
- **Rock (0)**: Defeats Scissors, loses to Paper.
- **Paper (1)**: Defeats Rock, loses to Scissors.
- **Scissors (2)**: Defeats Paper, loses to Rock.

---

## Features

- **Strict Input Validation**:
  - Replaces fragile `scanf` calls with standard `fgets()` and `strtol()`.
  - Rejects partial strings like `2abc`, floating-point values like `1.5`, and empty inputs.
  - Detects integer overflow and underflow (`ERANGE`).
  - Safely handles excessively long input lines without buffer overflows.
- **Accurate Match State Tracking**:
  - Tracks both requested rounds and actually completed rounds.
  - Distinguishes between completed games and interrupted matches (e.g. EOF / stream termination).
  - Unfinished rounds are never counted toward scores.
- **Modular Architecture**:
  - Deterministic game rules and parsing reside in `game_logic.c`.
  - Terminal presentation and game loop reside in `rockpaperseccisor.c`.
- **Automated Test Suite**:
  - Includes a standalone unit test executable (`tests/test_logic.c`) covering the full 9-outcome rules matrix, boundary values, parser validation, and random choice bounds.
- **Single-Seeded Random Generator**:
  - `srand()` is seeded exactly once at application startup.

---

## Requirements

- **Language Standard**: C11
- **Compiler**: GCC (MinGW / MinGW-w64 on Windows)
- **Standard Libraries**: `<stdio.h>`, `<stdlib.h>`, `<time.h>`, `<string.h>`, `<ctype.h>`, `<errno.h>`, `<limits.h>`, `<assert.h>`
- **Operating System**: Windows (tested on Windows with MinGW GCC 6.3.0)

---

## Project Structure

```text
Rock-paper-scesior-using-C/
├── rockpaperseccisor.c   # Main interactive game entry point
├── game_logic.c          # Pure game logic, input parsing, and move resolution
├── game_logic.h          # Header declarations and shared constants
├── tests/
│   └── test_logic.c      # Automated assertion-based test suite
├── .gitignore            # Git ignore rules for binaries and build artifacts
└── README.md             # Comprehensive project documentation
```

---

## Compilation & Execution

### Compile the Game

Using GCC with strict C11 compliance and compiler warnings:

```cmd
gcc -std=c11 -Wall -Wextra -Wpedantic rockpaperseccisor.c game_logic.c -o rockpaperseccisor.exe
```

### Run the Game

```cmd
.\rockpaperseccisor.exe
```

---

## Automated Testing

The project includes an automated test runner that verifies game logic and input parsing independently from the interactive CLI.

### Compile the Tests

```cmd
gcc -std=c11 -Wall -Wextra -Wpedantic tests/test_logic.c game_logic.c -I. -o tests/test_logic.exe
```

### Run the Tests

```cmd
.\tests\test_logic.exe
```

Expected output:

```text
=========================================
   ROCK PAPER SCISSORS AUTOMATED TESTS   
=========================================

[TEST] Testing complete 9-outcome game rules matrix...
  -> PASS: All 9 move outcomes verified.
[TEST] Testing rejection of invalid choices...
  -> PASS: Invalid choice boundary conditions verified.
[TEST] Testing choice_to_string mapping...
  -> PASS: String conversions verified.
[TEST] Testing strict integer parsing and error detection...
  -> PASS: Strict input validation and rejection verified.
[TEST] Testing get_computer_choice random bounds...
  -> PASS: Computer choices always stay within [0, 2].

=========================================
   ALL AUTOMATED TESTS PASSED (100%)    
=========================================
```

---

## Strict Input Validation

Input parsing is managed by `parse_strict_int()` and `read_input_line()`:

1. **Line Buffering**: Lines are read safely into a fixed buffer using `fgets()`. If an input line exceeds the buffer size, trailing characters are flushed until `\n` or `EOF` to prevent corrupting subsequent prompts.
2. **Whitespace Trimming**: Leading and trailing whitespace characters are permitted and trimmed.
3. **Integer Strictness**: `strtol()` converts the numeric portion. If trailing non-whitespace characters remain (such as in `2abc` or `1.5`), the input is rejected.
4. **Range & Overflow Detection**: Inputs exceeding `INT_MIN` or `INT_MAX` or triggering `errno == ERANGE` are rejected.
5. **Move Boundary Checks**: Moves must strictly fall in `{0, 1, 2}`. Round counts must be positive integers (`> 0`).

---

## Game Logic & Rules Matrix

Move values:
- `0` = Rock
- `1` = Paper
- `2` = Scissors

| Player Move | Computer Move | Round Outcome | Code Constant |
| :--- | :--- | :--- | :--- |
| **Rock (0)** | Rock (0) | Draw | `RESULT_DRAW` (0) |
| **Rock (0)** | Paper (1) | Computer Wins | `RESULT_COMPUTER_WIN` (2) |
| **Rock (0)** | Scissors (2) | **Player Wins** | `RESULT_PLAYER_WIN` (1) |
| **Paper (1)** | Rock (0) | **Player Wins** | `RESULT_PLAYER_WIN` (1) |
| **Paper (1)** | Paper (1) | Draw | `RESULT_DRAW` (0) |
| **Paper (1)** | Scissors (2) | Computer Wins | `RESULT_COMPUTER_WIN` (2) |
| **Scissors (2)** | Rock (0) | Computer Wins | `RESULT_COMPUTER_WIN` (2) |
| **Scissors (2)** | Paper (1) | **Player Wins** | `RESULT_PLAYER_WIN` (1) |
| **Scissors (2)** | Scissors (2) | Draw | `RESULT_DRAW` (0) |

Inputs outside `{0, 1, 2}` return `RESULT_INVALID` (-1) to ensure only valid moves are evaluated.

---

## Early Termination & Match Interruption

If `EOF` occurs during gameplay (e.g. via piped input or stream termination):
- The program halts immediately without entering an infinite loop.
- It prints `Notice: The match ended early due to input termination.`
- The summary clearly displays `Completed rounds: X of Y`.
- Unfinished rounds are never counted toward the final score.
- The outcome header distinguishes between `----- GAME OVER -----` (full match) and `----- MATCH INTERRUPTED -----` (partial match).

---

## Sample Gameplay

### Full Match

```text
-----! HELLO PLAYER !-----
------ Welcome to Game Rock(0), Paper(1), Scissors(2) -----
Enter the number of rounds: 2

---- Round 1 of 2 start -----
Enter your choice - Rock(0), Paper(1), Scissors(2): 0
Player choice: Rock
Computer Choice is Scissors
Match is win by Player

---- Round 2 of 2 start -----
Enter your choice - Rock(0), Paper(1), Scissors(2): 1
Player choice: Paper
Computer Choice is Rock
Match is win by Player

----- GAME OVER -----
------ Completed rounds: 2 of 2 ------
------ Total number of wins by player: 2 ------
------ Total number of wins by computer: 0 ------
------ Total number of tied rounds: 0 ------
===== Overall winner is player by 2 round(s)! =====
```

### Interrupted Match

```text
-----! HELLO PLAYER !-----
------ Welcome to Game Rock(0), Paper(1), Scissors(2) -----
Enter the number of rounds: 3

---- Round 1 of 3 start -----
Enter your choice - Rock(0), Paper(1), Scissors(2): 0
Player choice: Rock
Computer Choice is Rock
Match is tied

---- Round 2 of 3 start -----
Enter your choice - Rock(0), Paper(1), Scissors(2): 
Input terminated during round 2. Ending match early.

----- MATCH INTERRUPTED -----
Notice: The match ended early due to input termination.
------ Completed rounds: 1 of 3 ------
------ Total number of wins by player: 0 ------
------ Total number of wins by computer: 0 ------
------ Total number of tied rounds: 1 ------
======= Current standings: Tie! =======
```

---

## Test Coverage & Observed Results

Automated unit tests in `tests/test_logic.c` execute the following:
1. **Rule Matrix Tests**: Asserts correct outcome for all 9 move combinations. (**PASS**)
2. **Invalid Input Boundary Tests**: Asserts `RESULT_INVALID` for negative choices and values $\ge 3$. (**PASS**)
3. **String Mapping Tests**: Asserts exact string names for valid moves and `"Unknown"` for out-of-range moves. (**PASS**)
4. **Parser Strictness Tests**: Asserts acceptance of valid integers (with and without whitespace) and rejection of `2abc`, `1.5`, empty strings, non-numeric strings, and overflow values. (**PASS**)
5. **Computer Move Bounds**: Asserts that 500 consecutive random computer moves strictly stay within `[0, 2]`. (**PASS**)

---

## Possible Future Improvements

- Add selectable difficulty settings (e.g. frequency-tracking counter-moves).
- Add support for word-based input choices (`"rock"`, `"paper"`, `"scissors"`).
- Add a replay prompt (`Play again? [y/n]`) without restarting the executable.
